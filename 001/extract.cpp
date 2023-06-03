#include "001.h"

void Extract( WORD wResId, LPWSTR lpszOutputPath, LPCWSTR lpType )
{
    HRSRC hrsrc = FindResourceW( NULL, MAKEINTRESOURCEW( wResId ), lpType );
    HGLOBAL hLoaded = LoadResource( NULL, hrsrc );
    LPVOID lpLock = LockResource( hLoaded );
    DWORD dwSize = SizeofResource( NULL, hrsrc );
    HANDLE hFile = CreateFileW( lpszOutputPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
    DWORD dwByteWritten;
    WriteFile( hFile, lpLock, dwSize, &dwByteWritten, NULL );
    CloseHandle( hFile );
    FreeResource( hLoaded );
}