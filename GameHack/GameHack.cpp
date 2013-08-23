// GameHack.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "GameHack.h"
#include "DlgMain.h"
#include <TlHelp32.h>

#pragma data_seg(".GameHack")
HMODULE g_hDll = NULL;
HHOOK g_hKeyboardHook = NULL;
CDlgMain* g_dlgMain = NULL;
DWORD g_dwPID = -1;
HWND g_hParent = NULL;
#pragma data_seg()
#pragma comment(linker, "/Section:.GameHack,RWS")

HWND GetWindowHandleByPID( DWORD dwProcessID )
{
    HWND h = GetTopWindow( 0 );
    while ( h )
    {
        DWORD pid = 0;
        DWORD dwTheardId = GetWindowThreadProcessId( h, &pid );
        if ( dwTheardId != 0 )
        {
            if ( pid == dwProcessID/*your process id*/ )
            {
                return h;
            }
        }
        h = GetNextWindow( h , GW_HWNDNEXT );
    }
    return NULL;
}

DWORD GetThreadIDByProcssID( DWORD dwProcessID )
{
    DWORD dwThreadID = 0;
    THREADENTRY32 te32 = {sizeof( te32 )};
    HANDLE hThreadSnap = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, dwProcessID );
    if ( Thread32First( hThreadSnap, &te32 ) )
    {
        do
        {
            if ( dwProcessID == te32.th32OwnerProcessID )
            {
                dwThreadID = te32.th32ThreadID;
                break;
            }
        }
        while ( Thread32Next( hThreadSnap, &te32 ) );
    }
    
    return dwThreadID;
}

BOOL InstallWindowHook( DWORD dwPID )
{
    if ( NULL == g_hKeyboardHook )
    {
        g_hParent = GetWindowHandleByPID( dwPID );
        
        dwPID = GetThreadIDByProcssID( dwPID );
        g_dwPID = dwPID;
        g_hKeyboardHook =::SetWindowsHookEx( WH_KEYBOARD, ( HOOKPROC )KeyboardProc, g_hDll, dwPID );
    }
    return ( NULL != g_hKeyboardHook );
}

void UnInstallWindowHook()
{
    if ( NULL != g_hKeyboardHook )
    {
        if ( NULL != g_dlgMain )
        {
            //             g_dlgMain->Show( FALSE );
            //             g_dlgMain->Destroy();
            //             delete g_dlgMain;
            //             g_dlgMain = NULL;
        }
        ::UnhookWindowsHookEx( g_hKeyboardHook );
        g_hKeyboardHook = NULL;
    }
}

LRESULT CALLBACK KeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
{
    LRESULT lRet =::CallNextHookEx( g_hKeyboardHook, nCode, wParam, lParam );
    if ( nCode == HC_ACTION )
    {
        BOOL bKeyUp = lParam & ( 1 << 31 );
        if ( ( bKeyUp ) && ( wParam == VK_F8 ) )
        {
            if ( NULL == g_dlgMain )
            {
                g_dlgMain = CDlgMain::GetInstance();
            }
            g_dlgMain->Create( g_hDll, g_hParent );
            g_dlgMain->Show( g_dlgMain->IsShow() ? FALSE : TRUE );
        }
    }
    return lRet;
}
