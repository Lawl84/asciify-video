#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "asciify-engine.h"
#include "player.h"
#include "terminal.h"

int main(int argc, char* argv[])
{
	Player* player = new Player(argv[1]);
	player->play();
	delete player;
	return 0;
}
	