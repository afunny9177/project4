#ifndef __HOOKAPI_H__
#define __HOOKAPI_H__

#include "hook_handler.h"

typedef HMODULE (WINAPI* _LoadLibraryA)(
    _In_ LPCSTR lpFileName
    );

typedef HMODULE (WINAPI* _LoadLibraryW)(
    _In_ LPCWSTR lpFileName
    );

typedef HMODULE (WINAPI* _LoadLibraryExA)(
    _In_       LPCSTR lpFileName,
    _Reserved_ HANDLE  hFile,
    _In_       DWORD   dwFlags
    );

typedef HMODULE (WINAPI* _LoadLibraryExW)(
    _In_       LPCWSTR lpFileName,
    _Reserved_ HANDLE  hFile,
    _In_       DWORD   dwFlags
    );

HMODULE WINAPI HookLoadLibraryA(LPCSTR lpFileName);
HMODULE WINAPI HookLoadLibraryW(LPCWSTR lpFileName);
HMODULE WINAPI HookLoadLibraryExA(LPCSTR lpFileName, HANDLE hFile, DWORD dwFlags);
HMODULE WINAPI HookLoadLibraryExW(LPCWSTR lpFileName, HANDLE hFile, DWORD dwFlags);

class HookManager;

extern std::unique_ptr<HookManager> g_manager;

class HookManager
{
public:
    HookManager();
    ~HookManager();

    void Init();
    void Uninit();

    void Handle(HMODULE hModule, const std::wstring& dllName);

protected:
    void AddHandlers();

private:
    std::vector<std::unique_ptr<HookHandler>> handlers_;
};


#endif