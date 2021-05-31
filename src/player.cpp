#include "player.h"
#include "asciify-engine.h"
#include <iostream>
#include <string>
#include <Windows.h>

Player::Player(std::string file_path)
: vid(cv::VideoCapture(file_path)){}

std::vector<std::string*> Player::generate_frames()
{
	std::vector<std::string*> output;
	cv::Mat img;
	int frame_numbers = vid.get(cv::CAP_PROP_FRAME_COUNT);
	int total_frames = 0;
	while (vid.read(img))
	{
		AsciifyEngine* asceng = new AsciifyEngine(img);
		output.emplace_back(asceng->generate_frame());
		delete asceng;
		total_frames++;
		if (total_frames % 3 == 0)
			std::cout << "\r" << "Rendered " << total_frames << " frames";
	}
	frames = output;
	return output;
}

void Player::play() //Pause with the space key, and resume with the enter key.
{
	std::vector<std::string*> frame_output = generate_frames();
	std::string finish_message = "Done playing the Video!";
	bool key_r = false;
	bool key_l = false;
	bool key_space = false;
	bool paused = false;

	frame_output.emplace_back(&finish_message);
	HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console);
	DWORD bytes_written = 0;

	while (curr_frame < frame_output.size())
	{
		std::string* str = frame_output[curr_frame];
		WriteConsoleOutputCharacter(console, str->c_str(), str->size(), { 0, 0 }, &bytes_written);

		if (GetAsyncKeyState(VK_RIGHT) && !key_r)
		{
			progress(5);
			key_r = true;
		}

		if (GetAsyncKeyState(VK_LEFT) && !key_l)
		{
			progress(-5);
			key_l = true;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			paused = true;
		}

 		if (paused)
		{
			if (GetAsyncKeyState(VK_RETURN))
			{
				paused = false;
			}
		}

		if (!GetAsyncKeyState(VK_LEFT))
			key_l = false;

		if (!GetAsyncKeyState(VK_RIGHT))
			key_r = false;


		if (!paused) curr_frame++;
		Sleep(std::floor(1000 / vid.get(cv::CAP_PROP_FPS)));
	}
	std::cout << "\nDone Playing\n";

}

void Player::progress(int seconds)
{
	int fps = (int)vid.get(cv::CAP_PROP_FPS);
	curr_frame += (fps * seconds);
	if (curr_frame < 0)
		curr_frame = 0;
}

