#include "StdAfx.h"
#include <Windows.h>
#include "DlgMain.h"
#include "resource.h"
#include "GamePlayer.h"

CGamePlayer g_gamePlayer;
CDlgMain* CDlgMain::m_pInstance = NULL;
HWND CDlgMain::m_hDlg = NULL;
extern CDlgMain* g_dlgMain;
extern DWORD g_dwPID;
CDlgMain::CDlgMain( void )
{
    m_hDlg = NULL;
}


CDlgMain::~CDlgMain( void )
{
}

CDlgMain* CDlgMain::GetInstance()
{
    if ( NULL == m_pInstance )
    {
        m_pInstance = new CDlgMain();
    }
    return m_pInstance;
}

BOOL CDlgMain::Create( HMODULE hDll, HWND hParent )
{
    if ( NULL != m_hDlg )
    {
        return TRUE;
    }
    
    m_hDlg = CreateDialog( hDll, MAKEINTRESOURCE( IDD_DLG_MAIN ), hParent, ( DLGPROC )DlgProc ) ;
    ShowWindow( m_hDlg, SW_SHOWNORMAL );
    UpdateWindow( m_hDlg );
    
    BOOL bRet;
    MSG          msg;
    while ( ( bRet = GetMessage( &msg, NULL, 0, 0 ) ) != 0 )
    {
        if ( 0 == bRet )
        {
            break;
        }
        else if ( bRet == -1 )
        {
            // Handle the error and possibly exit
        }
        else if ( !IsWindow( m_hDlg ) || !IsDialogMessage( m_hDlg, &msg ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }
    return TRUE;
}

BOOL CDlgMain::Show( BOOL bShow/*=TRUE*/ )
{
    return ::ShowWindow( m_hDlg, bShow ? SW_SHOWNORMAL : SW_HIDE );
    //    return SetWindowPos( m_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE );
}

BOOL CDlgMain::IsShow() const
{
    return ::IsWindowVisible( m_hDlg );
}

INT_PTR CALLBACK  CDlgMain::DlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch ( message )
    {
        case WM_INITDIALOG:
        {
            if ( !g_gamePlayer.Init( g_dwPID ) )
            {
                return FALSE;
            }
            return ( TRUE );
        }
        case WM_CLOSE:
        {
            DestroyWindow(hDlg);
			m_hDlg=NULL;
            return ( TRUE );
        }
        case WM_DESTROY:
        {
            PostQuitMessage( 0 );
            return TRUE;
        }
        case WM_TIMER:
        {
            TimerProc( m_hDlg, WM_TIMER, wParam, 0 );
            return TRUE;
        }
        case WM_COMMAND:
            switch ( LOWORD( wParam ) )
            {
                case IDC_START:
                {
                    ::SetTimer( m_hDlg, 0, 1000, NULL );
                    return TRUE;
                }
                case IDC_STOP:
                {
                    ::KillTimer( m_hDlg, 0 );
                    return TRUE;
                }
            }
            return ( FALSE );
    }
    return FALSE;
}

void CDlgMain::Destroy()
{
//    DestroyWindow( m_hDlg );
    m_hDlg = NULL;
}

VOID CALLBACK CDlgMain::TimerProc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
    if ( 0 == idEvent )
    {
        CString sAxisX = g_gamePlayer.GetAxisX();
        CString sAxisY = g_gamePlayer.GetAxisY();
        
        SetItemText( hwnd, IDC_STATIC_AXISX, sAxisX );
        SetItemText( hwnd, IDC_STATIC_AXISY, sAxisY );
        
    }
}

void CDlgMain::SetItemText( HWND hDlg, UINT itemID, LPCTSTR lpszText )
{
    HWND hCtrl = GetDlgItem( hDlg, itemID );
    SetWindowText( hCtrl, lpszText );
}
