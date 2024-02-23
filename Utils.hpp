#pragma once

#include <windows.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <stdarg.h>
#include <vector>

std::vector<std::string> split(std::string line, std::string delimeter = "\t");
std::wstring ToWSTR(std::string st);

LPCWSTR ToLPCWSTR(std::string st);
