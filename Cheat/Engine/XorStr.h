#pragma once

#include <string>
#include <array>
#include <cstdarg>

#define BEGIN_NAMESPACE( x ) namespace x {
#define END_NAMESPACE }

BEGIN_NAMESPACE(XorCompileTime)

constexpr auto time = __TIME__;
constexpr auto seed = static_cast<int>(time[7]) + static_cast<int>(time[6]) * 10 + static_cast<int>(time[4]) * 60 + static_cast<int>(time[3]) * 600 + static_cast<int>(time[1]) * 3600 + static_cast<int>(time[0]) * 36000;

template < int N >
struct RandomGenerator {
private:
	static constexpr unsigned a = 16807; // 7^5
	static constexpr unsigned m = 2147483647; // 2^31 - 1

	static constexpr unsigned s = RandomGenerator< N - 1 >::value;
	static constexpr unsigned lo = a * (s & 0xFFFF); // Multiply lower 16 bits by 16807
	static constexpr unsigned hi = a * (s >> 16); // Multiply higher 16 bits by 16807
	static constexpr unsigned lo2 = lo + ((hi & 0x7FFF) << 16); // Combine lower 15 bits of hi with lo's upper bits
	static constexpr unsigned hi2 = hi >> 15; // Discard lower 15 bits of hi
	static constexpr unsigned lo3 = lo2 + hi;

public:
	static constexpr unsigned max = m;
	static constexpr unsigned value = lo3 > m ? lo3 - m : lo3;
};

template <>
struct RandomGenerator< 0 > {
	static constexpr unsigned value = seed;
};

template < int N, int M >
struct RandomInt {
	static constexpr auto value = RandomGenerator< N + 1 >::value % M;
};

template < int N >
struct RandomChar {
	static const char value = static_cast<char>(1 + RandomInt< N, 0x7F - 1 >::value);
};

template < size_t N, int K >
struct XorString {
private:
	const char _key;
	std::array< char, N + 1 > _encrypted;

	constexpr char enc(char c) const {
		return c ^ _key;
	}

	char dec(char c) const {
		return c ^ _key;
	}

public:
	template < size_t... Is >
	constexpr __forceinline XorString(const char* str, std::index_sequence< Is... >) : _key(RandomChar< K >::value), _encrypted{ enc(str[Is])... } {
	}

	__forceinline decltype(auto) decrypt(void)
	{

		for (size_t i = 0; i < N; ++i)
		{

			_encrypted[i] = dec(_encrypted[i]);

		}
		_encrypted[N] = '\0';

		return _encrypted.data();
	}
};

END_NAMESPACE

#pragma once

#define __cplusplus 0

#define HAS_EXCEPTIONS 0
#define _HAS_EXCEPTIONS 0

#define NDEBUG
#define _NDEBUG
#define __NDEBUG
#define NODEBUG
#define _NODEBUG
#define __NODEBUG
#define NO_DEBUG
#define _NO_DEBUG
#define __NO_DEBUG

#define NEXCEPT
#define _NEXCEPT
#define __NEXCEPT
#define NOEXCEPT
#define _NOEXCEPT
#define __NOEXCEPT
#define NO_EXCEPT
#define _NO_EXCEPT
#define __NO_EXCEPT
#define NOEXCEPTION
#define _NOEXCEPTION
#define __NOEXCEPTION
#define NOEXCEPTIONS
#define _NOEXCEPTIONS
#define __NOEXCEPTIONS
#define NO_EXCEPTION
#define _NO_EXCEPTION
#define __NO_EXCEPTION
#define NO_EXCEPTIONS
#define _NO_EXCEPTIONS
#define __NO_EXCEPTIONS

#define MBCS
#define _MBCS
#define __MBCS

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS_GLOBALS
#define _CRT_OBSOLETE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_MANAGED_HEAP_NO_WARNINGS

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE_GLOBALS
#define _CRT_OBSOLETE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_MANAGED_HEAP_NO_DEPRECATE

#define _CRT_SECURE_NOTHROW
#define _CRT_SECURE_C_NOTHROW
#define _CRT_SECURE_CPP_NOTHROW

#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

#define XS_DEBUG_WITH_LOGS 0
#define XS_ROUNDS 6

template < INT X > struct ENSURE_COMPILE_TIME { enum : INT { Value = X, }; };

#define XS_SEED ((__TIME__[4] - '0') * 60 + (__TIME__[3] - '0') * 600 + ( __TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 36000)

constexpr FORCEINLINE INT LINEAR_CONGRUENT_GENERATOR(INT Rounds)
{
	return 1013904223 + (1664525 * ((Rounds > NULL) ? (LINEAR_CONGRUENT_GENERATOR(Rounds - 1)) : (XS_SEED & 0xFFFFFFFF)));
};

#define XS_RANDOM( ) ( ENSURE_COMPILE_TIME < LINEAR_CONGRUENT_GENERATOR ( XS_ROUNDS ) > :: Value )
#define XS_RANDOM_NUMBER( Min, Max ) ( Min + ( XS_RANDOM ( ) % ( Max - Min + 1 ) ) )

template < INT ... Pack > struct XS_INDEX_LIST { };
template < typename XS_INDEX_LIST, INT Right > struct XS_APPEND;
template < INT ... Left, INT Right > struct XS_APPEND < XS_INDEX_LIST < Left ... >, Right > { typedef XS_INDEX_LIST < Left ..., Right > Result; };
template < INT N > struct XS_CONSTRUCT_INDEX_LIST { typedef typename XS_APPEND < typename XS_CONSTRUCT_INDEX_LIST < N - 1 > ::Result, N - 1 > ::Result Result; };
template < > struct XS_CONSTRUCT_INDEX_LIST < NULL > { typedef XS_INDEX_LIST < > Result; };

constexpr CONST CHAR CONST XS_XORKEY = static_cast <CONST CHAR CONST> (XS_RANDOM_NUMBER(NULL, 0x000000FF));

constexpr FORCEINLINE CONST CHAR CONST XS_ENCRYPT_CHARACTER(CONST CHAR CONST Character, INT Index)
{
	return Character ^ (XS_XORKEY + Index);
};

template < typename XS_INDEX_LIST > class XS;
template < INT ... Index > class XS < XS_INDEX_LIST < Index ... > >
{
private:
	CHAR Value[sizeof ... (Index) + 1 + __TIME__[3] - '0' + __TIME__[1] - '0' + __TIME__[0] - '0'] = { };

public:
	constexpr FORCEINLINE XS(CONST CHAR* CONST pszString)
		: Value{ XS_ENCRYPT_CHARACTER(pszString[Index], Index) ... } { };

	FORCEINLINE string Decrypt(VOID)
	{
		static INT Iter = NULL;

		for (Iter = NULL; Iter < sizeof ... (Index); Iter++)
		{
			Value[Iter] = Value[Iter] ^ (XS_XORKEY + Iter);
		};

		Value[sizeof ... (Index)] = NULL;
		return string(Value);
	};
};

#define XS_RANDOM_SIZE ( SIZE_T( MAX_PATH + __TIME__[3] - '0' + __TIME__[1] - '0' + __TIME__[0] - '0' + __TIME__[3] - '0' ) )

FORCEINLINE CONST VOID CONST xprintf(PCHAR pszBuffer, string Format, ...)
{
	static PCHAR pAp = NULL;
	va_start(pAp, Format), vsprintf(pszBuffer, Format.c_str(), pAp), va_end(pAp);
};

FORCEINLINE CONST VOID CONST xprintf(PCHAR pszBuffer, SIZE_T uSize, string Format, ...)
{
	static PCHAR pAp = NULL;
	va_start(pAp, Format), vsnprintf(pszBuffer, uSize, Format.c_str(), pAp), va_end(pAp);
};

#if defined(XS_DEBUG_WITH_LOGS) && XS_DEBUG_WITH_LOGS != 0

FORCEINLINE CONST VOID CONST xlogf(string Format, ...)
{
	static PCHAR pAp = NULL;
	static FILE* pFile = NULL;
	static CHAR szBuffer[XS_RANDOM_SIZE] = {};
	va_start(pAp, Format), vsnprintf(szBuffer, ARRAYSIZE(szBuffer), Format.c_str(), pAp), va_end(pAp);
	pFile = fopen(XorString("XS_LOGS.LOG"), XorString("a+"));
	fprintf(pFile, szBuffer);
	fclose(pFile);
};

#endif