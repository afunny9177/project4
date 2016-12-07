// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>
#include <Shlwapi.h>

// TODO:  在此处引用程序需要的其他头文件
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <tchar.h>

#include "detours.h"
#include "nsis.h"

#define DEFINE_TRUE_FUNCTION(name) typedef void (__cdecl* _##name)(HWND hwndParent, \
    int string_size, wchar_t *variables, stack_t **stacktop, extra_parameters *extra); \
    _##name True##name = nullptr

#define CALL_TRUE_FUNCTION(name) True##name(hwndParent, string_size, variables, stacktop, extra)

#define DEFINE_HOOK_FUNCTION(name) void __cdecl Hook##name(HWND hwndParent, int string_size, \
    wchar_t *variables, stack_t **stacktop, extra_parameters *extra)