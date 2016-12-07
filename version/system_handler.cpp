#include "stdafx.h"
#include "system_handler.h"
#include "hook_handler.h"

DEFINE_TRUE_FUNCTION(Alloc);
DEFINE_TRUE_FUNCTION(Call);
DEFINE_TRUE_FUNCTION(Copy);
DEFINE_TRUE_FUNCTION(Free);
DEFINE_TRUE_FUNCTION(Get);
DEFINE_TRUE_FUNCTION(Int64Op);
DEFINE_TRUE_FUNCTION(Store);


DEFINE_HOOK_FUNCTION(Call)
{
    if (stacktop != nullptr)
    {
        OutputDebugStringW(L"-------------------------->");
        OutputDebugStringW((*stacktop)->text);
        MessageBox(0, (*stacktop)->text, 0, 0);
    }

    CALL_TRUE_FUNCTION(Call);
}

SystemHandler::SystemHandler()
{

}

SystemHandler::~SystemHandler()
{

}

std::wstring SystemHandler::GetDllName() const
{
    return L"system.dll";
}

void SystemHandler::Handle(HMODULE hModule)
{
    TrueCall = reinterpret_cast<_Call>(GetProcAddress(hModule, "Call"));

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)TrueCall, HookCall);
    DetourTransactionCommit();
}

