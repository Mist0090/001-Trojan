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
		Subkey,//�L�[
		0,//�\��
		NULL,//�w��
		REG_OPTION_NON_VOLATILE,//�s������
		KEY_ALL_ACCESS | Wow64Mode,//�W���A�N�Z�X���j�̂��ׂĂ̌�����g�ݍ��킹������
		NULL,
		&hKey,
		&dwDisposition );

	result = RegSetValueExW(
		hKey,	// ���݃I�[�v�����Ă���L�[�̃n���h��
		ValueName,	// �l�́u���O�v��������������ւ̃|�C���^
		0,	// �\��p�����[�^�B0���w�肷��
		Type,	// �l�́u��ށv���w�肷��BNULL�ŏI��镶�����REG_SZ�A32�r�b�g�l��REG_DWORD
		( const unsigned char* ) &Value,	// �i�[����l�́u�f�[�^�v���������o�b�t�@�ւ̃|�C���^
		( int ) sizeof( Value )		// data�̃T�C�Y���w�肷�� 
	);

	//�L�[�����
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
			Subkey,//�L�[
			0,//�\��
			NULL,//�w��
			REG_OPTION_NON_VOLATILE,//�s������
			KEY_ALL_ACCESS | Wow64Mode,//�W���A�N�Z�X���j�̂��ׂĂ̌�����g�ݍ��킹������
			NULL,
			&hKey,
			&dwDisposition );

		result = RegSetValueExW(
			hKey,	// ���݃I�[�v�����Ă���L�[�̃n���h��
			ValueName,	// �l�́u���O�v��������������ւ̃|�C���^
			0,	// �\��p�����[�^�B0���w�肷��
			Type,	// �l�́u��ށv���w�肷��BNULL�ŏI��镶�����REG_SZ�A32�r�b�g�l��REG_DWORD
			( LPBYTE ) Value,	// �i�[����l�́u�f�[�^�v���������o�b�t�@�ւ̃|�C���^
			( MAX_PATH ) +1 	// data�̃T�C�Y���w�肷�� 
		);

		//�L�[�����
		RegCloseKey( hKey );
	}
	if ( !Wow64EnableWow64FsRedirection( TRUE ) )
	{
		return;
	}
	return;
}