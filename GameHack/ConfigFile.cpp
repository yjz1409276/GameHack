#include "stdafx.h"
#include "ConfigFile.h"


CConfigFile::CConfigFile( void )
{
    m_pIniReader = NULL;
}


CConfigFile::~CConfigFile( void )
{
}

DWORD CConfigFile::GetAxisX() const
{
    DWORD dwAxisX = m_pIniReader->ReadDword( _T( "人物信息" ), _T( "AxisX" ) );
    DWORD dwGameBase = GetGameBase();
    return dwGameBase + dwAxisX;
}

DWORD CConfigFile::GetAxisY() const
{
    DWORD dwAxisY = m_pIniReader->ReadDword( _T( "人物信息" ), _T( "AxisY" ) );
    DWORD dwGameBase = GetGameBase();
    return dwGameBase + dwAxisY;
}

BOOL CConfigFile::Load( LPCTSTR lpszPath )
{
    if ( NULL == m_pIniReader )
    {
        m_pIniReader = new CIniReader( lpszPath );
    }
    return ( NULL != m_pIniReader );
}

void CConfigFile::UnLoad()
{
    if ( NULL != m_pIniReader )
    {
        delete m_pIniReader;
        m_pIniReader = NULL;
    }
}

DWORD CConfigFile::GetGameBase() const
{
    return m_pIniReader->ReadDword( _T( "人物信息" ), _T( "GameBase" ) );
}
