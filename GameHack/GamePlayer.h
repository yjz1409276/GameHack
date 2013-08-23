#pragma once
#include "ProcessHelper.h"
#include "GameUtily.h"
#include "ConfigFile.h"
class CGamePlayer
{
public:
    CGamePlayer();
    virtual ~CGamePlayer( void );
    
    BOOL Init( DWORD dwPID );
    void UnInit();
    
    CString GetAxisX()const;
    CString GetAxisY()const;
private:
    CProcessHelper* m_pProHelper;
    CGameUtily m_gameUtily;
    CConfigFile m_configFile;
};

