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
        Shadow();
        Shadow(int size,wxPoint* points,wxPoint* check_points);
        ~Shadow();
        
        void Set(int size,wxPoint* points,wxPoint* check_points);
        wxPoint* GetPoints();
        wxPoint* GetCheckPoints();
        int GetSize();
    private:
        wxPoint* _points;
        wxPoint* _check_points;
        int _size;   
};
    

#endif