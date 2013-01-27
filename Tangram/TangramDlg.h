///-----------------------------------------------------------------
///
/// @file      TangramDlg.h
/// @author    Krzysiek
/// Created:   2012-12-19 20:39:16
/// @section   DESCRIPTION
///            TangramDlg class declaration
///
///------------------------------------------------------------------
//
#ifndef __TANGRAMDLG_H__
#define __TANGRAMDLG_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/sizer.h>
////Header Include End
#include <wx/brush.h>
#include <wx/colour.h>
#include <wx/pen.h>
#include <wx/dcbuffer.h>
#include "data/Rect.h"
#include "data/Triangle.h"
#include "data/Shadow.h"
#include "panel/TangramPanel.h"
#include "data/Constants.h"
#include "data/vecmat.h"
#include <fstream>

////Dialog Style Start
#undef TangramDlg_STYLE
#define TangramDlg_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End


class TangramDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		TangramDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Tangram"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = TangramDlg_STYLE);
		virtual ~TangramDlg();
		void WxPanel1UpdateUI(wxUpdateUIEvent& event);
		void RepaintMainPanel();
		void PaintTans(wxBufferedDC& dc);
        void MouseLeftDown(wxMouseEvent& event);
        void MouseLeftUp(wxMouseEvent& event);
        void MouseMoved(wxMouseEvent& event);
        void MouseLeftDoubleClick(wxMouseEvent& event);
        void MouseRightClick(wxMouseEvent& event);
        Tan* CheckIsIn(int x,int y);
	    void MoveHoldedTan(wxMouseEvent& event);
        void RotateHoldedTan(wxMouseEvent& event);
        bool Check();
		void NextClick(wxCommandEvent& event);
		void PreviousClick(wxCommandEvent& event);
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxStaticText *Label;
		wxButton *Next;
		wxButton *Previous;
		wxBoxSizer *WxBoxSizer2;
		wxPanel *WxPanel1;
		wxBoxSizer *WxBoxSizer1;
		////GUI Control Declaration End
		Tan *tans[TANS_NO];
		Shadow* shadows;
		int actual_shadow;
		int number_of_shadows;
		bool isRotateMode;
		Tan *holded;
		int holdedX,holdedY;
		wxPoint center;
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_LABEL = 1007,
			ID_NEXT = 1006,
			ID_PREVIOUS = 1005,
			ID_WXPANEL1 = 1002,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
