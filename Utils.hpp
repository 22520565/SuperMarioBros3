#pragma once

#include <csignal>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stdfloat>
#include <string>
#include <vector>
#include <windows.h>

namespace game {
    std::vector<std::string> split(std::string line, std::string delimeter = "\t");
    std::wstring ToWSTR(std::string st);

    LPCWSTR ToLPCWSTR(std::string st);
}
