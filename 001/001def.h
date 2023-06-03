#pragma once
#include "001.h"

#define _001 __stdcall
#define IMPORT extern "C" __declspec( dllimport )

#define entry_param HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd
#define main WinMain
#define wmain wWinMain
#define ENTRY_POINT(API) int API main(entry_param)

#define DLLFunctionDefW(ModuleName,API,Type,FunctionName,argument) HMODULE FunctionName##DLL = LoadLibraryW( ( LPCWSTR )ModuleName ); Type(API* FunctionName)argument = ( Type( API* )argument )GetProcAddress( FunctionName##DLL, ( LPCSTR ) #FunctionName );
#define _DefFunction(API,Type,FunctionName,argument) Type(API* FunctionName)(argument)

#define _001__MAX_PATH 260
#define _001__ZeroMemory(Destination,Length) _memset((Destination),0,(Length))

#ifdef WIN32
typedef DWORD32 DWORD32_64;
#else
typedef DWORD64 DWORD32_64;
#endif