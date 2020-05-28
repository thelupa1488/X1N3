#pragma once
#include <Windows.h>
#include <map>
#include "../Include/Def.h"
#include "cHide.h"

#define DEREF( name )*(UINT_PTR *)(name)
#define DEREF_64( name )*(DWORD64 *)(name)
#define DEREF_32( name )*(DWORD *)(name)
#define DEREF_16( name )*(WORD *)(name)
#define DEREF_8( name )*(BYTE *)(name)

template<typename T>
class Call
{
protected:
	Call() {}
	~Call() {}

	Call(const Call&) = delete;
	Call& operator=(const Call&) = delete;

	Call(Call&&) = delete;
	Call& operator=(Call&&) = delete;

public:
	static T& G()
	{
		static T inst{};
		return inst;
	}
};

class FastCall : public Call<FastCall>
{
private:

	std::map<std::string, FARPROC> lpAddrList
	{
		{ "CreateThread", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "CreateThread") },
		{ "CloseHandle", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "CloseHandle") },
		{ "MessageBoxA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "MessageBoxA") },
		{ "FindWindowA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "FindWindowA") },
		{ "PlaySoundA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winmm.dll").c_str()), "PlaySoundA") },
		{ "mouse_event", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "mouse_event") },
		{ "GetFileAttributesA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetFileAttributesA") },
		{ "GetThreadContext", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetThreadContext") },
		{ "GetClientRect", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "GetClientRect") },
		{ "SetCursor", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "SetCursor") },
		{ "ImmGetContext", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Imm32.dll").c_str()), "ImmGetContext") },
		{ "ImmSetCompositionWindow", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Imm32.dll").c_str()), "ImmSetCompositionWindow") },
		{ "WaitForSingleObject", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "WaitForSingleObject") },
		{ "MultiByteToWideChar", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "MultiByteToWideChar") },
		{ "GetTickCount64", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetTickCount64") },
		{ "GetLastError", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetLastError") },
		{ "CreateEventA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "CreateEventA") },
		{ "VirtualQuery", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "VirtualQuery") },
		{ "FindFirstFileA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "FindFirstFileA") },
		{ "FindNextFileA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "FindNextFileA") },
		{ "GetFullPathNameA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetFullPathNameA") },
		{ "FindClose", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "FindClose") },
		{ "lstrcmpiA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "lstrcmpiA") },
		{ "Sleep", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "Sleep") },
		{ "GetProcAddress", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetProcAddress") },
		{ "IsBadCodePtr", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "IsBadCodePtr") },
		{ "GetFileAttributesA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetFileAttributesA") },
		{ "DeleteFileA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "DeleteFileA") },
		{ "GlobalAlloc", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GlobalAlloc") },
		{ "GetLocalTime", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetLocalTime") },
		{ "GlobalLock", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GlobalLock") },
		{ "WideCharToMultiByte", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "WideCharToMultiByte") },
		{ "CreateDirectoryA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "CreateDirectoryA") },
		{ "GlobalUnlock", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GlobalUnlock") },
		{ "AddVectoredExceptionHandler", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "AddVectoredExceptionHandler") },
		{ "Beep", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "Beep") },
		{ "GetCurrentThread", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetCurrentThread") },
		{ "GetModuleHandleW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetModuleHandleW") },
		{ "QueryPerformanceFrequency", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "QueryPerformanceFrequency") },
		{ "QueryPerformanceCounter", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "QueryPerformanceCounter") },
		{ "TerminateProcess", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "TerminateProcess") },
		{ "SetEndOfFile", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "SetEndOfFile") },
		{ "WriteConsoleW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "WriteConsoleW") },
		{ "HeapSize", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "HeapSize") },
		{ "CreateFileW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "CreateFileW") },
		{ "SetStdHandle", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "SetStdHandle") },
		{ "SetEnvironmentVariableW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "SetEnvironmentVariableW") },
		{ "GetModuleFileNameA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetModuleFileNameA") },
		{ "GetEnvironmentStringsW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetEnvironmentStringsW") },
		{ "GetCommandLineW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetCommandLineW") },
		{ "GetCommandLineA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetCommandLineA") },
		{ "GetOEMCP", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetOEMCP") },
		{ "GetACP", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetACP") },
		{ "IsValidCodePage", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "IsValidCodePage") },
		{ "FindNextFileW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "FindNextFileW") },
		{ "K32GetModuleInformation", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "K32GetModuleInformation") },
		{ "GetModuleHandleA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetModuleHandleA") },
		{ "lstrlenA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "lstrlenA") },
		{ "GetCurrentProcess", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetCurrentProcess") },
		{ "IsBadReadPtr", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "IsBadReadPtr") },
		{ "GetProcessHeap", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetProcessHeap") },
		{ "HeapAlloc", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "HeapAlloc") },
		{ "FindFirstFileExW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "FindFirstFileExW") },
		{ "HeapReAlloc", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "HeapReAlloc") },
		{ "SetFilePointerEx", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "SetFilePointerEx") },
		{ "FlushFileBuffers", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "FlushFileBuffers") },
		{ "EnumSystemLocalesW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "EnumSystemLocalesW") },
		{ "GetUserDefaultLCID", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetUserDefaultLCID") },
		{ "IsValidLocale", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "IsValidLocale") },
		{ "GetFileType", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetFileType") },
		{ "GetStdHandle", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetStdHandle") },
		{ "HeapFree", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "HeapFree") },
		{ "GetConsoleCP", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetConsoleCP") },
		{ "WriteFile", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "WriteFile") },
		{ "ReadConsoleW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "ReadConsoleW") },
		{ "GetConsoleMode", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetConsoleMode") },
		{ "GetModuleFileNameW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetModuleFileNameW") },
		{ "GetModuleHandleExW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetModuleHandleExW") },
		{ "ExitProcess", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "ExitProcess") },
		{ "ReadFile", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "ReadFile") },
		{ "LoadLibraryExW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "LoadLibraryExW") },
		{ "FreeLibrary", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "FreeLibrary") },
		{ "InterlockedFlushSList", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "InterlockedFlushSList") },
		{ "RaiseException", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "RaiseException") },
		{ "RtlUnwind", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "RtlUnwind") },
		{ "InitializeSListHead", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "InitializeSListHead") },
		{ "GetCurrentThreadId", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetCurrentThreadId") },
		{ "FreeEnvironmentStringsW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "FreeEnvironmentStringsW") },
		{ "EnterCriticalSection", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "EnterCriticalSection") },
		{ "LeaveCriticalSection", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "LeaveCriticalSection") },
		{ "DeleteCriticalSection", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "DeleteCriticalSection") },
		{ "SetLastError", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "SetLastError") },
		{ "InitializeCriticalSectionAndSpinCount", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "InitializeCriticalSectionAndSpinCount") },
		{ "CreateEventW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "CreateEventW") },
		{ "SwitchToThread", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "SwitchToThread") },
		{ "TlsAlloc", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "TlsAlloc") },
		{ "TlsGetValue", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "TlsGetValue") },
		{ "TlsSetValue", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "TlsSetValue") },
		{ "TlsFree", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "TlsFree") },
		{ "GetSystemTimeAsFileTime", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetSystemTimeAsFileTime") },
		{ "EncodePointer", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "EncodePointer") },
		{ "DecodePointer", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "DecodePointer") },
		{ "GetStringTypeW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetStringTypeW") },
		{ "CompareStringW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "CompareStringW") },
		{ "LCMapStringW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "LCMapStringW") },
		{ "GetLocaleInfoW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetLocaleInfoW") },
		{ "GetCPInfo", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetCPInfo") },
		{ "InitializeCriticalSection", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "InitializeCriticalSection") },
		{ "SetEvent", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "SetEvent") },
		{ "ResetEvent", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "ResetEvent") },
		{ "WaitForSingleObjectEx", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "WaitForSingleObjectEx") },
		{ "UnhandledExceptionFilter", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "UnhandledExceptionFilter") },
		{ "SetUnhandledExceptionFilter", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "SetUnhandledExceptionFilter") },
		{ "IsProcessorFeaturePresent", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "IsProcessorFeaturePresent") },
		{ "IsDebuggerPresent", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "IsDebuggerPresent") },
		{ "GetStartupInfoW", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetStartupInfoW") },
		{ "GetCurrentProcessId", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()), "GetCurrentProcessId") },
		{ "SetWindowLongA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "SetWindowLongA") },
		{ "GetKeyState", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "GetKeyState") },
		{ "GetClipboardData", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "GetClipboardData") },
		{ "OpenClipboard", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "OpenClipboard") },
		{ "CloseClipboard", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "CloseClipboard") },
		{ "GetAsyncKeyState", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "GetAsyncKeyState") },
		{ "GetCursorPos", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "GetCursorPos") },
		{ "SetClipboardData", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "SetClipboardData") },
		{ "EmptyClipboard", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "EmptyClipboard") },
		{ "CallWindowProcA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()), "CallWindowProcA") },
		//{ "VMProtectBeginVirtualization", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("VMProtectSDK32.dll").c_str()), "VMProtectBeginVirtualization") },
		//{ "VMProtectBeginMutation", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("VMProtectSDK32.dll").c_str()), "VMProtectBeginMutation") },
		//{ "VMProtectBeginUltra", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("VMProtectSDK32.dll").c_str()), "VMProtectBeginUltra") },
		//{ "VMProtectBegin", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("VMProtectSDK32.dll").c_str()), "VMProtectBegin") },
		//{ "VMProtectEnd", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("VMProtectSDK32.dll").c_str()), "VMProtectEnd") },
		{ "WinHttpOpenRequest", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()), "WinHttpOpenRequest") },
		{ "WinHttpConnect", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()), "WinHttpConnect") },
		{ "WinHttpOpen", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()), "WinHttpOpen") },
		{ "WinHttpReadData", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()), "WinHttpReadData") },
		{ "WinHttpQueryHeaders", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()), "WinHttpQueryHeaders") },
		{ "WinHttpCloseHandle", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()), "WinHttpCloseHandle") },
		{ "WinHttpSendRequest", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()), "WinHttpSendRequest") },
		{ "WinHttpReceiveResponse", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()), "WinHttpReceiveResponse") },
		{ "WinHttpQueryDataAvailable", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()), "WinHttpQueryDataAvailable") },
		{ "InternetCloseHandle", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()), "InternetCloseHandle") },
		{ "InternetReadFile", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()), "InternetReadFile") },
		{ "HttpOpenRequestA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()), "HttpOpenRequestA") },
		{ "InternetConnectA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()), "InternetConnectA") },
		{ "InternetOpenA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()), "InternetOpenA") },
		{ "HttpSendRequestA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()), "HttpSendRequestA") },
		{ "InternetOpenUrlA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()), "InternetOpenUrlA") },
		{ "D3DXCreateTextureFromFileInMemoryEx", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("d3dx9_43.dll").c_str()), "D3DXCreateTextureFromFileInMemoryEx") },
		{ "D3DXCreateTextureFromFileExA", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("d3dx9_43.dll").c_str()), "D3DXCreateTextureFromFileExA") },
		{ "CreateDXGIFactory1", pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("dxgi.dll").c_str()), "CreateDXGIFactory1") },
	};
public:

	void Start()
	{
		for (auto it = lpAddrList.begin(); it != lpAddrList.end(); ++it)
		{
			printf(": %s ", it->first.c_str());
			printf("add: %X\n",DWORD(it->second));
			//it->second
		}
	}

#define ALL_A(...) __VA_ARGS__

#define CREATE_CALL(type, agrm, name, name_str, args1, args2, args3) type agrm t##name(args1){ \
	using t_##name = type(agrm*)(args2); \
	return reinterpret_cast<t_##name>(lpAddrList[name_str])(args3); \
	}

	CREATE_CALL(ALL_A(_Ret_maybenull_ HANDLE), WINAPI, _CreateThread, "CreateThread",
		ALL_A(_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
			_In_ SIZE_T dwStackSize,
			_In_ LPTHREAD_START_ROUTINE lpStartAddress,
			_In_opt_ __drv_aliasesMem LPVOID lpParameter,
			_In_ DWORD dwCreationFlags,
			_Out_opt_ LPDWORD lpThreadId
		),
		ALL_A(_In_opt_ LPSECURITY_ATTRIBUTES,
			_In_ SIZE_T,
			_In_ LPTHREAD_START_ROUTINE,
			_In_opt_ __drv_aliasesMem LPVOID,
			_In_ DWORD,
			_Out_opt_ LPDWORD
		),
		ALL_A(_In_opt_ lpThreadAttributes,
			_In_ dwStackSize,
			_In_ lpStartAddress,
			_In_opt_ __drv_aliasesMem lpParameter,
			_In_ dwCreationFlags,
			_Out_opt_ lpThreadId
		));

	CREATE_CALL(VOID, WINAPI, _mouse_event, "mouse_event",
		ALL_A(_In_ DWORD dwFlags,
			_In_ DWORD dx,
			_In_ DWORD dy,
			_In_ DWORD dwData,
			_In_ ULONG_PTR dwExtraInfo
		),
		ALL_A(_In_ DWORD,
			_In_ DWORD,
			_In_ DWORD,
			_In_ DWORD,
			_In_ ULONG_PTR
		),
		ALL_A(_In_ dwFlags,
			_In_ dx,
			_In_ dy,
			_In_ dwData,
			_In_ dwExtraInfo
		));

	CREATE_CALL(BOOL, WINAPI, _CloseHandle, "CloseHandle",
		ALL_A(_In_ HANDLE hObject
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hObject
		));

	CREATE_CALL(int, WINAPI, _MessageBoxA, "MessageBoxA",
		ALL_A(_In_opt_ HWND hWnd,
			_In_opt_ LPCSTR lpText,
			_In_opt_ LPCSTR lpCaption,
			_In_ UINT uType
		),
		ALL_A(_In_opt_ HWND,
			_In_opt_ LPCSTR,
			_In_opt_ LPCSTR,
			_In_ UINT
		),
		ALL_A(_In_opt_ hWnd,
			_In_opt_ lpText,
			_In_opt_ lpCaption,
			_In_ uType
		));

	CREATE_CALL(HWND, WINAPI, _FindWindowA, "FindWindowA",
		ALL_A(_In_opt_ LPCSTR lpClassName,
			_In_opt_ LPCSTR lpWindowName
		),
		ALL_A(_In_opt_ LPCSTR,
			_In_opt_ LPCSTR
		),
		ALL_A(_In_opt_ lpClassName,
			_In_opt_ lpWindowName
		));

	CREATE_CALL(BOOL, WINAPI, _PlaySoundA, "PlaySoundA",
		ALL_A(_In_opt_ LPCSTR pszSound,
			_In_opt_ HMODULE hmod,
			_In_ DWORD fdwSound
		),
		ALL_A(_In_opt_ LPCSTR,
			_In_opt_ HMODULE,
			_In_ DWORD
		),
		ALL_A(_In_opt_ pszSound,
			_In_opt_ hmod,
			_In_ fdwSound
		));

	CREATE_CALL(DWORD, WINAPI, _GetFileAttributesA, "GetFileAttributesA",
		ALL_A(_In_ LPCSTR lpFileName
		),
		ALL_A(_In_ LPCSTR
		),
		ALL_A(_In_ lpFileName
		));

	CREATE_CALL(BOOL, WINAPI, _GetThreadContext, "GetThreadContext",
		ALL_A(_In_ HANDLE hThread,
			_Inout_ LPCONTEXT lpContext
		),
		ALL_A(_In_ HANDLE,
			_Inout_ LPCONTEXT
		),
		ALL_A(_In_ hThread,
			_Inout_ lpContext
		));

	CREATE_CALL(BOOL, WINAPI, _GetClientRect, "GetClientRect",
		ALL_A(_In_ HWND hWnd,
			_Out_ LPRECT lpRect
		),
		ALL_A(_In_ HWND,
			_Out_ LPRECT
		),
		ALL_A(_In_ hWnd,
			_Out_ lpRect
		));

	CREATE_CALL(HCURSOR, WINAPI, _SetCursor, "SetCursor",
		ALL_A(_In_opt_ HCURSOR hCursor
		),
		ALL_A(_In_opt_ HCURSOR
		),
		ALL_A(_In_opt_ hCursor
		));

	CREATE_CALL(BOOL, WINAPI, _ImmSetCompositionWindow, "ImmSetCompositionWindow",
		ALL_A(IN HIMC hm, _In_ LPCOMPOSITIONFORM lpCompForm
		),
		ALL_A(IN HIMC, _In_ LPCOMPOSITIONFORM
		),
		ALL_A(IN hm, _In_ lpCompForm
		));

	CREATE_CALL(HIMC, WINAPI, _ImmGetContext, "ImmGetContext",
		ALL_A(IN HWND hw
		),
		ALL_A(IN HWND
		),
		ALL_A(IN hw
		));

	CREATE_CALL(HIMC, WINAPI, _WaitForSingleObject, "WaitForSingleObject",
		ALL_A(_In_ HANDLE hHandle,
			_In_ DWORD dwMilliseconds
		),
		ALL_A(_In_ HANDLE,
			_In_ DWORD
		),
		ALL_A(_In_ hHandle,
			_In_ dwMilliseconds
		));

	CREATE_CALL(int, WINAPI, _MultiByteToWideChar, "MultiByteToWideChar",
		ALL_A(_In_ UINT CodePage,
			_In_ DWORD dwFlags,
			_In_NLS_string_(cbMultiByte) LPCCH lpMultiByteStr,
			_In_ int cbMultiByte,
			_Out_writes_to_opt_(cchWideChar, return) LPWSTR lpWideCharStr,
			_In_ int cchWideChar
		),
		ALL_A(_In_ UINT,
			_In_ DWORD,
			_In_NLS_string_(cbMultiByte) LPCCH,
			_In_ int cbMultiByte,
			_Out_writes_to_opt_(cchWideChar, return) LPWSTR,
			_In_ int
		),
		ALL_A(_In_ CodePage,
			_In_ dwFlags,
			_In_NLS_string_(cbMultiByte) lpMultiByteStr,
			_In_ cbMultiByte,
			_Out_writes_to_opt_(cchWideChar, return) lpWideCharStr,
			_In_ cchWideChar
		));

	CREATE_CALL(ULONGLONG, WINAPI, _GetTickCount64, "GetTickCount64",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(DWORD, WINAPI, _GetLastError, "GetLastError",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	_Ret_maybenull_
		CREATE_CALL(HANDLE, WINAPI, _CreateEventA, "CreateEventA",
			ALL_A(_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
				_In_ BOOL bManualReset,
				_In_ BOOL bInitialState,
				_In_opt_ LPCSTR lpName
			),
			ALL_A(
				_In_opt_ LPSECURITY_ATTRIBUTES,
				_In_ BOOL,
				_In_ BOOL,
				_In_opt_ LPCSTR
			),
			ALL_A(_In_opt_ lpEventAttributes,
				_In_ bManualReset,
				_In_ bInitialState,
				_In_opt_ lpName
			));

	CREATE_CALL(SIZE_T, WINAPI, _VirtualQuery, "VirtualQuery",
		ALL_A(_In_opt_ LPCVOID lpAddress,
			_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
			_In_ SIZE_T dwLength
		),
		ALL_A(_In_opt_ LPCVOID,
			_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION,
			_In_ SIZE_T
		),
		ALL_A(_In_opt_ lpAddress,
			_Out_writes_bytes_to_(dwLength, return) lpBuffer,
			_In_ dwLength
		));

	CREATE_CALL(HANDLE, WINAPI, _FindFirstFileA, "FindFirstFileA",
		ALL_A(_In_ LPCSTR lpFileName,
			_Out_ LPWIN32_FIND_DATAA lpFindFileData
		),
		ALL_A(_In_ LPCSTR lpFileName,
			_Out_ LPWIN32_FIND_DATAA
		),
		ALL_A(_In_ lpFileName,
			_Out_ lpFindFileData
		));

	CREATE_CALL(BOOL, WINAPI, _FindNextFileA, "FindNextFileA",
		ALL_A(_In_ HANDLE hFindFile,
			_Out_ LPWIN32_FIND_DATAA lpFindFileData
		),
		ALL_A(_In_ HANDLE,
			_Out_ LPWIN32_FIND_DATAA
		),
		ALL_A(_In_ hFindFile,
			_Out_ lpFindFileData
		));



	CREATE_CALL(VOID, WINAPI, _GetLocalTime, "GetLocalTime",
		ALL_A(_Out_ LPSYSTEMTIME lpSystemTime
		),
		ALL_A(_Out_ LPSYSTEMTIME
		),
		ALL_A(_Out_ lpSystemTime
		));

	CREATE_CALL(VOID, WINAPI, _GetSystemTimeAsFileTime, "GetSystemTimeAsFileTime",
		ALL_A(_Out_ LPFILETIME lpSystemTimeAsFileTime
		),
		ALL_A(_Out_ LPFILETIME
		),
		ALL_A(_Out_ lpSystemTimeAsFileTime
		));

	//=========================

	CREATE_CALL(DWORD, WINAPI, _GetFullPathNameA, "GetFullPathNameA",
		ALL_A(_In_ LPCSTR lpFileName,
			_In_ DWORD nBufferLength,
			_Out_writes_to_opt_(nBufferLength, return +1) LPSTR lpBuffer,
			_Outptr_opt_ LPSTR* lpFilePart
		),
		ALL_A(_In_ LPCSTR,
			_In_ DWORD,
			_Out_writes_to_opt_(nBufferLength, return +1) LPSTR,
			_Outptr_opt_ LPSTR*
		),
		ALL_A(_In_ lpFileName,
			_In_ nBufferLength,
			_Out_writes_to_opt_(nBufferLength, return +1) lpBuffer,
			_Outptr_opt_ lpFilePart
		));

	CREATE_CALL(BOOL, WINAPI, _FindClose, "FindClose",
		ALL_A(_Inout_ HANDLE hFindFile
		),
		ALL_A(_Inout_ HANDLE
		),
		ALL_A(_Inout_ hFindFile
		));


	CREATE_CALL(BOOL, WINAPI, _DeleteFileA, "DeleteFileA",
		ALL_A(_In_ LPCSTR lpFileName
		),
		ALL_A(_In_ LPCSTR
		),
		ALL_A(_In_ lpFileName
		));

	CREATE_CALL(BOOL, WINAPI, _CreateDirectoryA, "CreateDirectoryA",
		ALL_A(_In_ LPCSTR lpPathName,
			_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
		),
		ALL_A(_In_ LPCSTR,
			_In_opt_ LPSECURITY_ATTRIBUTES
		),
		ALL_A(_In_ lpPathName,
			_In_opt_ lpSecurityAttributes
		));

	CREATE_CALL(BOOL, WINAPI, _SetEndOfFile, "SetEndOfFile",
		ALL_A(_In_ HANDLE hFile
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hFile
		));

	CREATE_CALL(HANDLE, WINAPI, _CreateFileW, "CreateFileW",
		ALL_A(_In_ LPCWSTR lpFileName,
			_In_ DWORD dwDesiredAccess,
			_In_ DWORD dwShareMode,
			_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
			_In_ DWORD dwCreationDisposition,
			_In_ DWORD dwFlagsAndAttributes,
			_In_opt_ HANDLE hTemplateFile
		),
		ALL_A(_In_ LPCWSTR,
			_In_ DWORD,
			_In_ DWORD,
			_In_opt_ LPSECURITY_ATTRIBUTES,
			_In_ DWORD,
			_In_ DWORD,
			_In_opt_ HANDLE
		),
		ALL_A(_In_ lpFileName,
			_In_ dwDesiredAccess,
			_In_ dwShareMode,
			_In_opt_ lpSecurityAttributes,
			_In_ dwCreationDisposition,
			_In_ dwFlagsAndAttributes,
			_In_opt_ hTemplateFile
		));

	CREATE_CALL(BOOL, WINAPI, _FindNextFileW, "FindNextFileW",
		ALL_A(_In_ HANDLE hFindFile,
			_Out_ LPWIN32_FIND_DATAW lpFindFileData
		),
		ALL_A(_In_ HANDLE,
			_Out_ LPWIN32_FIND_DATAW
		),
		ALL_A(_In_ hFindFile,
			_Out_ lpFindFileData
		));

	CREATE_CALL(HANDLE, WINAPI, _FindFirstFileExW, "FindFirstFileExW",
		ALL_A(_In_ LPCWSTR lpFileName,
			_In_ FINDEX_INFO_LEVELS fInfoLevelId,
			_Out_writes_bytes_(sizeof(WIN32_FIND_DATAW)) LPVOID lpFindFileData,
			_In_ FINDEX_SEARCH_OPS fSearchOp,
			_Reserved_ LPVOID lpSearchFilter,
			_In_ DWORD dwAdditionalFlags
		),
		ALL_A(_In_ LPCWSTR,
			_In_ FINDEX_INFO_LEVELS,
			_Out_writes_bytes_(sizeof(WIN32_FIND_DATAW)) LPVOID,
			_In_ FINDEX_SEARCH_OPS,
			_Reserved_ LPVOID,
			_In_ DWORD
		),
		ALL_A(_In_ lpFileName,
			_In_ fInfoLevelId,
			_Out_writes_bytes_(sizeof(WIN32_FIND_DATAW)) lpFindFileData,
			_In_ fSearchOp,
			_Reserved_ lpSearchFilter,
			_In_ dwAdditionalFlags
		));

	CREATE_CALL(BOOL, WINAPI, _SetFilePointerEx, "SetFilePointerEx",
		ALL_A(_In_ HANDLE hFile,
			_In_ LARGE_INTEGER liDistanceToMove,
			_Out_opt_ PLARGE_INTEGER lpNewFilePointer,
			_In_ DWORD dwMoveMethod
		),
		ALL_A(_In_ HANDLE,
			_In_ LARGE_INTEGER,
			_Out_opt_ PLARGE_INTEGER,
			_In_ DWORD
		),
		ALL_A(_In_ hFile,
			_In_ liDistanceToMove,
			_Out_opt_ lpNewFilePointer,
			_In_ dwMoveMethod
		));

	CREATE_CALL(BOOL, WINAPI, _FlushFileBuffers, "FlushFileBuffers",
		ALL_A(_In_ HANDLE hFile
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hFile
		));

	CREATE_CALL(DWORD, WINAPI, _GetFileType, "GetFileType",
		ALL_A(_In_ HANDLE hFile
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hFile
		));

	CREATE_CALL(BOOL, WINAPI, _WriteFile, "WriteFile",
		ALL_A(_In_ HANDLE hFile,
			_In_reads_bytes_opt_(nNumberOfBytesToWrite) LPCVOID lpBuffer,
			_In_ DWORD nNumberOfBytesToWrite,
			_Out_opt_ LPDWORD lpNumberOfBytesWritten,
			_Inout_opt_ LPOVERLAPPED lpOverlapped
		),
		ALL_A(_In_ HANDLE,
			_In_reads_bytes_opt_(nNumberOfBytesToWrite) LPCVOID,
			_In_ DWORD,
			_Out_opt_ LPDWORD,
			_Inout_opt_ LPOVERLAPPED
		),
		ALL_A(_In_ hFile,
			_In_reads_bytes_opt_(nNumberOfBytesToWrite) lpBuffer,
			_In_ nNumberOfBytesToWrite,
			_Out_opt_ lpNumberOfBytesWritten,
			_Inout_opt_ lpOverlapped
		));

	CREATE_CALL(BOOL, WINAPI, _ReadFile, "ReadFile",
		ALL_A(_In_ HANDLE hFile,
			_Out_writes_bytes_to_opt_(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) LPVOID lpBuffer,
			_In_ DWORD nNumberOfBytesToRead,
			_Out_opt_ LPDWORD lpNumberOfBytesRead,
			_Inout_opt_ LPOVERLAPPED lpOverlapped
		),
		ALL_A(_In_ HANDLE,
			_Out_writes_bytes_to_opt_(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) LPVOID,
			_In_ DWORD,
			_Out_opt_ LPDWORD,
			_Inout_opt_ LPOVERLAPPED
		),
		ALL_A(_In_ hFile,
			_Out_writes_bytes_to_opt_(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) lpBuffer,
			_In_ nNumberOfBytesToRead,
			_Out_opt_ lpNumberOfBytesRead,
			_Inout_opt_ lpOverlapped
		));

	CREATE_CALL(int, WINAPI, _lstrcmpiA, "lstrcmpiA",
		ALL_A(_In_ LPCSTR lpString1,
			_In_ LPCSTR lpString2
		),
		ALL_A(_In_ LPCSTR,
			_In_ LPCSTR
		),
		ALL_A(_In_ lpString1,
			_In_ lpString2
		));

	//===========================================

	void test2()
	{
		//InitializeCriticalSection
		//InitializeCriticalSectionAndSpinCount
		//EnterCriticalSection
		//SetEvent

	}

	CREATE_CALL(VOID, WINAPI, _Sleep, "Sleep",
		ALL_A(_In_ DWORD dwMilliseconds
		),
		ALL_A(_In_ DWORD
		),
		ALL_A(_In_ dwMilliseconds
		));

	CREATE_CALL(VOID, WINAPI, _EnterCriticalSection, "EnterCriticalSection",
		ALL_A(_Inout_ LPCRITICAL_SECTION lpCriticalSection
		),
		ALL_A(_Inout_ LPCRITICAL_SECTION
		),
		ALL_A(_Inout_ lpCriticalSection
		));

	CREATE_CALL(VOID, WINAPI, _LeaveCriticalSection, "LeaveCriticalSection",
		ALL_A(_Inout_ LPCRITICAL_SECTION lpCriticalSection
		),
		ALL_A(_Inout_ LPCRITICAL_SECTION
		),
		ALL_A(_Inout_ lpCriticalSection
		));

	CREATE_CALL(VOID, WINAPI, _DeleteCriticalSection, "DeleteCriticalSection",
		ALL_A(_Inout_ LPCRITICAL_SECTION lpCriticalSection
		),
		ALL_A(_Inout_ LPCRITICAL_SECTION
		),
		ALL_A(_Inout_ lpCriticalSection
		));

	CREATE_CALL(BOOL, WINAPI, _InitializeCriticalSectionAndSpinCount, "InitializeCriticalSectionAndSpinCount",
		ALL_A(_Out_ LPCRITICAL_SECTION lpCriticalSection,
			_In_ DWORD dwSpinCount
		),
		ALL_A(_Out_ LPCRITICAL_SECTION,
			_In_ DWORD
		),
		ALL_A(_Out_ lpCriticalSection,
			_In_ dwSpinCount
		));

	CREATE_CALL(HANDLE, WINAPI, _CreateEventW, "CreateEventW",
		ALL_A(_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
			_In_ BOOL bManualReset,
			_In_ BOOL bInitialState,
			_In_opt_ LPCWSTR lpName
		),
		ALL_A(_In_opt_ LPSECURITY_ATTRIBUTES,
			_In_ BOOL,
			_In_ BOOL,
			_In_opt_ LPCWSTR
		),
		ALL_A(_In_opt_ lpEventAttributes,
			_In_ bManualReset,
			_In_ bInitialState,
			_In_opt_ lpName
		));

	CREATE_CALL(VOID, WINAPI, _InitializeCriticalSection, "InitializeCriticalSection",
		ALL_A(_Out_ LPCRITICAL_SECTION lpCriticalSection
		),
		ALL_A(_Out_ LPCRITICAL_SECTION
		),
		ALL_A(_Out_ lpCriticalSection
		));

	CREATE_CALL(BOOL, WINAPI, _SetEvent, "SetEvent",
		ALL_A(_In_ HANDLE hEvent
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hEvent
		));

	CREATE_CALL(BOOL, WINAPI, _ResetEvent, "ResetEvent",
		ALL_A(_In_ HANDLE hEvent
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hEvent
		));

	CREATE_CALL(DWORD, WINAPI, _WaitForSingleObjectEx, "WaitForSingleObjectEx",
		ALL_A(_In_ HANDLE hHandle,
			_In_ DWORD dwMilliseconds,
			_In_ BOOL bAlertable
		),
		ALL_A(_In_ HANDLE,
			_In_ DWORD,
			_In_ BOOL
		),
		ALL_A(_In_ hHandle,
			_In_ dwMilliseconds,
			_In_ bAlertable
		));



	//===========================================

	CREATE_CALL(FARPROC, WINAPI, _GetProcAddress, "GetProcAddress",
		ALL_A(_In_ HMODULE hModule,
			_In_ LPCSTR lpProcName
		),
		ALL_A(_In_ HMODULE,
			_In_ LPCSTR
		),
		ALL_A(_In_ hModule,
			_In_ lpProcName
		));

	CREATE_CALL(HMODULE, WINAPI, _GetModuleHandleW, "GetModuleHandleW",
		ALL_A(_In_opt_ LPCWSTR lpModuleName
		),
		ALL_A(_In_opt_ LPCWSTR
		),
		ALL_A(_In_opt_ lpModuleName
		));

	CREATE_CALL(DWORD, WINAPI, _GetModuleFileNameA, "GetModuleFileNameA",
		ALL_A(_In_opt_ HMODULE hModule,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) LPSTR lpFilename,
			_In_ DWORD nSize
		),
		ALL_A(_In_opt_ HMODULE,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) LPSTR,
			_In_ DWORD
		),
		ALL_A(_In_opt_ hModule,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) lpFilename,
			_In_ nSize
		));

	CREATE_CALL(HMODULE, WINAPI, _GetModuleHandleA, "GetModuleHandleA",
		ALL_A(_In_opt_ LPCSTR lpModuleName
		),
		ALL_A(_In_opt_ LPCSTR
		),
		ALL_A(_In_opt_ lpModuleName
		));

	CREATE_CALL(DWORD, WINAPI, _GetModuleFileNameW, "GetModuleFileNameW",
		ALL_A(_In_opt_ HMODULE hModule,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) LPWSTR lpFilename,
			_In_ DWORD nSize
		),
		ALL_A(_In_opt_ HMODULE,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) LPWSTR,
			_In_ DWORD
		),
		ALL_A(_In_opt_ hModule,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) lpFilename,
			_In_ nSize
		));

	CREATE_CALL(BOOL, WINAPI, _GetModuleHandleExW, "GetModuleHandleExW",
		ALL_A(_In_ DWORD dwFlags,
			_In_opt_ LPCWSTR lpModuleName,
			_Out_ HMODULE* phModule
		),
		ALL_A(_In_ DWORD,
			_In_opt_ LPCWSTR,
			_Out_ HMODULE*
		),
		ALL_A(_In_ dwFlags,
			_In_opt_ lpModuleName,
			_Out_ phModule
		));

	CREATE_CALL(HMODULE, WINAPI, _LoadLibraryExW, "LoadLibraryExW",
		ALL_A(_In_ LPCWSTR lpLibFileName,
			_Reserved_ HANDLE hFile,
			_In_ DWORD dwFlags
		),
		ALL_A(_In_ LPCWSTR,
			_Reserved_ HANDLE,
			_In_ DWORD
		),
		ALL_A(_In_ lpLibFileName,
			_Reserved_ hFile,
			_In_ dwFlags
		));

	CREATE_CALL(BOOL, WINAPI, _FreeLibrary, "FreeLibrary",
		ALL_A(_In_ HMODULE hLibModule
		),
		ALL_A(_In_ HMODULE
		),
		ALL_A(_In_ hLibModule
		));

	//======================================

	void test3()
	{
		//WideCharToMultiByte
	}

	CREATE_CALL(BOOL, WINAPI, _IsBadCodePtr, "IsBadCodePtr", // исключение-норма
		ALL_A(_In_opt_ FARPROC lpfn
		),
		ALL_A(_In_opt_ FARPROC
		),
		ALL_A(_In_opt_ lpfn
		));

	CREATE_CALL(HGLOBAL, WINAPI, _GlobalAlloc, "GlobalAlloc",
		ALL_A(_In_ UINT uFlags,
			_In_ SIZE_T dwBytes
		),
		ALL_A(_In_ UINT,
			_In_ SIZE_T
		),
		ALL_A(_In_ uFlags,
			_In_ dwBytes
		));

	CREATE_CALL(LPVOID, WINAPI, _GlobalLock, "GlobalLock",
		ALL_A(_In_ HGLOBAL hMem
		),
		ALL_A(_In_ HGLOBAL
		),
		ALL_A(_In_ hMem
		));

	CREATE_CALL(BOOL, WINAPI, _GlobalUnlock, "GlobalUnlock",
		ALL_A(_In_ HGLOBAL hMem
		),
		ALL_A(_In_ HGLOBAL
		),
		ALL_A(_In_ hMem
		));

	CREATE_CALL(int, WINAPI, _lstrlenA, "lstrlenA",
		ALL_A(_In_ LPCSTR lpString
		),
		ALL_A(_In_ LPCSTR
		),
		ALL_A(_In_ lpString
		));

	//CREATE_CALL(BOOL, WINAPI, _IsBadReadPtr, "IsBadReadPtr",
	//	ALL_A(_In_opt_ CONST VOID *lp,
	//		_In_     UINT_PTR ucb
	//	),
	//	ALL_A(_In_opt_ CONST VOID,
	//		_In_     UINT_PTR
	//	),
	//	ALL_A(_In_opt_ CONST lp,
	//		_In_     ucb
	//	));

	CREATE_CALL(int, WINAPI, _WideCharToMultiByte, "WideCharToMultiByte",
		ALL_A(_In_ UINT CodePage,
			_In_ DWORD dwFlags,
			_In_NLS_string_(cchWideChar) LPCWCH lpWideCharStr,
			_In_ int cchWideChar,
			_Out_writes_bytes_to_opt_(cbMultiByte, return) LPSTR lpMultiByteStr,
			_In_ int cbMultiByte,
			_In_opt_ LPCCH lpDefaultChar,
			_Out_opt_ LPBOOL lpUsedDefaultChar
		),
		ALL_A(_In_ UINT,
			_In_ DWORD,
			_In_NLS_string_(cchWideChar) LPCWCH,
			_In_ int,
			_Out_writes_bytes_to_opt_(cbMultiByte, return) LPSTR,
			_In_ int,
			_In_opt_ LPCCH,
			_Out_opt_ LPBOOL
		),
		ALL_A(_In_ CodePage,
			_In_ dwFlags,
			_In_NLS_string_(cchWideChar) lpWideCharStr,
			_In_ cchWideChar,
			_Out_writes_bytes_to_opt_(cbMultiByte, return) lpMultiByteStr,
			_In_ cbMultiByte,
			_In_opt_ lpDefaultChar,
			_Out_opt_ lpUsedDefaultChar
		));

	CREATE_CALL(BOOL, WINAPI, _GetStringTypeW, "GetStringTypeW",
		ALL_A(_In_ DWORD dwInfoType,
			_In_NLS_string_(cchSrc) LPCWCH lpSrcStr,
			_In_ int cchSrc,
			_Out_ LPWORD lpCharType
		),
		ALL_A(_In_ DWORD,
			_In_NLS_string_(cchSrc) LPCWCH,
			_In_ int,
			_Out_ LPWORD
		),
		ALL_A(_In_ dwInfoType,
			_In_NLS_string_(cchSrc) lpSrcStr,
			_In_ cchSrc,
			_Out_ lpCharType
		));

	CREATE_CALL(int, WINAPI, _CompareStringW, "CompareStringW",
		ALL_A(_In_ LCID Locale,
			_In_ DWORD dwCmpFlags,
			_In_NLS_string_(cchCount1) PCNZWCH lpString1,
			_In_ int cchCount1,
			_In_NLS_string_(cchCount2) PCNZWCH lpString2,
			_In_ int cchCount2
		),
		ALL_A(_In_ LCID,
			_In_ DWORD,
			_In_NLS_string_(cchCount1) PCNZWCH,
			_In_ int,
			_In_NLS_string_(cchCount2) PCNZWCH,
			_In_ int
		),
		ALL_A(_In_ Locale,
			_In_ dwCmpFlags,
			_In_NLS_string_(cchCount1) lpString1,
			_In_ cchCount1,
			_In_NLS_string_(cchCount2) lpString2,
			_In_ cchCount2
		));


	CREATE_CALL(PVOID, WINAPI, _AddVectoredExceptionHandler, "AddVectoredExceptionHandler",
		ALL_A(_In_ ULONG First,
			_In_ PVECTORED_EXCEPTION_HANDLER Handler
		),
		ALL_A(_In_ ULONG,
			_In_ PVECTORED_EXCEPTION_HANDLER
		),
		ALL_A(_In_ First,
			_In_ Handler
		));

	/*CREATE_CALL(VOID, WINAPI, _RaiseException, "RaiseException",
		ALL_A(_In_ DWORD dwExceptionCode,
			_In_ DWORD dwExceptionFlags,
			_In_ DWORD nNumberOfArguments,
			_In_reads_opt_(nNumberOfArguments) CONST ULONG_PTR* lpArguments
		),
		ALL_A(_In_ DWORD,
			_In_ DWORD,
			_In_ DWORD,
			_In_reads_opt_(nNumberOfArguments) CONST ULONG_PTR*
		),
		ALL_A(_In_ dwExceptionCode,
			_In_ dwExceptionFlags,
			_In_ nNumberOfArguments,
			_In_reads_opt_(nNumberOfArguments) CONST lpArguments
		));*/

	CREATE_CALL(VOID, WINAPI, _SetLastError, "SetLastError",
		ALL_A(_In_ DWORD dwErrCode
		),
		ALL_A(_In_ DWORD
		),
		ALL_A(_In_ dwErrCode
		));

	//CREATE_CALL(LONG, WINAPI, _UnhandledExceptionFilter, "UnhandledExceptionFilter",
	//	ALL_A(_In_ struct _EXCEPTION_POINTERS* ExceptionInfo
	//	),
	//	ALL_A(_In_ struct _EXCEPTION_POINTERS*
	//	),
	//	ALL_A(_In_ struct ExceptionInfo
	//	));

	//CREATE_CALL(RETLIF_NOITP, WINAPI, _SetUnhandledExceptionFilter, "SetUnhandledExceptionFilter",
	//	ALL_A(_In_opt_ LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter
	//	),
	//	ALL_A(_In_opt_ LPTOP_LEVEL_EXCEPTION_FILTER
	//	),
	//	ALL_A(_In_opt_ lpTopLevelExceptionFilter
	//	));

	CREATE_CALL(BOOL, WINAPI, _Beep, "Beep",
		ALL_A(_In_ DWORD dwFreq,
			_In_ DWORD dwDuration
		),
		ALL_A(_In_ DWORD,
			_In_ DWORD
		),
		ALL_A(_In_ dwFreq,
			_In_ dwDuration
		));

	CREATE_CALL(PVOID, WINAPI, _EncodePointer, "EncodePointer",
		ALL_A(_In_opt_ PVOID Ptr
		),
		ALL_A(_In_opt_ PVOID
		),
		ALL_A(_In_opt_ Ptr
		));

	CREATE_CALL(PVOID, WINAPI, _DecodePointer, "DecodePointer",
		ALL_A(_In_opt_ PVOID Ptr
		),
		ALL_A(_In_opt_ PVOID
		),
		ALL_A(_In_opt_ Ptr
		));


	CREATE_CALL(HANDLE, WINAPI, _GetCurrentThread, "GetCurrentThread",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(BOOL, WINAPI, _TerminateProcess, "TerminateProcess",
		ALL_A(_In_ HANDLE hProcess,
			_In_ UINT uExitCode
		),
		ALL_A(_In_ HANDLE,
			_In_ UINT
		),
		ALL_A(_In_ hProcess,
			_In_ uExitCode
		));

	CREATE_CALL(HANDLE, WINAPI, _GetCurrentProcess, "GetCurrentProcess",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(VOID, WINAPI, _ExitProcess, "ExitProcess",
		ALL_A(_In_ UINT uExitCode
		),
		ALL_A(_In_ UINT
		),
		ALL_A(_In_ uExitCode
		));

	CREATE_CALL(DWORD, WINAPI, _GetCurrentThreadId, "GetCurrentThreadId",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(BOOL, WINAPI, _SwitchToThread, "SwitchToThread",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(DWORD, WINAPI, _TlsAlloc, "TlsAlloc",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(LPVOID, WINAPI, _TlsGetValue, "TlsGetValue",
		ALL_A(_In_ DWORD dwTlsIndex
		),
		ALL_A(_In_ DWORD
		),
		ALL_A(_In_ dwTlsIndex
		));

	CREATE_CALL(BOOL, WINAPI, _TlsSetValue, "TlsSetValue",
		ALL_A(_In_ DWORD dwTlsIndex,
			_In_opt_ LPVOID lpTlsValue
		),
		ALL_A(_In_ DWORD,
			_In_opt_ LPVOID
		),
		ALL_A(_In_ dwTlsIndex,
			_In_opt_ lpTlsValue
		));

	CREATE_CALL(BOOL, WINAPI, _TlsFree, "TlsFree",
		ALL_A(_In_ DWORD dwTlsIndex
		),
		ALL_A(_In_ DWORD
		),
		ALL_A(_In_ dwTlsIndex
		));

	CREATE_CALL(BOOL, WINAPI, _IsProcessorFeaturePresent, "IsProcessorFeaturePresent",
		ALL_A(_In_ DWORD ProcessorFeature
		),
		ALL_A(_In_ DWORD
		),
		ALL_A(_In_ ProcessorFeature
		));

	CREATE_CALL(VOID, WINAPI, _GetStartupInfoW, "GetStartupInfoW",
		ALL_A(_Out_ LPSTARTUPINFOW lpStartupInfo
		),
		ALL_A(_Out_ LPSTARTUPINFOW
		),
		ALL_A(_Out_ lpStartupInfo
		));

	CREATE_CALL(DWORD, WINAPI, _GetCurrentProcessId, "GetCurrentProcessId",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));


	CREATE_CALL(BOOL, WINAPI, _QueryPerformanceFrequency, "QueryPerformanceFrequency",
		ALL_A(_Out_ LARGE_INTEGER* lpFrequency
		),
		ALL_A(_Out_ LARGE_INTEGER*
		),
		ALL_A(_Out_ lpFrequency
		));

	CREATE_CALL(BOOL, WINAPI, _QueryPerformanceCounter, "QueryPerformanceCounter",
		ALL_A(_Out_ LARGE_INTEGER* lpPerformanceCount
		),
		ALL_A(_Out_ LARGE_INTEGER*
		),
		ALL_A(_Out_ lpPerformanceCount
		));


	CREATE_CALL(SIZE_T, WINAPI, _HeapSize, "HeapSize",
		ALL_A(_In_ HANDLE hHeap,
			_In_ DWORD dwFlags,
			_In_ LPCVOID lpMem
		),
		ALL_A(_In_ HANDLE,
			_In_ DWORD,
			_In_ LPCVOID
		),
		ALL_A(_In_ hHeap,
			_In_ dwFlags,
			_In_ lpMem
		));

	CREATE_CALL(HANDLE, WINAPI, _GetProcessHeap, "GetProcessHeap",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(LPVOID, WINAPI, _HeapAlloc, "HeapAlloc",
		ALL_A(_In_ HANDLE hHeap,
			_In_ DWORD dwFlags,
			_In_ SIZE_T dwBytes
		),
		ALL_A(_In_ HANDLE,
			_In_ DWORD,
			_In_ SIZE_T
		),
		ALL_A(_In_ hHeap,
			_In_ dwFlags,
			_In_ dwBytes
		));

	CREATE_CALL(LPVOID, WINAPI, _HeapReAlloc, "HeapReAlloc",
		ALL_A(_Inout_ HANDLE hHeap,
			_In_ DWORD dwFlags,
			_Frees_ptr_opt_ LPVOID lpMem,
			_In_ SIZE_T dwBytes
		),
		ALL_A(_Inout_ HANDLE,
			_In_ DWORD,
			_Frees_ptr_opt_ LPVOID,
			_In_ SIZE_T
		),
		ALL_A(_Inout_ hHeap,
			_In_ dwFlags,
			_Frees_ptr_opt_ lpMem,
			_In_ dwBytes
		));

	CREATE_CALL(BOOL, WINAPI, _HeapFree, "HeapFree",
		ALL_A(_Inout_ HANDLE hHeap,
			_In_ DWORD dwFlags,
			__drv_freesMem(Mem) _Frees_ptr_opt_ LPVOID lpMem
		),
		ALL_A(_Inout_ HANDLE,
			_In_ DWORD,
			__drv_freesMem(Mem) _Frees_ptr_opt_ LPVOID
		),
		ALL_A(_Inout_ hHeap,
			_In_ dwFlags,
			__drv_freesMem(Mem) _Frees_ptr_opt_ lpMem
		));


	CREATE_CALL(LONG, WINAPI, _SetWindowLongA, "SetWindowLongA",
		ALL_A(_In_ HWND hWnd,
			_In_ int nIndex,
			_In_ LONG dwNewLong
		),
		ALL_A(_In_ HWND,
			_In_ int,
			_In_ LONG
		),
		ALL_A(_In_ hWnd,
			_In_ nIndex,
			_In_ dwNewLong
		));

	CREATE_CALL(SHORT, WINAPI, _GetKeyState, "GetKeyState",
		ALL_A(_In_ int nVirtKey
		),
		ALL_A(_In_ int
		),
		ALL_A(_In_ nVirtKey
		));

	CREATE_CALL(HANDLE, WINAPI, _GetClipboardData, "GetClipboardData",
		ALL_A(_In_ UINT uFormat
		),
		ALL_A(_In_ UINT
		),
		ALL_A(_In_ uFormat
		));

	CREATE_CALL(BOOL, WINAPI, _OpenClipboard, "OpenClipboard",
		ALL_A(_In_opt_ HWND hWndNewOwner
		),
		ALL_A(_In_opt_ HWND
		),
		ALL_A(_In_opt_ hWndNewOwner
		));

	CREATE_CALL(BOOL, WINAPI, _CloseClipboard, "CloseClipboard",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(SHORT, WINAPI, _GetAsyncKeyState, "GetAsyncKeyState",
		ALL_A(_In_ int vKey
		),
		ALL_A(_In_ int
		),
		ALL_A(_In_ vKey
		));

	CREATE_CALL(BOOL, WINAPI, _GetCursorPos, "GetCursorPos",
		ALL_A(_Out_ LPPOINT lpPoint
		),
		ALL_A(_Out_ LPPOINT
		),
		ALL_A(_Out_ lpPoint
		));

	CREATE_CALL(HANDLE, WINAPI, _SetClipboardData, "SetClipboardData",
		ALL_A(_In_ UINT uFormat,
			_In_opt_ HANDLE hMem
		),
		ALL_A(_In_ UINT,
			_In_opt_ HANDLE
		),
		ALL_A(_In_ uFormat,
			_In_opt_ hMem
		));

	CREATE_CALL(BOOL, WINAPI, _EmptyClipboard, "EmptyClipboard",
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(LRESULT, WINAPI, _CallWindowProcA, "CallWindowProcA",
		ALL_A(_In_ WNDPROC lpPrevWndFunc,
			_In_ HWND hWnd,
			_In_ UINT Msg,
			_In_ WPARAM wParam,
			_In_ LPARAM lParam
		),
		ALL_A(_In_ WNDPROC,
			_In_ HWND,
			_In_ UINT,
			_In_ WPARAM,
			_In_ LPARAM
		),
		ALL_A(_In_ lpPrevWndFunc,
			_In_ hWnd,
			_In_ Msg,
			_In_ wParam,
			_In_ lParam
		));

};
