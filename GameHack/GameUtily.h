#pragma once
class CGameUtily
{
public:
    CGameUtily( void );
    virtual ~CGameUtily( void );
    
    DWORD Str2Dword( LPCTSTR lpszStr )const;
    LPCTSTR GetConfigPath( LPCTSTR lpFileName ) const;
};

