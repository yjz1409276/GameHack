// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "GameHack.h"

extern HMODULE g_hDll;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch ( ul_reason_for_call )
    {
        case DLL_PROCESS_ATTACH:
        {
            g_hDll = hModule;
            break;
        }
        case DLL_THREAD_ATTACH:
        {
            break;
        }
        case DLL_THREAD_DETACH:
        {
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            break;
        }
        default:
            break;
    }
    return TRUE;
}

