#include "StdAfx.h"
#include "GameHelper.h"
#include <TlHelp32.h>


CGameHelper::CGameHelper( void )
{
    m_bInited = FALSE;
    m_hGameHackDll = NULL;
    m_InstallWH = NULL;
    m_UnInstallWH = NULL;
}


CGameHelper::~CGameHelper( void )
{
}

BOOL CGameHelper::Start( CString sProName )
{
    if ( !IsInited() )
    {
        return FALSE;
    }
    
    DWORD dwPID = GetPidFromName( sProName );
    if ( -1 == dwPID )
    {
        return FALSE;
    }
    return InstallHook( dwPID );
}

BOOL CGameHelper::Stop()
{
    if ( !IsInited() )
    {
        return FALSE;
    }
    
    UnInstallHook();
    return TRUE;
}

DWORD CGameHelper::GetPidFromName( CString sProName )
{
    DWORD dwPID = -1;
    HANDLE hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if ( NULL == hSnap )
    {
        return -1;
    }
    PROCESSENTRY32 tr;
    tr.dwSize = sizeof( PROCESSENTRY32 );
    if ( Process32First( hSnap, &tr ) )
    {
        do
        {
            CString sName = tr.szExeFile;
            if ( 0 == sName.CompareNoCase( sProName ) )
            {
                dwPID = tr.th32ProcessID;
                break;
            }
        }
        while ( Process32Next( hSnap, &tr ) );
    }
    CloseHandle( hSnap );
    return dwPID;
}

BOOL CGameHelper::Init()
{
    CString sDllPath = GetGameHackDllPath();
    if ( !PathFileExists( sDllPath ) )
    {
        return FALSE;
    }
    if ( NULL == m_hGameHackDll )
    {
        m_hGameHackDll =::LoadLibrary( sDllPath );
    }
    if ( NULL != m_hGameHackDll )
    {
        m_InstallWH = ( InstallWindowHook )GetProcAddress( m_hGameHackDll, "InstallWindowHook" );
        m_UnInstallWH = ( UnInstallWindowHook )GetProcAddress( m_hGameHackDll, "UnInstallWindowHook" );
        if ( ( NULL != m_InstallWH ) && ( NULL != m_UnInstallWH ) )
        {
            m_bInited = TRUE;
            return TRUE;
        }
    }
    return FALSE;
}

void CGameHelper::UnInit()
{
    if ( NULL != m_hGameHackDll )
    {
        ::FreeLibrary( m_hGameHackDll );
        m_hGameHackDll = NULL;
        m_InstallWH = NULL;
        m_UnInstallWH = NULL;
        m_bInited = FALSE;
    }
}

CString CGameHelper::GetGameHackDllPath()
{
    CString sDllPath;
    TCHAR sModulePath[MAX_PATH] = {0};
    GetModuleFileName( NULL, sModulePath, MAX_PATH );
    CString sModule = sModulePath;
    sModule.Truncate( sModule.ReverseFind( _T( '\\' ) ) + 1 );
    sDllPath = sModule + _T( "GameHack.dll" );
    return sDllPath;
}

BOOL CGameHelper::InstallHook( DWORD dwPID )
{
    if ( NULL != m_InstallWH )
    {
        return m_InstallWH( dwPID );
    }
    return FALSE;
}

BOOL CGameHelper::UnInstallHook()
{
    if ( NULL != m_UnInstallWH )
    {
        m_UnInstallWH();
    }
    return TRUE;
}

BOOL CGameHelper::IsInited()
{
    return m_bInited;
}
