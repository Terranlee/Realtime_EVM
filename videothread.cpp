#include "videothread.h"

material::VideoThread::VideoThread(int frequency , QObject* parent) : QThread(parent)
{
    time_slice = static_cast<int>(1000 / frequency);
    frame = 0;
    capture = cvCaptureFromCAM(0);
    cvSetCaptureProperty(capture , CV_CAP_PROP_FRAME_WIDTH , videoWidth);
    cvSetCaptureProperty(capture , CV_CAP_PROP_FRAME_HEIGHT , videoHeight);
    process_method = new manipulate::MotionProcess(20);
    realImage = cvCreateImage(cvSize(videoWidth , videoHeight) , IPL_DEPTH_8U , 3);
}

void material::VideoThread::run()
{
    while(true)
    {
        frame = cvQueryFrame(capture);
        cvCopy(frame , realImage);
        process_method->area_of_interest(realImage , ROI);
        process_method->process_video(ROI , answer);
        emit frame_change();
        //std::cout<<counter++<<std::endl;
    }

}
