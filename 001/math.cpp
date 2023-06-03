#include "001.h"

#ifdef WIN32

DWORD xs32;

void _001 SeedXorshift( _In_ DWORD dwSeed )
{
	xs32 = dwSeed;
}
DWORD _001 Xorshift( void )
{
	xs32 ^= xs32 << 13;
	xs32 ^= xs32 >> 17;
	xs32 ^= xs32 << 5;
	return xs32;
}

#else

DWORD64 xs64;

void _001 SeedXorshift( _In_ DWORD64 dwSeed )
{
	xs64 = dwSeed;
}
DWORD64 _001 Xorshift( void )
{
	xs64 ^= xs64 << 13;
	xs64 ^= xs64 >> 7;
	xs64 ^= xs64 << 17;
	return xs64;
}
#endif

DWORD xor128( void )
{
	static DWORD x = 123456789, y = 362436069, z = 521288629, w = 88675123;
	DWORD t = ( x ^ ( x << 11 ) );
	x = y;
	y = z;
	z = w;
	return ( w = ( w ^ ( w >> 19 ) ) ^ ( t ^ ( t >> 8 ) ) );
}

float _001 _sin( float _X )
{
	return sinf( _X );
}

double _001 _sin( double _X )
{
	return sin( _X );
}