#include "CSX_Utils.h"
#include "../../X1API/X1FastCall.h"
static const DWORD dwModuleDelay = 100;
//[junk_enable /]
namespace CSX
{
	namespace Utils
	{
		/* Wait dwMsec Load Module */

		bool IsModuleLoad( PCHAR szModule , DWORD dwMsec )
		{
			HMODULE hModule = FastCall::G().t_GetModuleHandleA( szModule );

			if ( !hModule )
			{
				DWORD dwMsecFind = 0;

				while ( !hModule )
				{
					if ( dwMsecFind == dwMsec )
						return false;

					hModule = FastCall::G().t_GetModuleHandleA( szModule );

					HANDLE hEvent = FastCall::G().t_CreateEventA( 0 , true , false , 0 );

					if (!hEvent)
						return false;

					FastCall::G().t_WaitForSingleObject(hEvent, dwModuleDelay);
					FastCall::G().t_CloseHandle( hEvent );

					dwMsecFind += dwModuleDelay;
				}
			}

			return true;
		}

		/* Get Module File Path */

		string GetModuleFilePath( HMODULE hModule )
		{
			string ModuleName = "";
			char szFileName[MAX_PATH] = { 0 };

			if (FastCall::G().t_GetModuleFileNameA( hModule , szFileName , MAX_PATH ) )
				ModuleName = szFileName;

			return ModuleName;
		}

		/* Get Module Dir */

		string GetModuleBaseDir( HMODULE hModule )
		{
			string ModulePath = GetModuleFilePath( hModule );
			return ModulePath.substr( 0 , ModulePath.find_last_of( "\\/" ) );
		}
	}
}