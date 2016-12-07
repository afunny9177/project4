// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "hijackapi.h"
#include "hook_manager.h"

std::unique_ptr<HookManager> g_manager;

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
    if (DetourIsHelperProcess())
    {
        return TRUE;
    }

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        DetourRestoreAfterWith();
        LoadOrigin();

        if (!g_manager)
        {
            g_manager.reset(new HookManager());
            g_manager->Init();
        }
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        FreeOrigin();

        if (g_manager)
        {
            g_manager->Uninit();
            g_manager.reset();
        }
    }

	return TRUE;
}

