///-----------------------------------------------------------------
///
/// @file      TangramDlg.cpp
/// @author    Krzysiek
/// Created:   2012-12-19 20:39:16
/// @section   DESCRIPTION
///            TangramDlg class implementation
///
///------------------------------------------------------------------

#include "TangramDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// TangramDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(TangramDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(TangramDlg::OnClose)
	
	EVT_UPDATE_UI(ID_WXPANEL1,TangramDlg::WxPanel1UpdateUI)
END_EVENT_TABLE()
////Event Table End

TangramDlg::TangramDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

TangramDlg::~TangramDlg()
{
} 

void TangramDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(5, 5), wxSize(335, 344));
	WxBoxSizer1->Add(WxPanel1, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxPanel2 = new wxPanel(this, ID_WXPANEL2, wxPoint(407, 122), wxSize(185, 147));
	WxBoxSizer1->Add(WxPanel2, 0, wxALIGN_RIGHT | wxEXPAND | wxALL, 5);

	SetTitle(_("Tangram"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
}

void TangramDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * WxPanel1UpdateUI
 */
void TangramDlg::WxPanel1UpdateUI(wxUpdateUIEvent& event)
{
	RepaintMainPanel();
}

void TangramDlg::RepaintMainPanel(){
    int w,h;
    wxClientDC dc1(WxPanel1);
    wxBufferedDC dc(&dc1); 
    dc.SetBackground(wxBrush(RGB(56,89,223)));
    dc.Clear(); 
    WxPanel1->GetSize(&w,&h);
    dc.SetDeviceOrigin(w/2,h/2);
    
    dc.DrawRectangle(-10,-10,10,10);
}

/*
 * TangramDlgMiddleDown
 */
void TangramDlg::TangramDlgMiddleDown(wxMouseEvent& event)
{
	// insert your code here
}
