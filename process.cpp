#include "process.h"

static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;
static CvSeq* faces = 0;

static CvScalar colors[] = { {{0,0,255,0}} , {{0,128,255,0}} , {{0,255,255,0}} , {{0,255,0,0}} ,\
                             {{255,128,0,0}} , {{255,255,0,0}} , {{255,0,0,0}} , {{255,0,255,0}} };

//shared functions of process
manipulate::Process::Process(int f)
{
    face_frequency = f;
    pyramidLevel = defaultPyramidLevel;
    cascade = (CvHaarClassifierCascade*)cvLoad(cascadeName,0,0,0);          //initialize the cascade
    storage = cvCreateMemStorage(0);

    magnifyMethod = new IIRTemporal(0.4f , 2.0f , pyramidLevel);
    set_parameters();
}

void manipulate::Process::calculate_other_param()
{
	//calculate lambda
	delta = lambdaC / 8.0 / (1.0 + alpha);
	lambda = sqrt(videoHeight * videoHeight + videoWidth * videoWidth) / factor;
}

void manipulate::Process::set_parameters(float a , float lc)
{
	//set the parameters used for the amplify
	alpha = a;
	lambdaC = lc;
	calculate_other_param();
}

int manipulate::Process::get_max()
{
    if(faces->total == 0)
        return -1;              //no faces are found
    else
    {
        CvRect* r;
        int max_num = INT_MIN;
        int counter = -1;
        for(int i=0; i<faces->total ; i++)
        {
            r = (CvRect*) cvGetSeqElem(faces , i);
            if(r->height * r->width > max_num)            //find the max face in the picture
            {
                max_num = r->height * r->width;
                counter = i;
            }
        }
        return counter;
    }
}

void manipulate::Process::face_detect(const IplImage* input)
{
    IplImage* gray_input = cvCreateImage(cvGetSize(input) , input->depth , 1);
    cvCvtColor(input , gray_input , CV_BGR2GRAY);
    cvEqualizeHist(gray_input , gray_input);          //some initialization of face detection
    cvClearMemStorage(storage);
    if(faces != 0) cvClearSeq(faces);

    double t = (double) cvGetTickCount();               //face detection and get time
    faces = cvHaarDetectObjects(gray_input , cascade , storage , 1.2 , 2 , CV_HAAR_DO_CANNY_PRUNING , cvSize(30 , 30));
    t = (double) cvGetTickCount() - t;
    std::cout<<"detection time is:"<<t/((double)cvGetTickFrequency() * 1000)<<"ms"<<std::endl;
    cvReleaseImage(&gray_input);
}

void manipulate::Process::area_of_interest(IplImage* input, cv::Mat& ROI)
{
    //set area of interest
    //cv::Mat doesn't provide setROI , so we have to copy that to a new cv::Mat
    static int counter = 0;
    static CvRect area_ROI;
    area_ROI.width = ROIWidth;
    area_ROI.height = ROIHeight;
    static bool detectAns;

    if(counter == 0)
    {
        face_detect(input);
        int number = get_max();
        if(number == -1)               //no face detected , ROI is in the middle
        {
            area_ROI = cvRect(videoWidth/2 - ROIWidth/2 , videoHeight/2 - ROIHeight/2 , ROIWidth , ROIHeight);
            detectAns = false;
            cvRectangle(input , cvPoint(area_ROI.x , area_ROI.y) , cvPoint(area_ROI.x+area_ROI.width ,\
                                                area_ROI.y+area_ROI.height) , colors[0] , FACE_LINE_WIDTH);
        }
        else                            //face detected , ROI is in the face area
        {
            CvRect temp = (*(CvRect*)cvGetSeqElem(faces , number));
            if(temp.x + ROIWidth >= videoWidth)
                area_ROI.x = videoWidth - ROIWidth - FACE_LINE_WIDTH;
            else
                area_ROI.x = temp.x;

            if(temp.y + ROIHeight >= videoHeight)
                area_ROI.y = videoHeight - ROIHeight - FACE_LINE_WIDTH;
            else
                area_ROI.y = temp.y;
            detectAns = true;
            cvRectangle(input , cvPoint(area_ROI.x , area_ROI.y) , cvPoint(area_ROI.x+area_ROI.width ,\
                                                area_ROI.y+area_ROI.height) , colors[6] , FACE_LINE_WIDTH);
        }
        
    }
    cv::Mat all = cv::Mat(input , 0);
    ROI = all(area_ROI);

    counter++;
    if(counter == face_frequency)
        counter = 0;
}

//unique functions for MotionProcess
void manipulate::MotionProcess::process_video(cv::Mat& input , cv::Mat& output)
{
    bool ifFirst = false;       //if this is the first frame of the video

    input.convertTo(input , CV_32FC3 , 1.0f/255.0f);         //change of the data_type
    cv::cvtColor(input , input , CV_BGR2Lab);
    if(pyramid.size() == 0)
        ifFirst = true;

    build_pyramid(input , pyramid);

    //if this is the first time , just copy the pyramid
    if(ifFirst)
    {
        filtered = pyramid;
        magnifyMethod->first_frame(pyramid);
        output = input.clone();
    }
    //else , use temporal_filter  and amplify
    else
    {
        for(int i=0; i<pyramidLevel; i++)
            magnifyMethod->temporal_filtering(pyramid.at(i) , filtered.at(i));

        lambda = sqrt(videoHeight * videoHeight + videoWidth * videoWidth) / factor;
        for(int i=pyramidLevel; i>=0; i--)
        {
        	amplify(filtered.at(i) , filtered.at(i));
        	lambda /= 2.0;
        }
        reconstruction(filtered , output);
        attenuation(output , output);
        output += input;
    }
    cv::cvtColor(output , output , CV_Lab2BGR);
	output.convertTo(output , CV_8UC3 , 255.0 , 1.0 / 255.0);
}

void manipulate::MotionProcess::amplify(const cv::Mat& input , cv::Mat& output)
{
	//counter about which level it is
	static int level = pyramidLevel;

	//amplify for motion processing using laplacian pyramnid
	float curAlpha = lambda/delta/8.0 - 1;
	curAlpha *= exaggeration;

	if(level == pyramidLevel || level == 0)      //clear this two level of pyramid
		output = input * 0;
	else
		output = input * std::min(alpha , curAlpha);

	level--;
	if(level == -1)
		level = pyramidLevel;
}

void manipulate::MotionProcess::build_pyramid(const cv::Mat& input , vector<cv::Mat>& lPyramid)
{
    //use laplacian pyramid during motion process
    lPyramid.clear();
    cv::Mat source = input;
    cv::Mat quarter , full , laplacian;
    for(int i=0; i<pyramidLevel; i++)
    {
        cv::pyrDown(source , quarter);
        cv::pyrUp(quarter , full , source.size());
        laplacian = source - full;
        lPyramid.push_back(laplacian);
        source = quarter;
    }
    lPyramid.push_back(source);
}

void manipulate::MotionProcess::attenuation(cv::Mat& input , cv::Mat& output)
{
	//reduce the second and third channel of the image
	//chromAttenuation is a constant according to the paper
	cv::Mat channels[3];
	cv::split(input , channels);
	channels[1] = channels[1] * chromAttenuation;
	channels[2] = channels[2] * chromAttenuation;
	cv::merge(channels , 3 , output);
}

void manipulate::MotionProcess::reconstruction(const vector<cv::Mat>& lPyramid , cv::Mat& output)
{
    //reconstruct the picture from the pyramid
    cv::Mat addTo = lPyramid[pyramidLevel];
    cv::Mat fourfold;
    for(int i=pyramidLevel-1; i>=0; i--)
    {
        cv::pyrUp(addTo , fourfold , lPyramid[i].size());
        addTo = fourfold + lPyramid[i];
    }
    output = addTo.clone();
}


//unique functions for ColorProcess
void manipulate::ColorProcess::process_video(cv::Mat & input , cv::Mat& output)
{

}

void manipulate::ColorProcess::amplify(const cv::Mat& input , cv::Mat& output)
{

}

void manipulate::ColorProcess::build_pyramid(const cv::Mat& input , vector<cv::Mat>& gPyramid)
{
    //use gaussian pyramid during motion process
    gPyramid.clear();
    cv::Mat source , quarter;
    for(int i=0; i<pyramidLevel; i++)
    {
        cv::pyrDown(source , quarter);
        gPyramid.push_back(quarter);
        source = quarter;
    }
    gPyramid.push_back(source);
}

void manipulate::ColorProcess::reconstruction(const vector<cv::Mat>& gPyramid , cv::Mat& output)
{
    //reconstruct the picture from Gaussian pyramid

}
