#include "001.h"

void GetRandomPath( _Inout_ PWSTR szRandom, _In_ int nLength )
{
	for ( int i = 0; i < nLength; i++ )
	{
		szRandom[ i ] = ( WCHAR ) ( Xorshift( ) % ( 0x9FFF - 0x4E00 + 1 ) + 0x4E00 );
	}
}

void* _memset( void* buf, int c, size_t num )
{
	unsigned char* ptr = ( unsigned char* ) buf;
	const unsigned char ch = ( unsigned char ) c;

	while ( num-- )
		*ptr++ = ch;

	return buf;
}

size_t Mbstowcs(
	wchar_t* pwcs,
	const char* s,
	size_t n )
{
	register wchar_t* p = pwcs;
	for ( wchar_t* t = p + n;
		p != t && ( *p = ( unsigned char ) *s ) != L'\0';
		p++, s++ )
		;
	return p - pwcs;
}

wchar_t* cat( wchar_t* destination, wchar_t* source )
{
	//wcscat_s( destination, sizeof( destination ) / sizeof( *destination ), source );

	wchar_t* ptr = destination + lstrlenW( destination );
	while ( *source != L'\0' )
	{
		*ptr++ = *source++;
	}
	*ptr = L'\0';

	return destination;
}

char* cat( char* destination, char* source )
{
	//strcat_s( destination, sizeof( destination ) / sizeof( *destination ), source );

	char* ptr = destination + strlen( destination );
	while ( *source != L'\0' )
	{
		*ptr++ = *source++;
	}
	*ptr = L'\0';

	return destination;
}

char* push_front( char* src, char* dst )
{
	char Path[ MAX_PATH ];
	lstrcpyA( Path, src );
	return cat( Path, dst );
}

wchar_t* push_front( wchar_t* src, wchar_t* dst )
{
	wchar_t Path[ MAX_PATH ];
	lstrcpyW( Path, src );
	return cat( Path, dst );
}