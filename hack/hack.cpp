// hack.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "hack.h"

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")



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


typedef HMODULE(WINAPI* _LoadLibraryExW)(
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
        TrueCall = (_Call)GetProcAddress(hModule, "Call");
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

