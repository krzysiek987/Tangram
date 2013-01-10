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
#include <wx/brush.h>
#include <wx/colour.h>
#include <wx/pen.h>
#include <wx/msgdlg.h>
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
	EVT_LEFT_DOWN(TangramDlg::TangramDlgLeftDown0)
	EVT_LEFT_UP(TangramDlg::TangramDlgLeftUP)
	
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

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(5, 5), wxSize(800, 600));
	WxBoxSizer1->Add(WxPanel1, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	SetTitle(_("Tangram"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
	
	tans[0]=new Rect(wxPoint(200,400),wxPoint(100,300),wxPoint(200,200),wxPoint(300,300));
	tans[1]=new Rect(wxPoint(300,300),wxPoint(300,100),wxPoint(400,0),wxPoint(400,200));
	tans[2]=new Triangle(wxPoint(0,400),wxPoint(200,400),wxPoint(100,300));
	tans[3]=new Triangle(wxPoint(200,400),wxPoint(400,400),wxPoint(400,200));
	tans[4]=new Triangle(wxPoint(0,400),wxPoint(0,0),wxPoint(200,200));
	tans[5]=new Triangle(wxPoint(300,300),wxPoint(300,100),wxPoint(200,200));
	tans[6]=new Triangle(wxPoint(0,0),wxPoint(400,0),wxPoint(200,200));
	tans[7]=new Triangle(wxPoint(200,200),wxPoint(300,300),wxPoint(300,100));
	
	mouseDown=false;
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

void TangramDlg::RepaintMainPanel(bool click){
    int w,h;
    wxClientDC dc1(WxPanel1);
    wxBufferedDC dc(&dc1); 
    dc.SetBackground(wxBrush(RGB(56,89,223)));
    dc.Clear(); 
    WxPanel1->GetSize(&w,&h);
    PaintTans(dc);
    if(click){
        dc.DrawRectangle(400,400,500,500);
    }
    

}
void TangramDlg::PaintTans(wxBufferedDC& dc){
    for(int i=0;i<TANS_NO;i++){
        if(tans[i] != NULL) {
            dc.SetPen(wxPen(wxColour(0,0,0), 3 ));
            dc.SetBrush(wxBrush(wxColour(255*i/8,50,25)));
            dc.DrawPolygon(tans[i]->GetSize(),tans[i]->GetPoints());
        }
    }
    
        
}



/*
 * TangramDlgLeftDown0
 */
void TangramDlg::TangramDlgLeftDown0(wxMouseEvent& event)
{
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Download completed"), wxT("Info"), wxOK);
    dial->ShowModal();
    mouseDown=true;
    RepaintMainPanel(true);
    for(int i=0;i<TANS_NO;i++){
        if(tans[i]->IsInner(event.GetX(), event.GetY())){
               RepaintMainPanel(true);
        }
    }
	// insert your code here
}

/*
 * TangramDlgLeftUP
 */
void TangramDlg::TangramDlgLeftUP(wxMouseEvent& event)
{
    mouseDown=false;
	// insert your code here
}
