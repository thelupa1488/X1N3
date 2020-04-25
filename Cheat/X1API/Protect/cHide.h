#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>
#include "../../Include/Def.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace std;


class cHideClass
{
public:
	virtual HRESULT _D3DXCreateFont(LPDIRECT3DDEVICE9 pDevice, INT Height, UINT Width, UINT Weight, UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCSTR pFaceName, LPD3DXFONT * ppFont);
	virtual HRESULT _D3DXCreateLine(LPDIRECT3DDEVICE9 pDevice, LPD3DXLINE* ppLine);
	virtual int _atoi(const char *s);
	virtual inline char * _strstr(const char *source, const char *word);
	virtual int str_cmp(const char * str1, const char * str2);
	virtual int str_len(const char *str);
	virtual std::wstring UTF8ToWstring(const std::string& str);
	virtual std::wstring AnsiToWstring(const std::string& input, DWORD locale /*= CP_ACP*/);
	virtual FARPROC _GetProcAddress(HMODULE hModule, const char* lpProcName);
	virtual PVOID _GetLibraryProcAddress(const char* LibraryName, const char *ProcName);
	virtual HMODULE _GetModulehandle(const wchar_t* szModule);
	virtual BOOL _SetRect(_Out_ LPRECT lprc, _In_ int xLeft, _In_ int yTop, _In_ int xRight, _In_ int yBottom);
	virtual int _MessageBox(HWND hWnd, LPCSTR MbString, LPCSTR lpCaption, UINT uType);
	virtual void _ExitProcess(UINT uExitCode);
	virtual BOOL _GetCursorPos(LPPOINT lpPoint);
	virtual BOOL _ScreenToClient(HWND hWnd, LPPOINT lpPoint);
	virtual HWND _GetForegroundWindow();
	virtual SHORT _GetKeyState(int nVirtKey);
	virtual SHORT _GetAsyncKeyState(int vKey);
	HANDLE NtCreateThreadEx(void* InRemoteThreadStart, void* InRemoteCallback);
};
extern cHideClass pHideMe;

class CreateThread_
{
public:
	CreateThread_(void* func, HINSTANCE hInst);
	bool HideThread(HANDLE hThread);
private:
	HANDLE hHandle;
};

typedef DWORD WINAPI NtCreateThreadEx_PROC(
	PHANDLE ThreadHandle,
	ACCESS_MASK DesiredAccess,
	LPVOID ObjectAttributes,
	HANDLE ProcessHandle,
	LPTHREAD_START_ROUTINE lpStartAddress,
	LPVOID lpParameter,
	BOOL CreateSuspended,
	DWORD dwStackSize,
	LPVOID Unknown1,
	LPVOID Unknown2,
	LPVOID Unknown3
);

typedef struct _UNICODE_STRING_
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING_, *PUNICODE_STRING_;

typedef struct _LDR_MODULE_
{
	LIST_ENTRY      InLoadOrderModuleList;
	LIST_ENTRY      InMemoryOrderModuleList;
	LIST_ENTRY      InInitializationOrderModuleList;
	PVOID           BaseAddress;
	PVOID           EntryPoint;
	ULONG           SizeOfImage;
	UNICODE_STRING_  FullDLLName;
	UNICODE_STRING_  BaseDLLName;
	ULONG           Flags;
	SHORT           LoadCount;
	SHORT           TlsIndex;
	LIST_ENTRY      HashTableEntry;
	ULONG           TimeDateStamp;
}LDR_MODULE_, *PLDR_MODULE_;

using nD3DXCreateFont = HRESULT(WINAPI*)(
	LPDIRECT3DDEVICE9       pDevice,
	INT                     Height,
	UINT                    Width,
	UINT                    Weight,
	UINT                    MipLevels,
	BOOL                    Italic,
	DWORD                   CharSet,
	DWORD                   OutputPrecision,
	DWORD                   Quality,
	DWORD                   PitchAndFamily,
	LPCSTR                  pFaceName,
	LPD3DXFONT*             ppFont);

typedef HRESULT(WINAPI*nD3DXCreateLine)(
	LPDIRECT3DDEVICE9   pDevice,
	LPD3DXLINE*         ppLine);

using nSetRect = BOOL(WINAPI*)(_Out_ LPRECT, _In_ int, _In_ int, _In_ int, _In_ int);
using nMessageBoxTimeoutA = int(WINAPI*)(HWND hWnd, LPCSTR MbString, LPCSTR lpCaption, UINT uType, int a5, int a6);
using nGetCursorPos = BOOL(WINAPI*)(__out LPPOINT lpPoint);
using nScreenToClient = BOOL(WINAPI*)(HWND hWnd, LPPOINT lpPoint);
using nGetForegroundWindow = HWND(WINAPI*)();
using nGetKeyState = SHORT(WINAPI*)(int nVirtKey);
using nGetAsyncKeyState = SHORT(WINAPI*)(int vKey);
using nExitProcess = void(WINAPI*)(UINT);

static std::vector<std::string>ModName = { XorStr("D3DX9_43.dll"), XorStr("USER32.dll"), XorStr("ntdll.dll") };
enum ModName_text { D3DX9_43, USER32, ntdll };

static std::vector<std::string>Funcname = 
{
	XorStr("D3DXCreateFontA"),//0
	XorStr("D3DXCreateLine"),//1
	XorStr("SetRect"),//2
	XorStr("MessageBoxTimeoutA"),//3
	XorStr("GetCursorPos"),//4
	XorStr("ScreenToClient"),//5
	XorStr("GetForegroundWindow"),//6
	XorStr("GetKeyState"),//7
	XorStr("GetAsyncKeyState"),//8
	XorStr("RtlExitUserProcess"),//9
	XorStr("NtCreateThreadEx"),//10
};






