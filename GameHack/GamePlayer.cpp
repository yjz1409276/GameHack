#include "stdafx.h"
#include "GamePlayer.h"


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
    //	CString sConfigPath=m_gameUtily.GetConfigPath(_T("GameHack.ini"));
    CString sConfigPath = _T( "G:\\GitHub\\bin\\Debug\\GameHack.ini" );
    if ( !m_configFile.Load( sConfigPath ) )
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
