#ifndef Magnify_H
#define Magnify_H

//some method of Amplify the video
//different kind of Amplify_method
//use the inherit of virtual class Amplify

#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

namespace manipulate
{
    enum temporal_method { IIR , IDEAL , BUTTER };

    using std::vector;

    //const related to the frequency of heart beat
    const float heart_low = 0.4f;
    const float heart_high = 4.0f;

    //const about the pyramid
    const int defaultPyramidLevel = 4;

    class Temporal
    {
    protected:
        float fl;
        float fh;
        int pyramidLevel;

    public:
        Temporal(float l = heart_low , float h = heart_high , int pl = defaultPyramidLevel) : fl(l) , fh(h) , pyramidLevel(pl) {}
        virtual void first_frame(const vector<cv::Mat>&) = 0;
        virtual void temporal_filtering(const cv::Mat& , cv::Mat&) = 0;
    };


    class IIRTemporal : public Temporal
    {
    private:
        vector<cv::Mat> lowpass1;
        vector<cv::Mat> lowpass2;
        int curLevel;

    public:
        IIRTemporal(float l = heart_low, float h = heart_high , int pl = defaultPyramidLevel ) : Temporal(l , h , pl) { lowpass1.clear() , lowpass2.clear(); curLevel = 0; }
        void first_frame(const vector<cv::Mat>&);
        void temporal_filtering(const cv::Mat& , cv::Mat&);
    };

    class IdealTemporal : public Temporal
    {
    private:
        float ratio;

    protected:
        void ideal_bandpassing(cv::Mat&);

    public:
        IdealTemporal(float l = heart_low , float h = heart_high , int pl = defaultPyramidLevel) : Temporal(l , h , pl) {}
        void set_ratio(float r) { ratio = r; }
        void first_frame(const vector<cv::Mat>&);
        void temporal_filtering(const cv::Mat& , cv::Mat&);
    };

}


#endif // Magnify_H
