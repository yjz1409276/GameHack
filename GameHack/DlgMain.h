#pragma once
class CDlgMain
{
public:
    virtual ~CDlgMain( void );
public:
    static CDlgMain* GetInstance();
    BOOL Create( HMODULE hDll , HWND hParent );
    void Destroy();
    BOOL Show( BOOL bShow = TRUE );
    BOOL IsShow()const;
protected:
    static VOID CALLBACK TimerProc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime );
    static INT_PTR CALLBACK DlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam );
    static void SetItemText( HWND hDlg, UINT itemID, LPCTSTR lpszText );
private:
    CDlgMain( void );
    static CDlgMain* m_pInstance;
    static HWND m_hDlg;
};

