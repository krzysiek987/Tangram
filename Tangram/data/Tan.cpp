#ifndef _FIGURE_C_
#define _FIGURE_C_
#include <stdio.h>
#include <wx/gdicmn.h>
#include "../utils/MinMaxUtils.cpp"
#include "../utils/VectorUtils.cpp"
#include "Constants.h"

#define EPSILON 1e-5

class Tan
{
    public:
        int xmin, xmax, ymin, ymax;
        bool IsIn(int x,int y) 
        {
            printf("Tan: IsIn ( %d , %d )   ;  [%d,%d] x [%d,%d]",x,y,xmin,xmax,ymin,ymax);
            return ( x>=xmin && x<=xmax && y>=ymin && y<=ymax );
        }
        
        virtual bool MoveX(int x) =0;
        virtual bool MoveY(int y) =0;
        virtual bool Move(int x,int y) =0;
        
        virtual bool IsInner(int x,int y) =0;
        virtual wxPoint* GetPoints() =0;
        virtual int GetSize() =0;
    };
    

#endif
