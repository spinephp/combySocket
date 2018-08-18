#pragma once 

#include <tchar.h>
#include <string>
#include <map>
using namespace std;

#ifdef _UNICODE
#define string wstring
#else
#define string std::string
#endif