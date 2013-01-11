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
	
	isRotateMode=false;
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
    Tan* hit=CheckIsIn(event.GetX(), event.GetY());
    if(hit != NULL){
        holded=hit;
        holdedX=event.GetX();
        holdedY=event.GetY();
    }
}
void TangramDlg::MouseLeftUp(wxMouseEvent& event){
    isRotateMode=false;
    holded=NULL;
    holdedX=0;
    holdedY=0;
}
void TangramDlg::MouseMoved(wxMouseEvent& event){
    if(holded != NULL ) {
        if(!isRotateMode){
            MoveHoldedTan(event);
        }
        else {
            RotateHoldedTan(event);    
        }
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
        //printf("klik w %d , %d   ",x,y);
        if(tans[i]->IsIn(x,y)) {
            if(tans[i]->IsInner(x, y)){
                if(tans[i]->IsInCenterCircle(x,y)){
                    isRotateMode=false;    
                }
                else {
                    isRotateMode=true;
                    center=tans[i]->GetCenter();
                    printf("center : %d, %d ", center.x,center.y);
                    wxPoint* points=tans[i]->GetPoints(); 
                    printf(" [%d,%d] , [%d,%d] , [%d,%d] , [%d,%d] \n",points[0].x,points[0].y,points[1].x,points[1].y,points[2].x,points[2].y,points[3].x,points[3].y);
                    for(int j=0;j<tans[i]->GetSize();j++){
                        vectors[j].Set(points[j]-center);   
                    }
                    printf(" [%lf,%lf] , [%lf,%lf] , [%lf,%lf] , [%lf,%lf] \n",vectors[0].GetX(),vectors[0].GetY(),vectors[1].GetX(),vectors[1].GetY(),vectors[2].GetX(),vectors[2].GetY(),vectors[3].GetX(),vectors[3].GetY());//printf("hold: [%d,%d] ,  center:  [%d,%d],    event    [%d,%d]   \n",holdedX,holdedY,center.x,center.x,event.GetX(),event.GetY());    
    
                }
                //printf("trafiono %d   \n",i);
                return tans[i];
            } 
            else {
                //printf(" NIE trafiono %d   \n",i);  
            }
        }
        else {
            //printf(" NIE NIE NIE trafiono %d   \n",i); 
        } 
    }  
    return NULL;
}

void TangramDlg::MoveHoldedTan(wxMouseEvent& event){
    //printf("przesuwam X %d -> %d , Y %d -> %d \n",holdedX,event.GetX(),holdedY,event.GetY());
    ActualMoveInfo info=holded->Move(event.GetX()-holdedX,event.GetY()-holdedY); 
    holdedX+=info.GetActualMoveX();
    holdedY+=info.GetActualMoveY();   
    //printf("handled [%d,%d]  \n",holdedX,holdedY);    
}

void TangramDlg::RotateHoldedTan(wxMouseEvent& event){
    printf("obracam  hold [%d,%d] , center [%d,%d] ,  event [%d,%d] \n",holdedX,holdedY,center.x,center.y,event.GetX(),holdedY,event.GetY());
    printf("obracam  hold - center [%d,%d] ,  event - center [%d,%d] \n",holdedX-center.x,holdedY-center.y,event.GetX()-center.x,event.GetY()-center.y);
    wxPoint* points=holded->GetPoints();    
    //printf("size - %d \n",holded->GetSize());
    //printf(" [%d,%d] , [%d,%d] , [%d,%d] , [%d,%d] \n",points[0].x,points[0].y,points[1].x,points[1].y,points[2].x,points[2].y,points[3].x,points[3].y);
    //printf(" [%lf,%lf] , [%lf,%lf] , [%lf,%lf] , [%lf,%lf] \n",vectors[0].GetX(),vectors[0].GetY(),vectors[1].GetX(),vectors[1].GetY(),vectors[2].GetX(),vectors[2].GetY(),vectors[3].GetX(),vectors[3].GetY());//printf("hold: [%d,%d] ,  center:  [%d,%d],    event    [%d,%d]   \n",holdedX,holdedY,center.x,center.x,event.GetX(),event.GetY());    
    double rad=VectorUtils::AngleBetweenPointsInRadians(wxPoint(holdedX,holdedY),wxPoint(center.x,center.y),wxPoint(event.GetX(),event.GetY()));
    //printf("degreee  %lf   \n",rad); 
    if(holdedX>event.GetX() || holdedY < event.GetY()){
        rad=-rad;   
    }
    if(rad>0.001){
        Matrix matrix;
        matrix.data[0][0]=cos(rad); matrix.data[0][1]=-sin(rad);     
        matrix.data[1][0]=sin(rad); matrix.data[1][1]=cos(rad);
        for(int i=0;i<holded->GetSize();i++){
            vectors[i]=matrix*vectors[i];
        }
        holdedX=event.GetX();
        holdedY=event.GetY();
    }
    for(int i=0;i<holded->GetSize();i++){    
        points[i].x=vectors[i].GetX()+center.x;
        points[i].y=vectors[i].GetY()+center.y;
    }   
    
}
