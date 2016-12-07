#include "stdafx.h"
#include "hijackapi.h"

#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=_Hijack_GetFileVersionInfoA,@1")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=_Hijack_GetFileVersionInfoByHandle,@2")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=_Hijack_GetFileVersionInfoExA,@3")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=_Hijack_GetFileVersionInfoExW,@4")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=_Hijack_GetFileVersionInfoSizeA,@5")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=_Hijack_GetFileVersionInfoSizeExA,@6")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=_Hijack_GetFileVersionInfoSizeExW,@7")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=_Hijack_GetFileVersionInfoSizeW,@8")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=_Hijack_GetFileVersionInfoW,@9")
#pragma comment(linker, "/EXPORT:VerFindFileA=_Hijack_VerFindFileA,@10")
#pragma comment(linker, "/EXPORT:VerFindFileW=_Hijack_VerFindFileW,@11")
#pragma comment(linker, "/EXPORT:VerInstallFileA=_Hijack_VerInstallFileA,@12")
#pragma comment(linker, "/EXPORT:VerInstallFileW=_Hijack_VerInstallFileW,@13")
#pragma comment(linker, "/EXPORT:VerLanguageNameA=_Hijack_VerLanguageNameA,@14")
#pragma comment(linker, "/EXPORT:VerLanguageNameW=_Hijack_VerLanguageNameW,@15")
#pragma comment(linker, "/EXPORT:VerQueryValueA=_Hijack_VerQueryValueA,@16")
#pragma comment(linker, "/EXPORT:VerQueryValueW=_Hijack_VerQueryValueW,@17")

ALCDECL Hijack_GetFileVersionInfoA()
{
    GetAddress("GetFileVersionInfoA");
    __asm JMP EAX;
}
ALCDECL Hijack_GetFileVersionInfoByHandle()
{
    GetAddress("GetFileVersionInfoByHandle");
    __asm JMP EAX;
}
ALCDECL Hijack_GetFileVersionInfoExA()
{
    GetAddress("GetFileVersionInfoExA");
    __asm JMP EAX;
}
ALCDECL Hijack_GetFileVersionInfoExW()
{
    GetAddress("GetFileVersionInfoExW");
    __asm JMP EAX;
}
ALCDECL Hijack_GetFileVersionInfoSizeA()
{
    GetAddress("GetFileVersionInfoSizeA");
    __asm JMP EAX;
}
ALCDECL Hijack_GetFileVersionInfoSizeExA()
{
    GetAddress("GetFileVersionInfoSizeExA");
    __asm JMP EAX;
}
ALCDECL Hijack_GetFileVersionInfoSizeExW()
{
    GetAddress("GetFileVersionInfoSizeExW");
    __asm JMP EAX;
}
ALCDECL Hijack_GetFileVersionInfoSizeW()
{
    GetAddress("GetFileVersionInfoSizeW");
    __asm JMP EAX;
}
ALCDECL Hijack_GetFileVersionInfoW()
{
    GetAddress("GetFileVersionInfoW");
    __asm JMP EAX;
}
ALCDECL Hijack_VerFindFileA()
{
    GetAddress("VerFindFileA");
    __asm JMP EAX;
}
ALCDECL Hijack_VerFindFileW()
{
    GetAddress("VerFindFileW");
    __asm JMP EAX;
}
ALCDECL Hijack_VerInstallFileA()
{
    GetAddress("VerInstallFileA");
    __asm JMP EAX;
}
ALCDECL Hijack_VerInstallFileW()
{
    GetAddress("VerInstallFileW");
    __asm JMP EAX;
}
ALCDECL Hijack_VerLanguageNameA()
{
    GetAddress("VerLanguageNameA");
    __asm JMP EAX;
}

ALCDECL Hijack_VerLanguageNameW()
{
    GetAddress("VerLanguageNameW");
    __asm JMP EAX;
}ALCDECL Hijack_VerQueryValueA()
{
    GetAddress("VerQueryValueA");
    __asm JMP EAX;
}
ALCDECL Hijack_VerQueryValueW()
{
    GetAddress("VerQueryValueW");
    __asm JMP EAX;
}