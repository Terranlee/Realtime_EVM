#ifndef PROCESS_H
#define PROCESS_H

//some pre process and build of the pyramid
//different kind of magnify need different kind of process
//use the inherit of virtual class Process

#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>

#include "magnify.h"


namespace manipulate
{
    //different kind of amplify and spacial filter

    using std::vector;

    //const related to the video
    const int videoHeight = 240;
    const int videoWidth = 320;

    //const related to the ROIHeight and ROIWidth
    const int ROIHeight = videoHeight;
    const int ROIWidth = videoWidth;

    //const needed for the face detect
    const int FACE_LINE_WIDTH = 3;
    const char* const cascadeName = "haarcascade_frontalface_alt.xml";
    const CvRect empty = cvRect(0,0,0,0);

    //const for the magnify
    const float alphaConst = 10.0f;
    const float lambdaCConst = 80.0f;
    const float factor = 3.0f;
    const float exaggeration = 2.0f;
    const float attenuationConst = 0.1;

    class Process
    {
    protected:
    	//virables about amplify
    	float alpha;
    	float delta;
    	float lambda;
    	float lambdaC;

    	//virables about processing
        int face_frequency;                      //how frequency do we need a face detect
        int pyramidLevel;                        //the highest level of pyramid
        CvRect area_ROI;

        manipulate::Temporal* magnifyMethod;    //the temporal filter method and amplify

        //functions about the program
        void calculate_other_param();
        void face_detect(const IplImage*);       //face detect function and set the ROI
        int get_max();                           //get the max size face in the picture

        //protected virtual functions , different kind of amplify need different process
        virtual void build_pyramid(const cv::Mat& , vector<cv::Mat>& ) = 0;
        virtual void amplify(const cv::Mat& , cv::Mat&) = 0;
        virtual void reconstruction(const vector<cv::Mat>& , cv::Mat&) = 0;

    public:
        Process(int f = 10);

        //set functions
        void set_parameters(float a = alphaConst, float lc = lambdaCConst);
        void set_face_frequency(int f){ face_frequency = f; }
        void set_pyramid_level(int l){ pyramidLevel = l; }

        //preprocess and functions
        void area_of_interest(IplImage* , cv::Mat&);      //choose the area of interest , like cvSetROI
        void fill_in_area(IplImage* , const cv::Mat&);

        //public virtual functions
        virtual void process_video(cv::Mat& , cv::Mat&) = 0;
    };


    class MotionProcess : public Process
    {
    private:
    	vector<cv::Mat> pyramid;
    	vector<cv::Mat> filtered;
    	float chromAttenuation;

    protected:
    	void attenuation(cv::Mat& , cv::Mat&);

        //virtual functions inherited from Process
        virtual void build_pyramid(const cv::Mat& , vector<cv::Mat>& );
        virtual void reconstruction(const vector<cv::Mat> &, cv::Mat &);
        virtual void amplify(const cv::Mat& , cv::Mat&);

    public:
        MotionProcess(int f = 10) : Process(f) { pyramid.clear() , filtered.clear(); chromAttenuation = attenuationConst; }
        void set_chromAtt(float ch) { chromAttenuation = ch; }

        //for motion magnification , use laplacian_pyramid
        virtual void process_video(cv::Mat& , cv::Mat&);
    };


    class ColorProcess : public Process
    {
    private:
        vector<cv::Mat> pyramid;
        vector<cv::Mat> filtered;
        vector<CvSize> sizePyr;

    protected:
        void get_size_pyr(const cv::Mat& );

        //virtual functions inherited from Process
        virtual void build_pyramid(const cv::Mat& , vector<cv::Mat>& );
        virtual void reconstruction(const vector<cv::Mat> &, cv::Mat &);
        virtual void amplify(const cv::Mat& , cv::Mat&);
    public:
        ColorProcess(int f = 10) : Process(f) { pyramid.clear() , filtered.clear(); sizePyr.clear(); }

        //for color magnification , use gaussian_pyramid
        virtual void process_video(cv::Mat& , cv::Mat&);
    };
    void print(const cv::Mat&);
}

#endif // PROCESS_H
