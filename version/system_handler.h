#ifndef __SYSTEM_HANDLER_H__
#define __SYSTEM_HANDLER_H__

#include "hook_handler.h"

class SystemHandler : public HookHandler
{
public:
    SystemHandler();
    ~SystemHandler();

    virtual std::wstring GetDllName() const override;
    virtual void Handle(HMODULE hModule) override;
};

#endif