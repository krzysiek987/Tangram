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
	tans[0]=new Rect(wxPoint(80,160),wxPoint(40,120),wxPoint(80,80),wxPoint(120,120)); //kwadrat
	tans[1]=new Rect(wxPoint(120,120),wxPoint(120,40),wxPoint(160,0),wxPoint(160,80)); // rownoleglobok
	tans[2]=new Triangle(wxPoint(0,160),wxPoint(80,160),wxPoint(40,120)); //maly trojkat dol
	tans[3]=new Triangle(wxPoint(80,160),wxPoint(160,160),wxPoint(160,80)); // trojkat dol
	tans[4]=new Triangle(wxPoint(0,160),wxPoint(0,0),wxPoint(80,80)); //duzy trojkat lewa
	tans[5]=new Triangle(wxPoint(120,120),wxPoint(120,40),wxPoint(80,80)); //trojkat srodek
	tans[6]=new Triangle(wxPoint(0,0),wxPoint(160,0),wxPoint(80,80)); // duzy trojkat gora
	//ustawiam na wstepnie flage odpowiadajaca za obrony na false i do aktualnie trzymanego obiektu wstawiam NULL
	isRotateMode=false;
	holded=NULL;
	//dodanie cienia figury uk³adanej
	int size = 12;
	wxPoint points[12];
	points[0] = wxPoint(200,200);
	points[1] = wxPoint(200,314);
	points[2] = wxPoint(485,314);
	points[3] = wxPoint(485,200);
	points[4] = wxPoint(428,200);
	points[5] = wxPoint(428,257);
	points[6] = wxPoint(371,257);
	points[7] = wxPoint(371,200);
	points[8] = wxPoint(314,200);
	points[9] = wxPoint(314,257);
	points[10] = wxPoint(257,257);
	points[11] = wxPoint(257,200);
	wxPoint check_points[12];
	check_points[0] = wxPoint(198,198);
	check_points[1] = wxPoint(198,316);
	check_points[2] = wxPoint(489,316);
	check_points[3] = wxPoint(487,198);
	check_points[4] = wxPoint(426,198);
	check_points[5] = wxPoint(426,255);
	check_points[6] = wxPoint(373,255);
	check_points[7] = wxPoint(373,198);
	check_points[8] = wxPoint(312,198);
	check_points[9] = wxPoint(312,255);
	check_points[10] = wxPoint(259,255);
	check_points[11] = wxPoint(259,198);
	shadow.Set(size,points,check_points);
	
	for(int i=0;i<TANS_NO;++i) {
        tans[i]->SetShadow(&shadow);   
    }

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
    
    dc.SetPen(wxPen(wxColour(0,0,0), 3 ));
    dc.SetBrush(wxBrush(wxColour(150,150,150)));
    dc.DrawPolygon(shadow.GetSize(),shadow.GetPoints());
    
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
    Check();
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
    for(int i=0;i<ANGLE_NO;++i) {
        if(rad>(2*(ANGLE_NO-i)-1)*M_PI/(2*ANGLE_NO)) {rad = (ANGLE_NO-i)*M_PI/ANGLE_NO;break;}
    }
    if(rad>=M_PI/ANGLE_NO) {
        if(VectorUtils::GetDirection(eventX,eventY,center.x,center.y,holdedX,holdedY)>0){
            rad=-rad;
        }
        //obracam tan ktory byl wczesniej przesuniety do srodka ukladu wspolrzednych
        Tan* temp_tan;
        if(holded->GetSize()==3) {
            temp_tan = new Triangle(holded->GetP1(),holded->GetP2(),holded->GetP3());
        }
        else {
            temp_tan = new Rect(holded->GetP1(),holded->GetP2(),holded->GetP3(),holded->GetP4());
        }
        temp_tan->RotateTan(rad,center);
        //tworze tan ktory jest obroconym cofnietym wczesniejsze przesuniecie do srodka i sprawdzam
        //czy ten testowy tan nie koliduje z którymœ z pozosta³ych
        if(!holded->Conflicts(temp_tan,tans) && !temp_tan->IsOutsidePanel()){
            //przesuwam trzymany obiekt ze srodka ukladu wspolrzednych i ustawiam wspolrzedne ostatniego polozenia myszki
            holded->RotateTan(rad,center);
            holdedX=eventX;
            holdedY=eventY;   
        }
        delete temp_tan;
        
    }
}

bool TangramDlg::Check()
{
    double degrees = 0.0;
    double angle;
    wxPoint* shadow_points = shadow.GetCheckPoints();
    int shadow_size = shadow.GetSize();
    for(int i=0;i<TANS_NO;++i){
        wxPoint* tan_points = tans[i]->GetPoints();
        for(int j=0;j<tans[i]->GetSize();++j) { 
            for(int k=0;k<shadow.GetSize();++k){
                angle = VectorUtils::AngleBetweenPoints(shadow_points[k],tan_points[j],shadow_points[(k+1)%shadow_size]);
                if(VectorUtils::GetDirection(shadow_points[k].x,shadow_points[k].y,tan_points[j].x,tan_points[j].y,
                        shadow_points[(k+1)%shadow_size].x,shadow_points[(k+1)%shadow_size].y)>0){
                    angle=-angle;
                }
                degrees += angle;
            }
            if(abs(degrees-360.0) > EPSILON) return false;
            degrees = 0.0;
        }
        wxPoint tan_center = tans[i]->GetCenter();
        for(int k=0;k<shadow.GetSize();++k){
            angle = VectorUtils::AngleBetweenPoints(shadow_points[k],tan_center,shadow_points[(k+1)%shadow_size]);
            if(VectorUtils::GetDirection(shadow_points[k].x,shadow_points[k].y,tan_center.x,tan_center.y,
                    shadow_points[(k+1)%shadow_size].x,shadow_points[(k+1)%shadow_size].y)>0){
                angle=-angle;
            }
            degrees += angle;
        }
        if(abs(degrees-360.0) > EPSILON) return false;
        degrees = 0.0;
    }
    printf("U³o¿one!!!\n");
    return true;
}

