// Defines color util functions used for result messages, depending on the user operating system 

#ifndef LINUX_UTILS_HPP
#define LINUX_UTILS_HPP

#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

namespace UtilsOSDependable{

  int convert_16_bit_to_8_bit(const string& hex16);
	float get_terminal_bg_color_luminance();
  tuple<int, int, int> parse_terminal_color_response(const string& response);
  string capture_terminal_response();
  bool is_bg_color_dark();
};


#endif



