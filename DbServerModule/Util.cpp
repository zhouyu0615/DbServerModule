#include "stdafx.h"
#include "Util.h"


std::string MyCStringToStr(const CString& cstr)
{
	USES_CONVERSION;
	std::string str(W2A(cstr));
	return str;
}

