#pragma once
#include "001.h"

#ifdef WIN32
void _001 SeedXorshift( _In_ DWORD dwSeed );
DWORD _001 Xorshift( void );
#else
void _001 SeedXorshift( _In_ DWORD64 dwSeed );
DWORD64 _001 Xorshift( void );
#endif

DWORD xor128( void );

float _001 _sin( float _X );
double _001 _sin( double _X );