#include "stdafx.h"
#include "GameUtily.h"
#include <tchar.h>


CGameUtily::CGameUtily( void )
{
}


CGameUtily::~CGameUtily( void )
{
}

DWORD CGameUtily::Str2Dword( LPCTSTR lpszStr )const
{
    return _ttol( lpszStr );
}

LPCTSTR CGameUtily::GetConfigPath( LPCTSTR lpFileName ) const
{
    CString sDllPath;
    TCHAR sModulePath[MAX_PATH] = {0};
    GetModuleFileName( NULL, sModulePath, MAX_PATH );
    CString sModule = sModulePath;
    sModule.Truncate( sModule.ReverseFind( _T( '\\' ) ) + 1 );
    sDllPath = sModule + lpFileName;
    return sDllPath;
}
