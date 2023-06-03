#pragma once
#include "001.h"

void GetRandomPath( _Inout_ PWSTR szRandom, _In_ int nLength );

void* _memset( void* buf, int c, size_t num );
size_t Mbstowcs( wchar_t* pwcs, const char* s, size_t n );

wchar_t* cat( wchar_t* destination, wchar_t* source );
char* cat( char* destination, char* source );

char* push_front( char* src, char* dst );
wchar_t* push_front( wchar_t* src, wchar_t* dst );