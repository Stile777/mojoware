/*************************************************************************************************
/*
/*   cScrobIm.cpp
/*   
/*   started October 16, 2008
/*   
/*************************************************************************************************/

#include "stdafx.h"
#include "cScrobIm.h"

using namespace Gdiplus;

//===============================================================================================
// DATA
//===============================================================================================



//===============================================================================================
// PROTOTYPES
//===============================================================================================


//===============================================================================================
// CODE
//===============================================================================================

//----------------------------------------------------------------------------------------------
// POINT IS TRANSPARENT
//----------------------------------------------------------------------------------------------
bool cScrobIm :: point_is_transparent ( HDC hdc, int iIndex, int x, int y )
{
	IMAGEINFO ii;

	if ( 0 == ImageList_GetImageInfo ( hIL, iIndex, &ii ) )
	{
		assert(0);
		LOG_SYSTEM_ERROR_T ( L"ImageList_GetImageInfo" );
		return false;
	}
	
	SelectObject ( hdc, HGDIOBJ ( ii.hbmMask ) );

	COLORREF c = GetPixel ( hdc, x, y );
	
	if ( c == 0x00FFFFFF )
		return true;

	else
		return false;
}



//----------------------------------------------------------------------------------------------
// SET
//----------------------------------------------------------------------------------------------
void cScrobIm::set ( int x, int y, HIMAGELIST hArgIL )  // use this to change size and images -- it releases old list
{
	if ( this->hIL )
		ImageList_Destroy ( hIL );

	this->Dim.x = x;
	this->Dim.y = y;
	hIL = hArgIL;
}



//----------------------------------------------------------------------------------------------
// GET RECT
//----------------------------------------------------------------------------------------------
RECT * cScrobIm::get_rect ( RECT * r )
{

	r->left = Pos.x;
	r->top = Pos.y;
	r->right = Pos.x + Dim.x;
	r->bottom = Pos.y + Dim.y;

	return r;
}


//----------------------------------------------------------------------------------------------
// ADD SCROB
//----------------------------------------------------------------------------------------------