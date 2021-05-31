#include "terminal.h"
#include <string>
#include <iostream>
#include <vector>

COORD Terminal::max_size()
{
	HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, NULL);
	return GetLargestConsoleWindowSize(console);
}