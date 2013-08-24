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
    DWORD dwAxisX = m_pIniReader->ReadStringToHex( _T( "������Ϣ" ), _T( "������" ) );
    return dwAxisX;
}

DWORD CConfigFile::GetAxisY() const
{
    DWORD dwAxisY = m_pIniReader->ReadStringToHex( _T( "������Ϣ" ), _T( "������" ) );
    return dwAxisY;
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
    return m_pIniReader->ReadStringToHex( _T( "������Ϣ" ), _T( "��ַ" ) );
}

DWORD CConfigFile::GetPlayerName() const
{
	return m_pIniReader->ReadStringToHex( _T( "������Ϣ" ), _T( "��������" ) );
}

DWORD CConfigFile::GetGameModule() const
{
	return 0x00400000;
}
