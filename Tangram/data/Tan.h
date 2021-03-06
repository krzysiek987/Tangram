#ifndef _TAN_H_
#define _TAN_H_

#include <wx/gdicmn.h>
#include "../utils/MinMaxUtils.cpp"
#include "../utils/VectorUtils.cpp"
#include "Constants.h"
#include "ActualMoveInfo.cpp"
#include <cstring>
#include "vecmat.h"
#include "Shadow.h"

/*
 * Klasa abstrakcyjna Tan po ktorej dziedzicz� figury
 */
class Tan
{
    public:
        Tan();      
        /*
         * Metoda sprawdza czy punkt (x,y) trafia w prostokat opisany na tanie
         */
        bool IsIn(int x,int y);
        /*
         * Metoda sprawdza czy zakresy min-max tan�w zachodza na siebie
         */
        bool IsIn(Tan* tan);
        /*
         * Metoda sprawdza czy krawedzie tana przecinaja sie
         */
        bool IsCrossing(Tan* tan);
        /*
         * Metoda sprawdza czy punkt (x,y) trafia w otoczenie �rodka figury
         */
        bool IsInCenterCircle(int x,int y);
        /*
         * Metoda sprawdza czy tan jest poza panelem
         */
        bool IsOutsidePanel();
        
        /*
         * Metoda sprawdza czy tan toCheck zachacza o kt�ry� z tan�w tans r�znych od aktualnego
         */
        bool Conflicts(Tan* toCheck,Tan** tans);      
        /*
         * Metoda sprawdzajaca czy punkt (x,y) trafia w tan
         */
        bool IsInner(int x,int y);
        /*
         * Metoda wypisuje wierzcholki
         */
        void Print();
        /*
         * Metoda zwraca rozmiar (ilosc wierzcho�k�w tana)
         */ 
        int GetSize();  
        /*
         * Metoda zwraca �rodek tana
         */ 
        wxPoint GetCenter();  
        /*
         * Metoda pr�buje przesun�� Tan o wektor (x,y) + ewentualny wektor wynikaj�cy z przyci�gania
         */     
        ActualMoveInfo Move(int x,int y, Tan** tans);
        /*
         * Metoda zwraca warto�� przesuni�cia dla przyci�gania
         */          
        wxPoint AttractionShift(Tan** tans);
        /*
         * Metoda obraca tan o podany k�t wzgl�dem podanego punktu
         */
        void RotateTan(double radius,wxPoint rotate_point);
        /*
         * Metoda przesuwa tan o podany wektor
         */
        void TranslateTan(wxPoint translation);
        /*
         * Metoda zwracaj�ce wierzcho�ki tana
         */ 
        wxPoint* GetPoints();
        wxPoint GetP1();
        wxPoint GetP2();
        wxPoint GetP3();
        wxPoint GetP4();
        /*
         * Metoda ustawiaj�ca cie� aktualnie uk�adanej figury
         */
        void SetShadow(Shadow* shadow);
        /*
         * Metoda ustawiaj�ca tana w zasobniku
         */
        void GetBack();
        /*
         * Metoda wirtualna odwracaj�ca tan
         */
        virtual void Mirroring(Tan** tans)=0;
    protected:
        /*
         * Metody zmieniajace punkty tana
         */
        void SetP(int i,wxPoint p);
        virtual void SetP1(wxPoint p1)=0;
        virtual void SetP2(wxPoint p2)=0;
        virtual void SetP3(wxPoint p3)=0;
        virtual void SetP4(wxPoint p4)=0;
        //wspolrzedne prostok�ta na kt�rym opisany jest tan
        int xmin, xmax, ymin, ymax;
        //wierzcho�ki startowe tana (z zasobnika)
        Vector start_vectors[4];
        //wierzcholki tana
        wxPoint points[4];
        //ilosc wierzcholkow
        int size;   
        //macierz przekszta�cenia z pozycji pocz�tkowej
        Matrix matrix;
        //Wska�nik do cienia aktualnie uk�adanej figury
        Shadow* shadow;    
    };
    

#endif
