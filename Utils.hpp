#pragma once

#include <windows.h>
#include <stdfloat>
#include <csignal>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

namespace game {
    std::vector<std::string> split(std::string line, std::string delimeter = "\t");
    std::wstring ToWSTR(std::string st);

    LPCWSTR ToLPCWSTR(std::string st);
}
