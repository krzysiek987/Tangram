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
	//inicjalizuje figury (tak jak sa pociete)
	tans[0]=new Rect(wxPoint(200,400),wxPoint(100,300),wxPoint(200,200),wxPoint(300,300)); //kwadrat
	tans[1]=new Rect(wxPoint(300,300),wxPoint(300,100),wxPoint(400,0),wxPoint(400,200)); // rownoleglobok
	tans[1]->type=1;
	tans[2]=new Triangle(wxPoint(0,400),wxPoint(200,400),wxPoint(100,300)); //maly trojkat dol
	tans[3]=new Triangle(wxPoint(300,400),wxPoint(500,400),wxPoint(500,200)); // trojkat dol
	tans[3]->type=2;
	tans[4]=new Triangle(wxPoint(0,400),wxPoint(0,0),wxPoint(200,200)); //duzy trojkat lewa
	tans[5]=new Triangle(wxPoint(300,300),wxPoint(300,100),wxPoint(200,200)); //trojkat srodek
	tans[6]=new Triangle(wxPoint(0,0),wxPoint(400,0),wxPoint(200,200)); // duzy trojkat gora
	//ustawiam na wstepnie flage odpowiadajaca za obrony na false i do aktualnie trzymanego obiektu wstawiam NULL
	isRotateMode=false;
	holded=NULL;
}

void TangramDlg::OnClose(wxCloseEvent& /*event*/)
{
    //kasuje wszystkie tany ktore byly wczeœniej tworzone przez new
    for(int i=0;i<TANS_NO;i++) delete tans[i];
	Destroy();
}
/************************************** METODY MALUJ¥CE NA PANELU ***************************************/
/*
 * WxPanel1UpdateUI event przemalowania panelu - wywo³uje dalsz¹ metodê która maluje tany na panelu
 */
void TangramDlg::WxPanel1UpdateUI(wxUpdateUIEvent& event)
{
	RepaintMainPanel();
}
/*
 * Metoda przemalowuj¹ca panel
 */
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
/******************************** EVENTY ****************************************/
/*
 * Event klikniecia lewym przyciskiem przekazywany z analogicznego eventu w TangramPanel
 */
void TangramDlg::MouseLeftDown(wxMouseEvent& event){
    //sprawdzam czy klikniêcie trafia w jakiœ tan (jesli trafia to jest zwracany)
    Tan* hit=CheckIsIn(event.GetX(), event.GetY());
    if(hit != NULL){
        //wstawiam do obiektu holded (aktualnie trzymanego) trafiony myszk¹ i pobieram do holdedX,holdedY wspó³rzedne klikniêcia
        holded=hit;
        holdedX=event.GetX();
        holdedY=event.GetY();
    }
}
/*
 * Event odklikniecia lewym przyciskiem przekazywany z analogicznego eventu w TangramPanel
 */
void TangramDlg::MouseLeftUp(wxMouseEvent& event){
    //zeruje informacje o aktualnie trzymanym obiekcie i miejscu klikniêcia
    isRotateMode=false;
    holded=NULL;
    holdedX=0;
    holdedY=0;
}
/*
 * Event przesuniecia myszki przekazywany z analogicznego eventu w TangramPanel
 */
void TangramDlg::MouseMoved(wxMouseEvent& event){
    //jezeli jakis obiekt jest trzymany myszka
    if(holded != NULL ) {
        if(!isRotateMode){
            //i nie jestesmy w trybie obracania przesuwamy go
            MoveHoldedTan(event);
        }
        else {
            //w przeciwnym razie obracamy
            RotateHoldedTan(event);    
        }
    };
}
/**************************************** METODY SPRAWDZAJACE KLIKNIECIA **********************************************/
/*
 * Metoda sprawdza czy w punkcie (x,y) jest jakas figura, jesli tak jest ona zwracana
 */
Tan* TangramDlg::CheckIsIn(int x,int y){
    //iteruje po tanach, sprawdzajac najpierw czy (x,y) trafia w prostokat opisany na tanie
    for(int i=0;i<TANS_NO;i++){
        if(tans[i]->IsIn(x,y)) {
            //jesli trafia to sprawdzam czy trafia dok³adnie w œrodek tana
            if(tans[i]->IsInner(x, y)){
                    //dodatkowo jeœli klikniecie jest w srodku figury ustawiam flage isRotateMode na false - odpowiada tryb przesuwania
                    if(tans[i]->IsInCenterCircle(x,y)){
                        isRotateMode=false;    
                    }
                    else {
                        //w przeciwnym przypadku aktywny jest tryb obracania, pobierany jest srodek tana
                        //nastepnie tan przesuwany jest do srodka ukladu wspolrzednych i zapisywany w tablicy vectors
                        isRotateMode=true;
                        center=tans[i]->GetCenter();
                        wxPoint* points=tans[i]->GetPoints(); 
                        for(int j=0;j<tans[i]->GetSize();j++){
                            vectors[j].Set(points[j]-center);   
                        }
                    }
                //trafiono - zwracam tan w który nast¹pi³o trafienie
                return tans[i];
            } 
        }
    }  
    //zwracam NULL - nie trafiono
    return NULL;
}

/*
 * Metoda przesuwa aktualnie trzymany tan o odleglosc wektor miedzy punktem klikniecia i poprzednio kliknietym punktem
 */
void TangramDlg::MoveHoldedTan(wxMouseEvent& event){
    ActualMoveInfo info=holded->Move(event.GetX()-holdedX,event.GetY()-holdedY,tans); 
    //przesuwamy punkt w który bylo klikniêcie o tyle ile naprawde siê uda³o przesun¹æ
    holdedX+=info.GetActualMoveX();
    holdedY+=info.GetActualMoveY();     
}

/*
 * Metoda obraca aktualnie trzymany tan
 */
void TangramDlg::RotateHoldedTan(wxMouseEvent& event){
    int eventX=event.GetX(),eventY=event.GetY();  
    //obliczam kat o jaki obrócony jest z iloczynu skalarnego i jesli kierunek ruchu  
    //myszki byl przeciwnie do wskazówek zegara zamieniam wynik na przeciwny
    double rad=VectorUtils::AngleBetweenPointsInRadians(wxPoint(holdedX,holdedY),wxPoint(center.x,center.y),wxPoint(eventX,eventY));
    if(VectorUtils::GetDirection(eventX,eventY,center.x,center.y,holdedX,holdedY)>0){
        rad=-rad;
    }
    //obracam tan ktory byl wczesniej przesuniety do srodka ukladu wspolrzednych
    RotateVectors(rad);
    //tworze tan ktory jest obroconym cofnietym wczesniejsze przesuniecie do srodka i sprawdzam
    //czy ten testowy tan nie koliduje z którymœ z pozosta³ych
    Tan* tan=GetTestTan();
    if(tan!=NULL){
        if(holded->Conflicts(tan,tans) || tan->IsOutsidePanel()){
            RotateVectors(-rad);
        }
        else {
            //przesuwam trzymany obiekt ze srodka ukladu wspolrzednych i ustawiam wspolrzedne ostatniego polozenia myszki
            for(int i=0;i<holded->GetSize();i++){   
                holded->SetP(i+1,wxPoint(vectors[i].GetX()+center.x,vectors[i].GetY()+center.y));
            }   
            holdedX=eventX;
            holdedY=eventY;   
        }
        delete tan;
    } 
}

/*
 * Metoda obraca wektory w tablicy vectors o podany k¹t
 */
void TangramDlg::RotateVectors(double rad){
    Matrix matrix;
    matrix.data[0][0]=cos(rad); matrix.data[0][1]=-sin(rad);     
    matrix.data[1][0]=sin(rad); matrix.data[1][1]=cos(rad);
    for(int i=0;i<holded->GetSize();i++){
        vectors[i]=matrix*vectors[i];
    }
}

/*
 * Metoda tworzy testowy tan przywracajac przechowywane punkty w tablicy vectors ze œrodka uk³adu wspó³rzêdnych
 */
Tan* TangramDlg::GetTestTan(){
    if(holded->GetSize()==3){
        return new Triangle(wxPoint(vectors[0].GetX()+center.x,vectors[0].GetY()+center.y),
                                wxPoint(vectors[1].GetX()+center.x,vectors[1].GetY()+center.y),
                                wxPoint(vectors[2].GetX()+center.x,vectors[2].GetY()+center.y));
    } else if(holded->GetSize()==4){
        return new Rect  (wxPoint(vectors[0].GetX()+center.x,vectors[0].GetY()+center.y),
                            wxPoint(vectors[1].GetX()+center.x,vectors[1].GetY()+center.y),
                            wxPoint(vectors[2].GetX()+center.x,vectors[2].GetY()+center.y),
                            wxPoint(vectors[3].GetX()+center.x,vectors[3].GetY()+center.y));
    }
    return NULL;
}

