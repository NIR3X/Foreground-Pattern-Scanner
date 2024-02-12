#include "FastPatternsScanner.cpp/FastPatternsScanner.h"
#include "FileMapping.cpp/FileMapping.h"
#include <psapi.h>
#include <iostream>

static __forceinline std::wstring GetFilePathByWindow(HWND hWnd) {
	DWORD pid;
	GetWindowThreadProcessId(hWnd, &pid);

	HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (!hProc) {
		return {};
	}

	std::wstring path = {};
	path.resize(MAX_PATH);
	path.resize(GetModuleFileNameExW(hProc, NULL, path.data(), MAX_PATH));
	CloseHandle(hProc);
	return path;
}

int main() {
	CFastPatternsScanner fastPatternsScanner({
		{
			77,101,109,111,114,121,32,83,99,97,110,32,79,112,116,105,111,110,115
		}, // Cheat Engine
		{
			80,114,111,99,101,115,115,32,116,101,114,109,105,110,97,116,105,111,110,
			32,119,97,115,32,114,101,113,117,101,115,116,101,100,32,105,110,32,97,
			110,32,117,110,117,115,117,97,108,32,119,97,121,46,32,80,114,111,103,
			114,97,109,32,119,105,108,108,32,110,111,119,32,103,101,110,101,114,97,
			116,101,32,97,110,32,101,120,99,101,112,116,105,111,110
		}, // x64dbg
		{
			70,0,105,0,110,0,100,0,32,0,104,0,97,0,110,0,100,0,108,0,101,0,115,0,32,
			0,111,0,114,0,32,0,68,0,76,0,76,0,115,0
		}, // Process Hacker
		{
			68,101,98,117,103,103,105,110,103,32,111,112,116,105,111,110,115
		}, // OllyDbg
		{
			65,0,116,0,116,0,97,0,99,0,104,0,32,0,116,0,111,0,32,0,97,0,110,0,32,0,
			97,0,99,0,116,0,105,0,118,0,101,0,32,0,112,0,114,0,111,0,99,0,101,0,115,
			0,115,0
		}, // Scylla
		{
			85,110,104,105,100,101,32,99,111,108,108,97,112,115,101,100,32,105,116,
			101,109,115,32,97,117,116,111,109,97,116,105,99,97,108,108,121,32,119,
			104,101,110,32,106,117,109,112,105,110,103,32,116,111,32,116,104,101,109
		}, // IDA
		{
			109,97,115,116,101,114,49,51,49
		}, // Extreme Injector v3
		{
			65,116,116,101,109,112,116,32,116,111,32,104,105,100,101,32,116,104,101,
			32,100,101,98,117,103,103,101,114,32,102,114,111,109,32,80,69,66
		}, // CrySearch
		{
			83,0,111,0,102,0,116,0,119,0,97,0,114,0,101,0,32,0,116,0,111,0,32,0,109,
			0,111,0,100,0,32,0,118,0,105,0,100,0,101,0,111,0,32,0,103,0,97,0,109,0,
			101,0,115,0
		}, // Squalr
		{
			34,79,110,108,121,32,112,101,114,102,111,114,109,32,99,111,110,116,114,
			111,108,32,102,108,111,119,32,97,110,97,108,121,115,105,115,32,111,110,
			32,116,104,101,32,98,105,110,97,114,121,46,32,67,114,111,115,115,32,114,
			101,102,101,114,101,110,99,101,115,32,97,114,101,32,118,97,108,105,100,
			32,111,110,108,121,32,102,111,114,32,100,105,114,101,99,116,32,102,117,
			110,99,116,105,111,110,32,99,97,108,108,115,46,32,91,68,105,115,97,115,
			115,101,109,98,108,121,32,79,110,108,121,93,34
		} // Binary Ninja
	});

	HWND prevHWnd = NULL;
	for (;;) {
		HWND currHWnd = GetForegroundWindow();
		if (prevHWnd != currHWnd) {
			prevHWnd = currHWnd;
			std::wstring filePath = GetFilePathByWindow(currHWnd);
			CFileMapping fileMapping(filePath);
			if (LPVOID fileMapView = fileMapping.getMapView()) {
				if (fastPatternsScanner.ContainsAny((const uint8_t*)fileMapView, fileMapping.getFileSize()).size() > 0) {
					std::wcout << filePath << std::endl;
					// e.g. Ban HWID here
				}
			}
		}
		Sleep(1);
	}
}
