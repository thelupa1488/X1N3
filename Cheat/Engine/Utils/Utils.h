#pragma once
#include <Windows.h>
#include <string>

using namespace std;

namespace Utils
{
	/* Wait dwMsec Load Module */
	bool IsModuleLoad(PCHAR szModule, DWORD dwMsec = 5000);
	/* Get Module File Path */
	string GetModuleFilePath(HMODULE hModule);
	/* Get Module Dir */
	string GetModuleBaseDir(HMODULE hModule);
	/* IDA Style 00 FF ?? */
	DWORD PatternScan(std::string moduleName, std::string Mask);
	/* IDA Style \xE8????\x8B */
	std::uintptr_t FindPattern(const wchar_t* module, const char* pattern);
}