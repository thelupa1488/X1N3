#pragma once

#include "CSX.h"

namespace CSX
{
	namespace Utils
	{
//[swap_lines]
		/* Wait dwMsec Load Module */
		bool IsModuleLoad( PCHAR szModule , DWORD dwMsec = 5000 );

		/* Get Module File Path */
		string GetModuleFilePath( HMODULE hModule );

		/* Get Module Dir */
		string GetModuleBaseDir( HMODULE hModule );
//[/swap_lines]
	}
}