#include "stdafx.h"
#include "GamePlayer.h"

extern CString g_configPath;
CGamePlayer::CGamePlayer()
{
    m_pProHelper = NULL;
}


CGamePlayer::~CGamePlayer( void )
{
}

CString CGamePlayer::GetAxisX() const
{
    DWORD dwAxisX = m_configFile.GetAxisX();
    DWORD dwBuf = 0;
    m_pProHelper->ReadMemory( ( LPCVOID )dwAxisX, &dwBuf, sizeof( dwBuf ) );
    CString sRet;
    sRet.Format( _T( "%u" ), dwBuf );
    return sRet;
}

BOOL CGamePlayer::Init( DWORD dwPID )
{
    if ( !m_configFile.Load( g_configPath ) )
    {
        return FALSE;
    }
    if ( NULL == m_pProHelper )
    {
        m_pProHelper = new CProcessHelper( dwPID );
    }
    
    return m_pProHelper->Open();
}

void CGamePlayer::UnInit()
{
    if ( NULL != m_pProHelper )
    {
        m_pProHelper->Close();
        delete m_pProHelper;
        m_pProHelper = NULL;
    }
    
    m_configFile.UnLoad();
}

CString CGamePlayer::GetAxisY() const
{
    DWORD dwAxisY = m_configFile.GetAxisY();
    DWORD dwBuf = 0;
    m_pProHelper->ReadMemory( ( LPCVOID )dwAxisY, &dwBuf, sizeof( dwBuf ) );
    CString sRet;
    sRet.Format( _T( "%u" ), dwBuf );
    return sRet;
}
