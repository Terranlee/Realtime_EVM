#include "magnify.h"

//copy the pyramid to lowpass
//use this function in the first time of temporal filtering
void manipulate::IIRTemporal::first_frame(const vector<cv::Mat>& input)
{
	lowpass1 = input;
	lowpass2 = input;
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

void manipulate::IdealTemporal::ideal_bandpassing(cv::Mat& input)
{
	int width = input.cols;
	int height = input.rows;

	float curFl = 2 * fl * width / ratio;
	float curFh = 2 * fh * width / ratio;  //question?
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
		{
			if(j >= curFl && j <= curFh)
				input.at<float>(i,j) = 1.0f;
			else
				input.at<float>(i,j) = 0.0f;
		}
}

//temporal filtering using Ideal
void manipulate::IdealTemporal::temporal_filtering(const cv::Mat& input , cv::Mat& output)
{
	//using dft provided by opencv
	cv::Mat channels[3];
	int width = cv::getOptimalDFTSize(input.cols);
	int height = cv::getOptimalDFTSize(input.rows);
	cv::split(input , channels);
	for(int i=0; i<3; i++)
	{
		cv::Mat resizeImg , bandpass;
		cv::copyMakeBorder(channels[i] , resizeImg , 0 , height - channels[i].rows , 0 , width - channels[i].cols , cv::BORDER_CONSTANT , cv::Scalar::all(0));
		cv::dft(resizeImg , resizeImg , cv::DFT_ROWS | cv::DFT_SCALE);
		bandpass = resizeImg.clone();
		ideal_bandpassing(bandpass);
		cv::mulSpectrums(resizeImg , bandpass , resizeImg , cv::DFT_ROWS);
		cv::idft(resizeImg , resizeImg , cv::DFT_ROWS | cv::DFT_SCALE);
		resizeImg(cv::Rect(0,0,channels[i].cols,channels[i].rows)).copyTo(channels[i]);
	}
	cv::merge(channels , 3 , output);
	cv::normalize(output , output , 0 , 1 , CV_MINMAX);
}
