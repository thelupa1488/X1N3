#pragma once

#include "CSX.h"

namespace CSX
{
	namespace Memory
	{
//[swap_lines]
		DWORD FindPatternV2(std::string moduleName, std::string Mask);
		DWORD FindSignature(const char* szModuleName, char* szPattern);

		/* Code Style Use Mask \x8B\xFF\xFF\xFF\xFF x???? */
		DWORD FindPattern( PCHAR pPattern , PCHAR pszMask , DWORD dwStart , DWORD dwEnd , DWORD dwOffset );
		DWORD FindPattern( PCHAR szModule , PCHAR pPattern , PCHAR pszMask , DWORD dwOffset );

		/* IDA Style 00 FF ?? */
		DWORD FindPattern( PCHAR pPattern , DWORD dwStart , DWORD dwEnd , DWORD dwOffset );
		DWORD FindPattern( PCHAR szModule , PCHAR pPattern , DWORD dwOffset );
//[/swap_lines]
	}
}