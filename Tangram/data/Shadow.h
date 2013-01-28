#ifndef _SHADOW_H_
#define _SHADOW_H_

#include <wx/gdicmn.h>
#include "../utils/MinMaxUtils.cpp"
#include "../utils/VectorUtils.cpp"
#include "Constants.h"
#include "ActualMoveInfo.cpp"
#include <cstring>
#include "vecmat.h"

/*
 * Klasa Shadow reprezentuj¹ca cieñ uk³adanej figury
 */
class Shadow
{
    public:
        /* 
        * Konstruktory i destruktory
        */
        Shadow();
        Shadow(int size,wxPoint* points,wxPoint* check_points);
        ~Shadow();
        
        /*
         * Metoda ustawiaj¹ca wszystkie atrybuty cienia
         */
        void Set(int size,wxPoint* points,wxPoint* check_points);
        /*
         * Metoda zwracaj¹ca wierzcho³ki cienia
         */
        wxPoint* GetPoints();
        /*
         * Metoda zwracaj¹ca wierzcho³ki obwiedni cienia
         */
        wxPoint* GetCheckPoints();
        /*
         * Metoda zwracaj¹ca liczbê wierzcho³ków cienia
         */
        int GetSize();
    private:
        // Wierzcho³ki cienia
        wxPoint* _points;
        // Wierzcho³ki obwiedni cienia
        wxPoint* _check_points;
        // Liczba wierzcho³ków cienia
        int _size;   
};
    

#endif
