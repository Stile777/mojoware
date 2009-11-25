/***********************************************************************************************************************
/*
/*    cWinMain.h / mojo_app
/*
/*    This class is a wrapper for the program's main window.  The main window does its work by filling 
/*    its client area with various child dialog boxes.  This class has separate files for its window proc
/*    and WM_COMMAND handler.
/* 
/*    Copyright 2009 Robert Sacks.  See end of file for more info.
/*
/**********************************************************************************************************************/

#pragma once

#include "cWin.h"
#include "cDlgMonitor.h"
#include "cDlgMessageBox.h"


//=======================================================================================================
// CLASS
//=======================================================================================================

class cWinMain : public cWin
{
public:

	cWinMain () { pClassName = L"cWinMain"; }
	void load_script_sub();

private:

	void wm_command ( WPARAM wParam, LPARAM lParam );
	void on_create ( HWND hwnd );

	wchar_t * pClassName; // = L"cWinMain";

	cDlgMonitor DlgMonitor;
	cDlgMessageBox MB;

public:

	static LRESULT CALLBACK window_proc ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
};


/***********************************************************************************************************************
/*
/*    This file is part of Mojo.  For more information, see http://mojoware.org.
/*
/*    You may redistribute and/or modify Mojo under the terms of the GNU General Public License, version 3, as
/*    published by the Free Software Foundation.  You should have received a copy of the license with mojo.  If you
/*    did not, go to http://www.gnu.org.
/* 
/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
/*    NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
/*    IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
/*    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
/*    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
/*    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
/*    EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
/*
/***********************************************************************************************************************/
