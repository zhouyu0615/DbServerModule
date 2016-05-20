#pragma once
#include <string>


template<typename T>
std::string ToString(T val)
{
	std::string str;
	std::stringstream ss;
	ss << val;
	ss >> str;
	return str;
}

std::string MyCStringToStr(const CString& cstr);


