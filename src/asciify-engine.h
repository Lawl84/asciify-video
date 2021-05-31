#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

class AsciifyEngine
{
public:
	cv::Mat img;
	AsciifyEngine(cv::Mat img);
	static std::vector<int> get_intensities(cv::Mat& img);
	std::string* generate_frame();
};