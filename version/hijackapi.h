#ifndef __HIJACKAPI_H__
#define __HIJACKAPI_H__

#define ORIGIN_DLL_PATH _T("C:\\Windows\\System32\\Version.dll")
#define ALCDECL extern "C" __declspec(naked) void __cdecl

extern HMODULE g_hModule;
BOOL WINAPI LoadOrigin();
VOID WINAPI FreeOrigin();
FARPROC WINAPI GetAddress(LPCSTR pszProcName);

#endif