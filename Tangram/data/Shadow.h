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
        Shadow();
        Shadow(int size,wxPoint* points);
        ~Shadow();
        
        void Set(int size,wxPoint* points);
        wxPoint* GetPoints();
        int GetSize();
    private:
        wxPoint* _points;
        int _size;   
};
    

#endif
