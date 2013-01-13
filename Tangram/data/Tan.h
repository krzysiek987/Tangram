#ifndef _TAN_H_
#define _TAN_H_

#include <wx/gdicmn.h>
#include "../utils/MinMaxUtils.cpp"
#include "../utils/VectorUtils.cpp"
#include "Constants.h"
#include "ActualMoveInfo.cpp"
#include <cstring>

/*
 * Klasa abstrakcyjna Tan po ktorej dziedzicz¹ figury
 */
class Tan
{
    public:
        int type;
        /*
         * Metoda wirtualna odpowiadajace za przesuwanie tana
         */
        virtual ActualMoveInfo Move(int x,int y, Tan** tans) =0;        
        /*
         * Metoda wirtualna sprawdzajaca czy punkt (x,y) trafia w tan
         */
        virtual bool IsInner(int x,int y) =0;
        /*
         * Metoda sprawdza czy punkt (x,y) trafia w prostokat opisany na tanie
         */
        bool IsIn(int x,int y);
        /*
         * Metoda sprawdza czy zakresy min-max tanów zachodza na siebie
         */
        bool IsIn(Tan* tan);
        /*
         * Metoda sprawdza czy krawedzie tana przecinaja sie
         */
        bool IsCrossing(Tan* tan);
        /*
         * Metoda sprawdza czy punkt (x,y) trafia w otoczenie œrodka figury
         */
        bool IsInCenterCircle(int x,int y);
        /*
         * Metoda sprawdza czy tan jest poza panelem
         */
        bool IsOutsidePanel();
        
        /*
         * Metoda sprawdza czy tan toCheck zachacza o któryœ z tanów tans róznych od aktualnego
         */
        bool Conflicts(Tan* toCheck,Tan** tans);      
        /*
         * Metoda sprawdza czy wierzcholki tana toCheck le¿a w tanie conflicted lub czy wierzcholki tana conflicted le¿a w tanie toCheck
         */
        bool IsInner(Tan* toCheck, Tan* conflicted);    
        
        /*
         * Metoda wypisuje wierzcholki
         */
        void Print();
        /*
         * Metoda zwraca rozmiar (ilosc wierzcho³ków tana)
         */ 
        int GetSize();  
        /*
         * Metoda zwraca œrodek tana
         */ 
        wxPoint GetCenter();  
        /*
         * Metoda zwracaj¹ce wierzcho³ki tana
         */ 
        wxPoint* GetPoints();
        wxPoint GetP1();
        wxPoint GetP2();
        wxPoint GetP3();
        wxPoint GetP4();
        /*
         * Metody zmieniajace punkty tana
         */
        void SetP(int i,wxPoint p);
        virtual void SetP1(wxPoint p1)=0;
        virtual void SetP2(wxPoint p2)=0;
        virtual void SetP3(wxPoint p3)=0;
        virtual void SetP4(wxPoint p4)=0;
        
    protected:
        //wspolrzedne prostok¹ta na którym opisany jest tan
        int xmin, xmax, ymin, ymax;
        //wierzcholki tana
        wxPoint points[4];
        //ilosc wierzcholkow
        int size;       
    };
    

#endif
