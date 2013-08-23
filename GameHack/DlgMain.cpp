#include "StdAfx.h"
#include <Windows.h>
#include "DlgMain.h"
#include "resource.h"
#include "GamePlayer.h"

extern CGamePlayer g_gamePlayer;
extern DWORD g_dwPID;
extern CDlgMain* g_dlgMain;
//extern HMODULE g_hDll;
CDlgMain::CDlgMain( void )
{
    m_hDlg = NULL;
}

CDlgMain::~CDlgMain( void )
{
    Destroy();
}

BOOL CDlgMain::Create( HMODULE hDll, HWND hParent )
{
    if ( NULL != m_hDlg )
    {
        return TRUE;
    }
    m_hDlg = CreateDialogParam( hDll, MAKEINTRESOURCE( IDD_DLG_MAIN ), hParent, ( DLGPROC )DlgProc, 0 ) ;
    return TRUE;
}

BOOL CDlgMain::Show( BOOL bShow/*=TRUE*/ )
{
    return ::ShowWindow( m_hDlg, bShow ? SW_SHOWNORMAL : SW_HIDE );
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
            // 			HWND hParent=::GetParent(hDlg);
            // 			CString sBuf;
            // 			GetWindowText(hParent,sBuf.GetBuffer(),sBuf.GetLength());
            // 			MessageBox(NULL,sBuf,sBuf,0);
            if ( !g_gamePlayer.Init( g_dwPID ) )
            {
                return FALSE;
            }
            return ( TRUE );
        }
        case WM_CLOSE:
        {
            g_dlgMain->Show( FALSE );
            return ( TRUE );
        }
        case WM_DESTROY:
        {
            //            PostQuitMessage( 0 );
            return TRUE;
        }
        case WM_TIMER:
        {
            TimerProc( g_dlgMain->m_hDlg, WM_TIMER, wParam, 0 );
            return TRUE;
        }
        case WM_COMMAND:
            switch ( LOWORD( wParam ) )
            {
                case IDC_START:
                {
                    ::SetTimer( g_dlgMain->m_hDlg, 0, 1000, NULL );
                    return TRUE;
                }
                case IDC_STOP:
                {
                    ::KillTimer( g_dlgMain->m_hDlg, 0 );
                    return TRUE;
                }
            }
            return ( FALSE );
    }
    return FALSE;
}

void CDlgMain::Destroy()
{
    if ( NULL != m_hDlg )
    {
        DestroyWindow( m_hDlg );
        m_hDlg = NULL;
    }
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