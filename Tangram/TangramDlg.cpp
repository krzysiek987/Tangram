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
	EVT_BUTTON(ID_NEXT,TangramDlg::NextClick)
	EVT_BUTTON(ID_PREVIOUS,TangramDlg::PreviousClick)
	
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

	WxBoxSizer1 = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxPanel1 = new TangramPanel(this, ID_WXPANEL1, wxPoint(5, 5), wxSize(800, 600));
	WxBoxSizer1->Add(WxPanel1, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer2, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	Previous = new wxButton(this, ID_PREVIOUS, _("Poprzedni"), wxPoint(5, 7), wxSize(75, 25), 0, wxDefaultValidator, _("Previous"));
	Previous->Enable(false);
	WxBoxSizer2->Add(Previous, 0, wxALIGN_RIGHT | wxALL, 5);

	Next = new wxButton(this, ID_NEXT, _("Nast�pny"), wxPoint(90, 7), wxSize(75, 25), 0, wxDefaultValidator, _("Next"));
	WxBoxSizer2->Add(Next, 0, wxALIGN_RIGHT | wxALL, 5);

	Label = new wxStaticText(this, ID_LABEL, _("U�o�y�e� poprawnie!!!"), wxPoint(175, 5), wxDefaultSize, 0, _("Label"));
	Label->SetForegroundColour(wxColour(255,0,0));
	Label->SetFont(wxFont(14, wxSWISS, wxITALIC, wxBOLD, false));
	WxBoxSizer2->Add(Label, 0, wxALIGN_RIGHT | wxALL, 5);

	SetTitle(_("Tangram"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
	Label->Hide();
	//inicjalizuje figury (tak jak sa pociete)
	tans[0]=new Rect(wxPoint(723,30),wxPoint(723,87),wxPoint(780,87),wxPoint(780,30)); //kwadrat
	tans[1]=new Rect(wxPoint(599,30),wxPoint(656,87),wxPoint(713,87),wxPoint(656,30)); // rownoleglobok
	tans[2]=new Triangle(wxPoint(750,117),wxPoint(636,231),wxPoint(750,231)); //duzy trojkat
	tans[3]=new Triangle(wxPoint(750,261),wxPoint(636,375),wxPoint(750,375)); //duzy trojkat
	tans[4]=new Triangle(wxPoint(693,405),wxPoint(636,463),wxPoint(750,463)); //�redni t�jk�t
	tans[5]=new Triangle(wxPoint(750,493),wxPoint(693,550),wxPoint(750,550)); //ma�y t�jk�t
    tans[6]=new Triangle(wxPoint(683,493),wxPoint(626,550),wxPoint(683,550)); //ma�y t�jk�t
	//ustawiam na wstepnie flage odpowiadajaca za obrony na false i do aktualnie trzymanego obiektu wstawiam NULL
	isRotateMode=false;
	holded=NULL;
	//dodanie cieni figury uk�adanej
	
	number_of_shadows = 0;
	actual_shadow = -1;
	int size;
	wxPoint *points;
	wxPoint *check_points;
	std::fstream file;
	file.open("tangrams.txt",std::ios::in);
	if(file.good()) {
    	file>>number_of_shadows;
    	shadows = new Shadow[number_of_shadows];
    	for(int i=0;i<number_of_shadows;++i) {
        	file>>size;
        	points = new wxPoint[size];
        	check_points = new wxPoint[size];
        	for(int j=0;j<size;++j) {
                file>>points[j].x>>points[j].y;
            }
            for(int j=0;j<size;++j) {
                file>>check_points[j].x>>check_points[j].y;
            }
            shadows[i].Set(size,points,check_points);
            delete check_points;
            delete points;
        }
    	file.close();
    }
	
	if(number_of_shadows>0) {
        actual_shadow = 0;
    	for(int i=0;i<TANS_NO;++i) {
            tans[i]->SetShadow(shadows);   
        }
    }

}

void TangramDlg::OnClose(wxCloseEvent& /*event*/)
{
    //kasuje wszystkie tany ktore byly wcze�niej tworzone przez new
    for(int i=0;i<TANS_NO;i++) delete tans[i];
	Destroy();
}
/************************************** METODY MALUJ�CE NA PANELU ***************************************/
/*
 * WxPanel1UpdateUI event przemalowania panelu - wywo�uje dalsz� metod� kt�ra maluje tany na panelu
 */
void TangramDlg::WxPanel1UpdateUI(wxUpdateUIEvent& event)
{
	RepaintMainPanel();
}
/*
 * Metoda przemalowuj�ca panel
 */
void TangramDlg::RepaintMainPanel(){
    int w,h;
    wxClientDC dc1(WxPanel1);
    wxBufferedDC dc(&dc1); 
    dc.SetBackground(wxBrush(RGB(56,89,223))); 
    dc.Clear(); 
    WxPanel1->GetSize(&w,&h);
    
    dc.SetBrush(wxColour(70,70,70));
    dc.DrawRectangle(WIDTH,0,800-WIDTH,HEIGHT);
    
    dc.SetPen(wxPen(wxColour(0,0,0), 3 ));
    dc.SetBrush(wxBrush(wxColour(150,150,150)));
    dc.DrawPolygon(shadows[actual_shadow].GetSize(),shadows[actual_shadow].GetPoints());
    
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
 * Event klikniecia lewym przyciskiem myszy przekazywany z analogicznego eventu w TangramPanel
 */
void TangramDlg::MouseLeftDown(wxMouseEvent& event){
    //sprawdzam czy klikni�cie trafia w jaki� tan (jesli trafia to jest zwracany)
    Tan* hit=CheckIsIn(event.GetX(), event.GetY());
    if(hit != NULL){
        //wstawiam do obiektu holded (aktualnie trzymanego) trafiony myszk� i pobieram do holdedX,holdedY wsp�rzedne klikni�cia
        holded=hit;
        holdedX=event.GetX();
        holdedY=event.GetY();
    }
}
/*
 * Event odklikniecia lewym przyciskiem myszy przekazywany z analogicznego eventu w TangramPanel
 */
void TangramDlg::MouseLeftUp(wxMouseEvent& event){
    //zeruje informacje o aktualnie trzymanym obiekcie i miejscu klikni�cia
    isRotateMode=false;
    holded=NULL;
    holdedX=0;
    holdedY=0;
    if(Check()) {
        Label->Show();
    }
    else Label->Hide();
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
/*
 * Event podw�jnego klikniecia lewym przyciskiem myszy przekazywany z analogicznego eventu w TangramPanel
 */
void TangramDlg::MouseLeftDoubleClick(wxMouseEvent& event){
    //sprawdzam czy klikni�cie trafia w jaki� tan (jesli trafia to jest zwracany)
    Tan* hit=CheckIsIn(event.GetX(), event.GetY());
    if(hit != NULL){
        //Symetri tana
        hit->Mirroring(tans);
    }
}
/*
 * Event klikniecia prawym przyciskiem myszy przekazywany z analogicznego eventu w TangramPanel
 */
void TangramDlg::MouseRightClick(wxMouseEvent& event){
    //sprawdzam czy klikni�cie trafia w jaki� tan (jesli trafia to jest zwracany)
    Tan* hit=CheckIsIn(event.GetX(), event.GetY());
    if(hit != NULL){
        //przeniesienie tana do zasobnika
        hit->GetBack();
    }
}
/**************************************** METODY SPRAWDZAJACE KLIKNIECIA **********************************************/
/*
 * Metoda sprawdza czy w punkcie (x,y) jest jakas figura, jesli tak jest ona zwracana
 */
Tan* TangramDlg::CheckIsIn(int x,int y){
    //iteruje po tanach, sprawdzajac najpierw czy (x,y) trafia w prostokat opisany na tanie
    for(int i=0;i<TANS_NO;i++){
        if(tans[i]->IsIn(x,y)) {
            //jesli trafia to sprawdzam czy trafia dok�adnie w �rodek tana
            if(tans[i]->IsInner(x, y)){
                    //dodatkowo je�li klikniecie jest w srodku figury ustawiam flage isRotateMode na false - odpowiada tryb przesuwania
                    if(tans[i]->IsInCenterCircle(x,y)){
                        isRotateMode=false;    
                    }
                    else {
                        //w przeciwnym przypadku aktywny jest tryb obracania, pobierany jest srodek tana
                        //nastepnie tan przesuwany jest do srodka ukladu wspolrzednych i zapisywany w tablicy vectors
                        isRotateMode=true;
                        center=tans[i]->GetCenter();
                    }
                //trafiono - zwracam tan w kt�ry nast�pi�o trafienie
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
    //przesuwamy punkt w kt�ry bylo klikni�cie o tyle ile naprawde si� uda�o przesun��
    holdedX+=info.GetActualMoveX();
    holdedY+=info.GetActualMoveY();   
}

/*
 * Metoda obraca aktualnie trzymany tan
 */
void TangramDlg::RotateHoldedTan(wxMouseEvent& event){
    int eventX=event.GetX(),eventY=event.GetY();  
    //obliczam kat o jaki obr�cony jest z iloczynu skalarnego i jesli kierunek ruchu  
    //myszki byl przeciwnie do wskaz�wek zegara zamieniam wynik na przeciwny
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
        //czy ten testowy tan nie koliduje z kt�rym� z pozosta�ych
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
    wxPoint* shadow_points = shadows[actual_shadow].GetCheckPoints();
    int shadow_size = shadows[actual_shadow].GetSize();
    for(int i=0;i<TANS_NO;++i){
        wxPoint* tan_points = tans[i]->GetPoints();
        for(int j=0;j<tans[i]->GetSize();++j) { 
            for(int k=0;k<shadow_size;++k){
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
        for(int k=0;k<shadow_size;++k){
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
    return true;
}


/*
 * NextClick
 */
void TangramDlg::NextClick(wxCommandEvent& event)
{
	++actual_shadow;
	if(actual_shadow+1==number_of_shadows)
	{ 
        Next->Enable(false);
    }
    Previous->Enable(true);
    
    for(int i=0;i<TANS_NO;++i){
        tans[i]->GetBack();
        tans[i]->SetShadow(&(shadows[actual_shadow]));
    }
    
    Label->Hide();
}

/*
 * PreviousClick
 */
void TangramDlg::PreviousClick(wxCommandEvent& event)
{
	--actual_shadow;
	if(actual_shadow-1<0)
	{ 
        Previous->Enable(false);
    }
    Next->Enable(true);
    
    for(int i=0;i<TANS_NO;++i){
        tans[i]->GetBack();
        tans[i]->SetShadow(&(shadows[actual_shadow]));
    }
    
    Label->Hide();
}
