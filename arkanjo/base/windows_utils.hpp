// 

#ifndef WINDOWS_UTILS_HPP
#define WINDOWS_UTILS_HPP

#pragma once
#include <string>
#include <sstream>

using namespace std;

namespace UtilsOSDependable{

  float get_terminal_bg_color_luminance();
  tuple<int, int, int> parse_terminal_color_response();
  bool is_bg_color_dark();
};


#endif