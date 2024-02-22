#pragma once

#include <windows.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <stdarg.h>
#include <vector>

using namespace std;

vector<string> split(string line, string delimeter = "\t");
wstring ToWSTR(string st);

LPCWSTR ToLPCWSTR(string st);
