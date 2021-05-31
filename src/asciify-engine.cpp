#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "asciify-engine.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <map>
#include "terminal.h"

bool isbetween(int a, int b, int c)
{
    return c > a && c < b;
}
AsciifyEngine::AsciifyEngine(cv::Mat img)
: img(img){}


std::vector<int> AsciifyEngine::get_intensities(cv::Mat& img)
{
    std::vector<int> intensities;
    for (int i = 0; i < img.rows; ++i)
    {
        for (int j = 0; j < img.cols; ++j)
        {
            cv::Vec3b intensity = img.at<cv::Vec3b>(i, j);
            std::array<int, 3> rgb;

            for (int k = 0; k < img.channels(); ++k)
            {
                rgb[k] = intensity.val[k];
            }

            int in = (int)(0.2126f * (float)rgb[2] + 0.7152f * (float)rgb[1] + 0.0722f * (float)rgb[0]);
            intensities.emplace_back(in);
        }
    }
    return intensities;
}


std::string* AsciifyEngine::generate_frame()
{
	HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, NULL);
    COORD coords = Terminal::max_size();
	std::string* output = new std::string("");
    cv::Mat img_resized;
    cv::resize(img, img_resized, cv::Size(coords.X, coords.Y));
    std::vector<int> intensities = AsciifyEngine::get_intensities(img_resized);
    for (int row_count = 0; row_count < img_resized.rows; row_count++)
    {

        for (int col_count = 0; col_count < img_resized.cols; col_count++)
        {
            if (isbetween(-1, 51, intensities[(row_count * img_resized.cols + col_count)]))
                *output += ":";
            else if (isbetween(51, 102, intensities[(row_count * img_resized.cols + col_count)]))
                *output += "=";
            else if (isbetween(102, 153, intensities[(row_count * img_resized.cols + col_count)]))
                *output += "$";
            else if (isbetween(153, 204, intensities[(row_count * img_resized.cols + col_count)]))
                *output += "#";
            else if (isbetween(204, 256, intensities[(row_count * img_resized.cols + col_count)]))
                *output += "@";
            else
                *output += ".";

        }
    }

    return output;
}