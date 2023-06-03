#include "001.h"

POINT msgBoxPoint = { 0 };

BOOL CALLBACK MonitorEnumProc( HMONITOR hMonitor, HDC hdcMonitor, PRECT prcBounds, LPARAM lParam )
{
	PRECT prcParam = ( RECT* ) lParam;
	UnionRect( prcParam, prcParam, prcBounds );
	return TRUE;
}

LRESULT CALLBACK msgBoxHook( INT nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode == HCBT_CREATEWND )
	{
		CREATESTRUCT* pcs = ( ( CBT_CREATEWND* ) lParam )->lpcs;

		if ( ( pcs->style & WS_DLGFRAME ) || ( pcs->style & WS_POPUP ) ) {
			HWND hwnd = ( HWND ) wParam;

			INT x = msgBoxPoint.x;
			INT y = msgBoxPoint.y;

			pcs->x = x;
			pcs->y = y;
		}
	}

	return CallNextHookEx( 0, nCode, wParam, lParam );
}