//Generate by DLLHijacker.py

#include <Windows.h>
//#include "../mhook/mhook-lib/mhook.h"
#include "detours.h"
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=_DLLHijacker_GetFileVersionInfoA,@1")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=_DLLHijacker_GetFileVersionInfoByHandle,@2")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=_DLLHijacker_GetFileVersionInfoExA,@3")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=_DLLHijacker_GetFileVersionInfoExW,@4")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=_DLLHijacker_GetFileVersionInfoSizeA,@5")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=_DLLHijacker_GetFileVersionInfoSizeExA,@6")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=_DLLHijacker_GetFileVersionInfoSizeExW,@7")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=_DLLHijacker_GetFileVersionInfoSizeW,@8")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=_DLLHijacker_GetFileVersionInfoW,@9")
#pragma comment(linker, "/EXPORT:VerFindFileA=_DLLHijacker_VerFindFileA,@10")
#pragma comment(linker, "/EXPORT:VerFindFileW=_DLLHijacker_VerFindFileW,@11")
#pragma comment(linker, "/EXPORT:VerInstallFileA=_DLLHijacker_VerInstallFileA,@12")
#pragma comment(linker, "/EXPORT:VerInstallFileW=_DLLHijacker_VerInstallFileW,@13")
#pragma comment(linker, "/EXPORT:VerLanguageNameA=_DLLHijacker_VerLanguageNameA,@14")
#pragma comment(linker, "/EXPORT:VerLanguageNameW=_DLLHijacker_VerLanguageNameW,@15")
#pragma comment(linker, "/EXPORT:VerQueryValueA=_DLLHijacker_VerQueryValueA,@16")
#pragma comment(linker, "/EXPORT:VerQueryValueW=_DLLHijacker_VerQueryValueW,@17")

#define EXTERNC extern "C"
#define NAKED __declspec(naked)
#define EXPORT __declspec(dllexport)
#define ALCPP EXPORT NAKED
#define ALSTD EXTERNC EXPORT NAKED void __stdcall
#define ALCFAST EXTERNC EXPORT NAKED void __fastcall
#define ALCDECL EXTERNC NAKED void __cdecl

HMODULE m_hModule = NULL;
DWORD m_dwReturn[17] = {0};
inline BOOL WINAPI Load()
{
    TCHAR tzPath[MAX_PATH];
    lstrcpy(tzPath, TEXT("C:\\Windows\\System32\\Version.dll"));
    m_hModule = LoadLibrary(tzPath);
    if (m_hModule == NULL)
        return FALSE;
    return (m_hModule != NULL);
}

inline VOID WINAPI Free()
{
    if (m_hModule)
        FreeLibrary(m_hModule);
}

FARPROC WINAPI GetAddress(PCSTR pszProcName)
{
    FARPROC fpAddress;
    CHAR szProcName[16];
    fpAddress = GetProcAddress(m_hModule, pszProcName);
    if (fpAddress == NULL)
    {
        if (HIWORD(pszProcName) == 0)
        {
            wsprintfA(szProcName, "%d", pszProcName);
            pszProcName = szProcName;
        }
        ExitProcess(-2);
    }

    return fpAddress;
}

typedef int (WINAPI* _MessageBoxW)(
    _In_opt_ HWND    hWnd,
    _In_opt_ LPCWSTR lpText,
    _In_opt_ LPCWSTR lpCaption,
    _In_     UINT    uType
    );

_MessageBoxW TrueMessageBoxW = (_MessageBoxW)GetProcAddress(GetModuleHandle(L"user32"), "MessageBoxW");

typedef int (WINAPI* _MessageBoxIndirectW)(
    _In_ const LPMSGBOXPARAMSW lpMsgBoxParams
    );

_MessageBoxIndirectW TrueMessageBoxIndirectW = (_MessageBoxIndirectW)GetProcAddress(GetModuleHandle(L"user32"), "MessageBoxIndirectW");


typedef HMODULE (WINAPI* _LoadLibraryExW)(
    _In_       LPCWSTR lpFileName,
    _Reserved_ HANDLE  hFile,
    _In_       DWORD   dwFlags
);

_LoadLibraryExW TrueLoadLibraryExW = (_LoadLibraryExW)GetProcAddress(GetModuleHandle(L"kernel32"), "LoadLibraryExW");

int WINAPI HookMessageBoxW(
    _In_opt_ HWND    hWnd,
    _In_opt_ LPCWSTR lpText,
    _In_opt_ LPCWSTR lpCaption,
    _In_     UINT    uType
    )
{
    return TrueMessageBoxW(hWnd, lpText, L"你被hook了！！！！", uType);
}

int WINAPI HookMessageBoxIndirectW(
    _In_ const LPMSGBOXPARAMSW lpMsgBoxParams
    )
{
    return TrueMessageBoxIndirectW(lpMsgBoxParams);
}

typedef struct _stack_t
{
    struct _stack_t *next;      // 指向下一个堆栈结构的指针
    TCHAR text[1];              // 参数（字符串长度为string_size）
} stack_t;

typedef void(__cdecl* _Call)(HWND hwndParent, int string_size, wchar_t *variables, stack_t **stacktop, void *extra);

_Call TrueCall = nullptr;

void __cdecl HookCall(HWND hwndParent, int string_size, wchar_t *variables, stack_t **stacktop, void *extra)
{
    if (stacktop != nullptr)
    {
        OutputDebugStringW(L"-------------------------->");
        OutputDebugStringW((*stacktop)->text);
    }

    TrueCall(hwndParent, string_size, variables, stacktop, extra);
}

HMODULE WINAPI HookLoadLibraryExW(
    _In_       LPCWSTR lpFileName,
    _Reserved_ HANDLE  hFile,
    _In_       DWORD   dwFlags
    )
{
    HMODULE hModule = TrueLoadLibraryExW(lpFileName, hFile, dwFlags);
    
    LPWSTR fileName = ::PathFindFileNameW(lpFileName);
    WCHAR szSystem[] = L"system.dll";
    //if (fileName[0] == L'S' &&
    //    fileName[1] == L'y' &&
    //    fileName[2] == L's' &&
    //    fileName[3] == L't' &&
    //    fileName[4] == L'e' &&
    //    fileName[5] == L'm' &&
    //    fileName[6] == L'.' &&
    //    fileName[7] == L'd' &&
    //    fileName[8] == L'l' &&
    //    fileName[9] == L'l')
        if (lstrcmpiW(fileName, szSystem) == 0)
    {
        //OutputDebugStringW(L"----------------------------------------->");
        //OutputDebugStringW(fileName);
        //MessageBoxW(0, lpFileName, 0, 0);
        TrueCall = (_Call) GetProcAddress(hModule, "Call");
        //Mhook_SetHook((PVOID*)&TrueCall, HookCall);
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)TrueCall, HookCall);
        DetourTransactionCommit();
    }

    return hModule;
}

VOID Hijack()
{
    //MessageBoxW(NULL, L"DLL Hijack! by DLLHijacker", L":)", 0);

    //Mhook_SetHook((PVOID*)&TrueMessageBoxW, HookMessageBoxW);
    //Mhook_SetHook((PVOID*)&TrueMessageBoxIndirectW, HookMessageBoxIndirectW);
    //Mhook_SetHook((PVOID*)&TrueLoadLibraryExW, HookLoadLibraryExW);
    //{
   //     MessageBoxW(0, L"999", L"888", 0);
        //Mhook_Unhook((PVOID*)&TrueMessageBoxW);
    //}

    DetourRestoreAfterWith();

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)TrueLoadLibraryExW, HookLoadLibraryExW);
    DetourTransactionCommit();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
    if (DetourIsHelperProcess())
    {
        return TRUE;
    }

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        if (Load())
            Hijack();
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        Free();

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)TrueLoadLibraryExW, HookLoadLibraryExW);
        DetourTransactionCommit();
    }

    return TRUE;
}

ALCDECL DLLHijacker_GetFileVersionInfoA(void)
{
    GetAddress("GetFileVersionInfoA");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_GetFileVersionInfoByHandle(void)
{
    GetAddress("GetFileVersionInfoByHandle");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_GetFileVersionInfoExA(void)
{
    GetAddress("GetFileVersionInfoExA");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_GetFileVersionInfoExW(void)
{
    GetAddress("GetFileVersionInfoExW");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_GetFileVersionInfoSizeA(void)
{
    GetAddress("GetFileVersionInfoSizeA");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_GetFileVersionInfoSizeExA(void)
{
    GetAddress("GetFileVersionInfoSizeExA");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_GetFileVersionInfoSizeExW(void)
{
    GetAddress("GetFileVersionInfoSizeExW");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_GetFileVersionInfoSizeW(void)
{
    GetAddress("GetFileVersionInfoSizeW");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_GetFileVersionInfoW(void)
{
    GetAddress("GetFileVersionInfoW");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_VerFindFileA(void)
{
    GetAddress("VerFindFileA");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_VerFindFileW(void)
{
    GetAddress("VerFindFileW");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_VerInstallFileA(void)
{
    GetAddress("VerInstallFileA");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_VerInstallFileW(void)
{
    GetAddress("VerInstallFileW");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_VerLanguageNameA(void)
{
    GetAddress("VerLanguageNameA");
    __asm JMP EAX;
}

ALCDECL DLLHijacker_VerLanguageNameW(void)
{
    GetAddress("VerLanguageNameW");
    __asm JMP EAX;
}ALCDECL DLLHijacker_VerQueryValueA(void)
{
    GetAddress("VerQueryValueA");
    __asm JMP EAX;
}
ALCDECL DLLHijacker_VerQueryValueW(void)
{
    GetAddress("VerQueryValueW");
    __asm JMP EAX;
}