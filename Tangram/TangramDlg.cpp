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

	WxPanel1 = new TangramPanel(this, ID_WXPANEL1, wxPoint(5, 5), wxSize(800, 600));
	WxBoxSizer1->Add(WxPanel1, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("WxButton1"), wxPoint(815, 292), wxSize(75, 25), 0, wxDefaultValidator, _("WxButton1"));
	WxBoxSizer1->Add(WxButton1, 0, wxALIGN_CENTER | wxALL, 5);

	SetTitle(_("Tangram"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
	
	tans[0]=new Rect(wxPoint(200,400),wxPoint(100,300),wxPoint(200,200),wxPoint(300,300)); //kwadrat
	tans[1]=new Rect(wxPoint(300,300),wxPoint(300,100),wxPoint(400,0),wxPoint(400,200)); // rownoleglobok
	tans[2]=new Triangle(wxPoint(0,400),wxPoint(200,400),wxPoint(100,300)); //maly trojkat dol
	tans[3]=new Triangle(wxPoint(300,400),wxPoint(500,400),wxPoint(500,200)); // trojkat dol
	tans[4]=new Triangle(wxPoint(0,400),wxPoint(0,0),wxPoint(200,200)); //duzy trojkat lewa
	tans[5]=new Triangle(wxPoint(300,300),wxPoint(300,100),wxPoint(200,200)); //trojkat srodek
	tans[6]=new Triangle(wxPoint(0,0),wxPoint(400,0),wxPoint(200,200)); // duzy trojkat gora
	
	_mouseDown=false;
	holded=NULL;
}

void TangramDlg::OnClose(wxCloseEvent& /*event*/)
{
    for(int i=0;i<TANS_NO;i++) delete tans[i];
	Destroy();
}

/*
 * WxPanel1UpdateUI
 */
void TangramDlg::WxPanel1UpdateUI(wxUpdateUIEvent& event)
{
	RepaintMainPanel();
}

void TangramDlg::MouseLeftDown(wxMouseEvent& event){
    _mouseDown=true;
    Tan* hit=CheckIsIn(event.GetX(), event.GetY());
    if(hit != NULL){
        holded=hit;
        holdedX=event.GetX();
        holdedY=event.GetY();
    }
}
void TangramDlg::MouseLeftUp(wxMouseEvent& event){
    _mouseDown=false;
    holded=NULL;
}
void TangramDlg::MouseMoved(wxMouseEvent& event){
    if(holded != NULL) {
        printf("%d , %d \n",event.GetX(),event.GetY());
        if(!holded->Move(event.GetX()-holdedX,event.GetY()-holdedY)) {
            //printf("POZA");
            return;
        }  
        holdedX=event.GetX();
        holdedY=event.GetY(); 
    };
}

void TangramDlg::RepaintMainPanel(){
    int w,h;
    wxClientDC dc1(WxPanel1);
    wxBufferedDC dc(&dc1); 
    dc.SetBackground(wxBrush(RGB(56,89,223)));
    dc.Clear(); 
    WxPanel1->GetSize(&w,&h);
    PaintTans(dc);
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

Tan* TangramDlg::CheckIsIn(int x,int y){
    for(int i=0;i<TANS_NO;i++){
        printf("klik w %d , %d   ",x,y);
        if(tans[i]->IsIn(x,y)) {
            
            if(tans[i]->IsInner(x, y)){
                printf("trafiono %d   \n",i);
                return tans[i];
            } 
            else {
                printf(" NIE trafiono %d   \n",i);  
            }
        }
        else {
            printf(" NIE NIE NIE trafiono %d   \n",i); 
        } 
    }  
    return NULL;
}



