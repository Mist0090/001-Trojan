#include "001.h"

void _001 reg_add(
	HKEY HKey,
	LPCWSTR Subkey,
	LPCWSTR ValueName,
	unsigned long Type,
	unsigned int Value
)
{
	HKEY hKey;
	DWORD dwDisposition;
	LONG result;

	DWORD Wow64Mode = KEY_WOW64_32KEY;
	BOOL Wow64Flags = FALSE;

	IsWow64Process( GetCurrentProcess( ), &Wow64Flags );
	if ( Wow64Flags )
	{
		Wow64Mode = KEY_WOW64_64KEY;
	}

	result = RegCreateKeyExW(
		HKey, //HKEY
		Subkey,//キー
		0,//予約
		NULL,//指定
		REG_OPTION_NON_VOLATILE,//不揮発性
		KEY_ALL_ACCESS | Wow64Mode,//標準アクセス権）のすべての権利を組み合わせたもの
		NULL,
		&hKey,
		&dwDisposition );

	result = RegSetValueExW(
		hKey,	// 現在オープンしているキーのハンドル
		ValueName,	// 値の「名前」が入った文字列へのポインタ
		0,	// 予約パラメータ。0を指定する
		Type,	// 値の「種類」を指定する。NULLで終わる文字列はREG_SZ、32ビット値はREG_DWORD
		( const unsigned char* ) &Value,	// 格納する値の「データ」が入ったバッファへのポインタ
		( int ) sizeof( Value )		// dataのサイズを指定する 
	);

	//キーを閉じる
	RegCloseKey( hKey );
	return;
}

void _001 reg_add(
	HKEY HKey,
	LPCWSTR Subkey,
	LPCWSTR ValueName,
	unsigned long Type,
	LPCWSTR Value
)
{
	if ( Wow64EnableWow64FsRedirection( FALSE ) )
	{
		HKEY hKey;
		DWORD dwDisposition;
		LONG result;

		DWORD Wow64Mode = KEY_WOW64_32KEY;
		BOOL Wow64Flags = FALSE;

		IsWow64Process( GetCurrentProcess( ), &Wow64Flags );
		if ( Wow64Flags )
		{
			Wow64Mode = KEY_WOW64_64KEY;
		}

		result = RegCreateKeyExW(
			HKey, //HKEY
			Subkey,//キー
			0,//予約
			NULL,//指定
			REG_OPTION_NON_VOLATILE,//不揮発性
			KEY_ALL_ACCESS | Wow64Mode,//標準アクセス権）のすべての権利を組み合わせたもの
			NULL,
			&hKey,
			&dwDisposition );

		result = RegSetValueExW(
			hKey,	// 現在オープンしているキーのハンドル
			ValueName,	// 値の「名前」が入った文字列へのポインタ
			0,	// 予約パラメータ。0を指定する
			Type,	// 値の「種類」を指定する。NULLで終わる文字列はREG_SZ、32ビット値はREG_DWORD
			( LPBYTE ) Value,	// 格納する値の「データ」が入ったバッファへのポインタ
			( MAX_PATH ) +1 	// dataのサイズを指定する 
		);

		//キーを閉じる
		RegCloseKey( hKey );
	}
	if ( !Wow64EnableWow64FsRedirection( TRUE ) )
	{
		return;
	}
	return;
}