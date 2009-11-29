/***********************************************************************************************************************
/*
/*    scrib_compiler
/*
/*    Copyright Robert Sacks 2009.
/*
/**********************************************************************************************************************/


#include "stdafx.h"
#include "..\\mojo_engine\\cLog.h"

using namespace mojo;

#include "cFile.h"

//======================================================================================================================
//  PROTOTYPES
//======================================================================================================================

void print_header ( cFileOut * pOut );
void print_footer ( cFileOut * pOut );
void do_it ( const wchar_t * pIn, const wchar_t * pOut );


//======================================================================================================================
//  CODE 
//======================================================================================================================




//----------------------------------------------------------------------------------------------------------------------
//  MAIN
//----------------------------------------------------------------------------------------------------------------------
void _tmain(int iArgQty, _TCHAR * apArg[])
{
	UNREFERENCED_PARAMETER ( iArgQty );
	UNREFERENCED_PARAMETER ( apArg );

	printf ( "scrib_compiler" );

#if 0
	do_it ( L"..\\osbxr\\gpl3.txt", L"..\\osbxr\\gpl3.cpp" );
#endif

	do_it ( L"..\\mojo_engine\\mojo_engine.scribs.english.txt", L"..\\mojo_engine\\default_scribs.cpp" );
	do_it ( L"..\\mojo_app\\mojo_app.scribs.english.txt", 		L"..\\mojo_app\\default_scribs.cpp" );
}


//----------------------------------------------------------------------------------------------------------------------
//  DO IT
//----------------------------------------------------------------------------------------------------------------------
void do_it ( const wchar_t * pIn, const wchar_t * pOut )
{

	cFileIn In ( pIn );

	if ( ! In.h )
	{
		printf ( "Unable to open in file\n." );
		return;
	}

	cFileOut Out ( pOut );

	if ( ! Out.h )
	{
		printf ( "Unable to open out file\n." );
		return;
	}

	print_header ( &Out );

	cStrW s;


	// while ( WEOF != ( c = getwc ( In.h ) ) )
    while ( In.get_line ( &s ) )
	{
		s.trim_right_space();

		if ( 0 == s.len() )
			continue;

		if ( 2 <= s.len() )
			if ( ! wcsncmp ( L"//", s.cstr(), 2 ) )
			{
				s.erase();
				continue;
			}

		fwprintf ( Out.h, L"   L\"" );

		for ( const wchar_t * p = s.cstr(); *p; p++ )
		{
			if ( (*p) == L'\t' )
				fwprintf ( Out.h, L" " );

			else if ( (*p) == L'%' )
				fwprintf ( Out.h, L"%%" );

			else
				fwprintf ( Out.h, L"%c", *p );
		}

		fwprintf ( Out.h, L"\",\n" );

		s.erase();
	}

	print_footer ( &Out );
}


//----------------------------------------------------------------------------------------------------------------------
//  PRINT HEADER
//----------------------------------------------------------------------------------------------------------------------
void print_header ( cFileOut * pOut )
{

	cStrW sDate ( __WDATE__ );
	cStrW sTime ( __WTIME__ );

	fwprintf ( pOut->h, L"/*\n" ); ;
	fwprintf ( pOut->h, L"/*    default_scribs.cpp\n" );
	fwprintf ( pOut->h, L"/*\n" ); ;
	fwprintf ( pOut->h, L"/*    Generated by scrib_compiler.exe on %s at %s\n", sDate.cstr(), sTime.cstr() );
	fwprintf ( pOut->h, L"/*\n" ); ;
	fwprintf ( pOut->h, L"/*    Copyright Robert Sacks 2009\n" );
	fwprintf ( pOut->h, L"*/\n" );
	fwprintf ( pOut->h, L"\n\n" );

	fwprintf ( pOut->h, L"const wchar_t * g_apDefaultScribs [] =\n" );
	fwprintf ( pOut->h, L"{\n" );

}

//----------------------------------------------------------------------------------------------------------------------
//  PRINT FOOTER
//----------------------------------------------------------------------------------------------------------------------
void print_footer( cFileOut * pOut )
{
	fwprintf ( pOut->h, L"   0\n" );
	fwprintf ( pOut->h, L"};\n\n" );

}

///////////////////////////////////

#if 0
//----------------------------------------------------------------------------------------------------------------------
//  DO GPL
//----------------------------------------------------------------------------------------------------------------------
void do_gpl3( cFileOut &Out, cFileIn In )
{
	// while ( WEOF != ( c = getwc ( In.h ) ) )

	cStrW s;

	fwprintf ( Out.h, L"//\n" );
	fwprintf ( Out.h, L"//\n" );
	fwprintf ( Out.h, L"//\tgpl3.cpp / osbxr\n" );
	fwprintf ( Out.h, L"//\n" );
	fwprintf ( Out.h, L"//\n\n" );


	fwprintf ( Out.h, L"static const wchar_t * apwGPL3 [] =\n" );
	fwprintf ( Out.h, L"{\n" );

    while ( In.get_line ( &s ) )
	{
		s.trim_left_space();
		s.trim_right_space();

		if ( 0 == s.len() )
		{
			fwprintf ( Out.h, L"\tL\"\\n\\n\",\n" );
			continue;
		}

		else
		{
			fwprintf ( Out.h, L"\tL\"" );

			for ( wchar_t * p = s.cstr(); *p; p++ )
			{
				if ( (*p) == L'\xFFFD' ) // copyright symbol
					fwprintf ( Out.h, L"(c)" );

				else if ( (*p) == L'\"' )
					fwprintf ( Out.h, L"\\\"" );

				else
					fwprintf ( Out.h, L"%c", *p );
			}

			fwprintf ( Out.h, L" \"," );
			fwprintf ( Out.h, L"\n" );
		}

		s.erase();
	}

	fwprintf ( Out.h, L"\n};" );

}
#endif