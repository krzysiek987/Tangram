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
 * Klasa Shadow reprezentująca cień układanej figury
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
         * Metoda ustawiająca wszystkie atrybuty cienia
         */
        void Set(int size,wxPoint* points,wxPoint* check_points);
        /*
         * Metoda zwracająca wierzchołki cienia
         */
        wxPoint* GetPoints();
        /*
         * Metoda zwracająca wierzchołki obwiedni cienia
         */
        wxPoint* GetCheckPoints();
        /*
         * Metoda zwracająca liczbę wierzchołków cienia
         */
        int GetSize();
    private:
        // Wierzchołki cienia
        wxPoint* _points;
        // Wierzchołki obwiedni cienia
        wxPoint* _check_points;
        // Liczba wierzchołków cienia
        int _size;   
};
    

#endif
