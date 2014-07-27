#include "videothread.h"

material::VideoThread::VideoThread(int frequency , QObject* parent) : QThread(parent)
{
    time_slice = static_cast<int>(1000 / frequency);
    frame = 0;
    capture = cvCaptureFromCAM(0);

    //problem : cannnot control the size of the image begin captured
    //the frequency also cannot be controled
    cvSetCaptureProperty(capture , CV_CAP_PROP_FRAME_WIDTH , videoWidth);
    cvSetCaptureProperty(capture , CV_CAP_PROP_FRAME_HEIGHT , videoHeight);

    process_method = new manipulate::MotionProcess(20);
    realImage = cvCreateImage(cvSize(videoWidth , videoHeight) , IPL_DEPTH_8U , 3);
}

material::VideoThread::~VideoThread()
{
    cvReleaseImage(&realImage);
    cvReleaseCapture(&capture);
}

void material::VideoThread::run()
{
    
    while(true)
    {
        double t = (double) cvGetTickCount();               //face detection and get time

        frame = cvQueryFrame(capture);

        t = (double) cvGetTickCount() - t;
        std::cout<<t/((double)cvGetTickFrequency() * 1000)<<"ms"<<std::endl;

        cvCopy(frame , realImage);
        process_method->area_of_interest(realImage , ROI);
        process_method->process_video(ROI , answer);
        process_method->fill_in_area(realImage , answer);        

        emit frame_change();
        //std::cout<<counter++<<std::endl;
    }
}

