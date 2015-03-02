#include "magnify.h"

//copy the pyramid to lowpass
//use this function in the first time of temporal filtering
void manipulate::IIRTemporal::first_frame(const vector<cv::Mat>& input)
{
	lowpass1 = input;
	lowpass2 = input;
    pyramidLevel = input.size() - 1;
}

//temporal filtering using IIR
void manipulate::IIRTemporal::temporal_filtering(const cv::Mat& input , cv::Mat& output)
{
	//using lowpass1 and lowpass2 , which is the previews pyramid
	cv::Mat temp1 = (1-fh)*lowpass1[curLevel] + fh*input;
	cv::Mat temp2 = (1-fl)*lowpass2[curLevel] + fl*input;
	lowpass1[curLevel] = temp1;
	lowpass2[curLevel] = temp2;
	output = lowpass1[curLevel] - lowpass2[curLevel];
	curLevel++;
	if(curLevel == pyramidLevel)
		curLevel = 0;
}

void manipulate::IdealTemporal::first_frame(const vector<cv::Mat>& gPyramid)
{
	//first frame of ideal filtering , set some arguments using the pyramid
	widthOne = gPyramid.at(0).cols;
	heightOne = gPyramid.at(0).rows;
	imageList = cv::Mat(widthOne * heightOne , memoryLength , CV_32FC3);
	filteredList = imageList.clone();
	tickCount = (float)cvGetTickCount();
}

void manipulate::IdealTemporal::ideal_bandpassing(cv::Mat& input)
{
	//create the ideal bandpassing filter
	//input is the image after dft
	int width = input.cols;
	int height = input.rows;

	float curFl = 2 * fl * width / ratio;     //frequency and ratio are updated 
	float curFh = 2 * fh * width / ratio;
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
		{
			if(j >= curFl && j <= curFh)
				input.at<float>(i,j) = 1.0f;
			else
				input.at<float>(i,j) = 0.0f;
		}
}

void manipulate::IdealTemporal::make_image_list(cv::Mat& input , int counter)
{
	//imageList is not ready , do not calculate
	//just return the initial image
	cv::Mat line = input.reshape(3 , widthOne * heightOne).clone();
	line.copyTo( imageList.col(counter) );
}

void manipulate::IdealTemporal::add_to_image_list(const cv::Mat& input)
{
	//move the imageList one pixel to the left
	//and the new image to the end of columns
	cv::Mat line = input.reshape(3 , widthOne * heightOne).clone();
	for(int i=0; i<imageList.rows; i++)
		for(int j=0; j<imageList.cols-1; j++)
			imageList.at<cv::Vec3f>(i,j) = imageList.at<cv::Vec3f>(i,j+1);
	line.copyTo( imageList.col(memoryLength-1) );
}

void manipulate::IdealTemporal::dft_ideal(const cv::Mat& input , cv::Mat& output)
{
	//using dft provided by opencv
	//input is the imageList and the output is the filtered imageList
	cv::Mat channels[3];
	int width = cv::getOptimalDFTSize(input.cols);
	int height = cv::getOptimalDFTSize(input.rows);
	cv::split(input , channels);
	for(int i=0; i<3; i++)
	{
		cv::Mat resizeImg , bandpass;
		cv::copyMakeBorder(channels[i] , resizeImg , 0 , height - channels[i].rows , 0 , width - channels[i].cols , cv::BORDER_CONSTANT , cv::Scalar::all(0));
		cv::dft(resizeImg , resizeImg , cv::DFT_ROWS | cv::DFT_SCALE);    //resizeImg contains the dft infomation
		bandpass = resizeImg.clone();
		ideal_bandpassing(bandpass);            //bandpass contains the filtering information
		cv::mulSpectrums(resizeImg , bandpass , resizeImg , cv::DFT_ROWS);           //multiply the dft result and the bandpass
		cv::idft(resizeImg , resizeImg , cv::DFT_ROWS | cv::DFT_SCALE);
		resizeImg(cv::Rect(0,0,channels[i].cols,channels[i].rows)).copyTo(channels[i]);
	}
	cv::merge(channels , 3 , output);
	cv::normalize(output , output , 0 , 1 , CV_MINMAX);	
}

void manipulate::IdealTemporal::calculate_by_list(const cv::Mat& input , cv::Mat& output)
{
	//the input is the gPyramid[0] , the output is the filtered[0]
	//output is the first image in the imageList ( maybe it can be the last one )
	add_to_image_list(input);
	dft_ideal(imageList , filteredList);
	cv::Mat line = filteredList.col(0).clone();
	output = line.reshape(3 , heightOne).clone();
}

void manipulate::IdealTemporal::calculate_ratio(float delta)
{
	//calculate the ratio 
	static int pointer = 0;
	static float aggregate = 0.0f;

	aggregate -= sumTime[pointer];
	aggregate += delta;
	sumTime[pointer] = delta;
	pointer++;
	if(pointer == memoryLength)
		pointer = 0;

	ratio = 1000.0f / (aggregate / memoryLength);
}

//temporal filtering using Ideal
void manipulate::IdealTemporal::temporal_filtering(const cv::Mat& input , cv::Mat& output)
{
	//the input is the gPyramid[0] , the output is the filtered[0]
	static int counter = 0;

	float delta = tickCount;
	tickCount = (float)cvGetTickCount();
	delta = (tickCount - delta) / ((float)cvGetTickFrequency() * 1000);
	calculate_ratio(delta);

	if(counter <memoryLength)             //imageList is not ready
	{
		make_image_list(input , counter);
		output = input;
	}
	else                                   //add new image to the list and remove the old
		calculate_by_list(input , output);
	counter++;	
}
