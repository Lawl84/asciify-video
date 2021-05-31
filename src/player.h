#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include "asciify-engine.h"

class Player
{
public:
	cv::VideoCapture vid;
	int curr_frame = 0;
	std::vector<std::string*> frames;
	Player(std::string file_path);
	std::vector<std::string*> generate_frames();
	void progress(int seconds);
	void play();
};