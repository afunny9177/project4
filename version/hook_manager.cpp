#include "stdafx.h"
#include "hook_manager.h"
#include "sys_string_conversions.h"

#include "system_handler.h"

_LoadLibraryA TrueLoadLibraryA = reinterpret_cast<_LoadLibraryA>(
    GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "LoadLibraryA"));

_LoadLibraryW TrueLoadLibraryW = reinterpret_cast<_LoadLibraryW>(
    GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "LoadLibraryW"));

_LoadLibraryExA TrueLoadLibraryExA = reinterpret_cast<_LoadLibraryExA>(
    GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "LoadLibraryExA"));

_LoadLibraryExW TrueLoadLibraryExW = reinterpret_cast<_LoadLibraryExW>(
    GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "LoadLibraryExW"));

HMODULE WINAPI HookLoadLibraryA(LPCSTR lpFileName)
{
    HMODULE hModule = TrueLoadLibraryA(lpFileName);

    if (g_manager)
    {
        std::string dllName = PathFindFileNameA(lpFileName);
        std::transform(dllName.begin(), dllName.end(), dllName.begin(), tolower);
        g_manager->Handle(hModule, base::SysUTF8ToWide(dllName));
    }

    return hModule;
}

HMODULE WINAPI HookLoadLibraryW(LPCWSTR lpFileName)
{
    HMODULE hModule = TrueLoadLibraryW(lpFileName);

    if (g_manager)
    {
        std::wstring dllName = PathFindFileNameW(lpFileName);
        std::transform(dllName.begin(), dllName.end(), dllName.begin(), tolower);
        g_manager->Handle(hModule, dllName);
    }

    return hModule;
}

HMODULE WINAPI HookLoadLibraryExA(LPCSTR lpFileName, HANDLE hFile, DWORD dwFlags)
{
    HMODULE hModule = TrueLoadLibraryExA(lpFileName, hFile, dwFlags);

    if (g_manager)
    {
        std::string dllName = PathFindFileNameA(lpFileName);
        std::transform(dllName.begin(), dllName.end(), dllName.begin(), tolower);
        g_manager->Handle(hModule, base::SysUTF8ToWide(dllName));
    }

    return hModule;
}

HMODULE WINAPI HookLoadLibraryExW(LPCWSTR lpFileName, HANDLE hFile, DWORD dwFlags)
{
    HMODULE hModule = TrueLoadLibraryExW(lpFileName, hFile, dwFlags);

    if (g_manager)
    {
        std::wstring dllName = PathFindFileNameW(lpFileName);
        std::transform(dllName.begin(), dllName.end(), dllName.begin(), tolower);
        g_manager->Handle(hModule, dllName);
    }

    return hModule;
}


HookManager::HookManager()
    : handlers_()
{

}

HookManager::~HookManager()
{

}

void HookManager::Init()
{
    AddHandlers();

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)TrueLoadLibraryA, HookLoadLibraryA);
    DetourAttach(&(PVOID&)TrueLoadLibraryW, HookLoadLibraryW);
    DetourAttach(&(PVOID&)TrueLoadLibraryExA, HookLoadLibraryExA);
    DetourAttach(&(PVOID&)TrueLoadLibraryExW, HookLoadLibraryExW);
    DetourTransactionCommit();
}

void HookManager::Uninit()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)TrueLoadLibraryA, HookLoadLibraryA);
    DetourDetach(&(PVOID&)TrueLoadLibraryW, HookLoadLibraryW);
    DetourDetach(&(PVOID&)TrueLoadLibraryExA, HookLoadLibraryExA);
    DetourDetach(&(PVOID&)TrueLoadLibraryExW, HookLoadLibraryExW);
    DetourTransactionCommit();
}

void HookManager::AddHandlers()
{
    // System.dll
    std::unique_ptr<HookHandler> system(new SystemHandler());
    handlers_.push_back(std::move(system));
}

void HookManager::Handle(HMODULE hModule, const std::wstring& dllName)
{
    for (const auto& handler : handlers_)
    {
        if (handler && handler->GetDllName() == dllName)
        {
            handler->Handle(hModule);
            break;
        }
    }
}