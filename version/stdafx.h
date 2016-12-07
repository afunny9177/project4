// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>
#include <Shlwapi.h>

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
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