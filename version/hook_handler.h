#ifndef __HOOK_HANDLER_H__
#define __HOOK_HANDLER_H__

class HookHandler
{
public:
    HookHandler();
    ~HookHandler();

    virtual std::wstring GetDllName() const = 0;
    virtual void Handle(HMODULE hModule) = 0;
};

#endif