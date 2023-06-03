#include "001.h"

BOOL FlagExists( WCHAR* flag )
{
	DLLFunctionDefW( L"shlwapi.dll", WINAPI, BOOL, PathFileExistsW, ( LPCWSTR pszPath ) );

	WCHAR FLAG_PATH[ MAX_PATH ] = L"C:\\ProgramData\\";
	cat( FLAG_PATH, flag );

	if ( PathFileExistsW( FLAG_PATH ) )
	{
		return TRUE;
	}

	return FALSE;
}

void CreateFlag( WCHAR* flag ) 
{
	WCHAR FLAG_PATH[ MAX_PATH ] = L"C:\\ProgramData\\";
	cat( FLAG_PATH, flag );

	DWORD dw;
	HANDLE newflag = CreateFileW( FLAG_PATH, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM, NULL );
	WriteFile( newflag, NULL, NULL, &dw, NULL );
	CloseHandle( newflag );
}

void DeleteFlag( WCHAR* flag )
{
	WCHAR FLAG_PATH[ MAX_PATH ] = L"C:\\ProgramData\\";
	cat( FLAG_PATH, flag );

	DeleteFileW( FLAG_PATH );
}