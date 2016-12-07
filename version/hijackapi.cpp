#include "stdafx.h"
#include "hijackapi.h"

HMODULE g_hModule = nullptr;

BOOL WINAPI LoadOrigin()
{
    g_hModule = LoadLibrary(ORIGIN_DLL_PATH);
    return (g_hModule != nullptr);
}

VOID WINAPI FreeOrigin()
{
    if (g_hModule != nullptr)
    {
        FreeLibrary(g_hModule);
        g_hModule = nullptr;
    }
}

FARPROC WINAPI GetAddress(LPCSTR pszProcName)
{
    return GetProcAddress(g_hModule, pszProcName);
}