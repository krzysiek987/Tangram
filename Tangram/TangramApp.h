//---------------------------------------------------------------------------
//
// Name:        TangramApp.h
// Author:      Krzysiek
// Created:     2012-12-19 20:39:16
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __TANGRAMDLGApp_h__
#define __TANGRAMDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class TangramDlgApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
