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
 * Klasa Shadow reprezentuj�ca cie� uk�adanej figury
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
         * Metoda ustawiaj�ca wszystkie atrybuty cienia
         */
        void Set(int size,wxPoint* points,wxPoint* check_points);
        /*
         * Metoda zwracaj�ca wierzcho�ki cienia
         */
        wxPoint* GetPoints();
        /*
         * Metoda zwracaj�ca wierzcho�ki obwiedni cienia
         */
        wxPoint* GetCheckPoints();
        /*
         * Metoda zwracaj�ca liczb� wierzcho�k�w cienia
         */
        int GetSize();
    private:
        // Wierzcho�ki cienia
        wxPoint* _points;
        // Wierzcho�ki obwiedni cienia
        wxPoint* _check_points;
        // Liczba wierzcho�k�w cienia
        int _size;   
};
    

#endif
