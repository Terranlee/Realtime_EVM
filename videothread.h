#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

//about the video input
//also include the pointer of

#include <iostream>
#include <vector>
#include <QThread>
#include "process.h"

using std::cout;
using std::endl;
using std::vector;

typedef cv::Vec3f DTYPE;
typedef int CTYPE;

namespace material
{
    using std::vector;
    using manipulate::videoHeight;
    using manipulate::videoWidth;
    
    class VideoThread : public QThread
    {
        Q_OBJECT

    private:
        CvCapture* capture;

        IplImage* frame;         //directly copy the pointer of picture in cvCapture
        IplImage* realImage;     //a copy of the frame and the one which is processed

        cv::Mat ROI;
        cv::Mat answer;

        manipulate::Process* process_method;

        int time_slice;         //the time slice to capture the next frame

    protected:
        void run();

    public:
        explicit VideoThread(int frequency , QObject* parent = 0);

        void set_time_slice(int frequency){
            time_slice = static_cast<int>(1000 / frequency);
        }
        IplImage* acquire_access(){ return realImage; }         //access to the IplImage

    signals:
        void frame_change();          //new frame is comming
    };

}

#endif // VIDEOTHREAD_H
