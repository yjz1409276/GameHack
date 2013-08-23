#pragma once
#include "ProcessHelper.h"
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
    CConfigFile m_configFile;
};

