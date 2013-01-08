#ifndef _FIGURE_C_
#define _FIGURE_C_
#include <stdio.h>

class Figure
{
 public:
   int size; 
   virtual wxPoint* GetPoints(){};
};

class Tan
{
    public:
        int xmin, xmax, ymin, ymax;
        bool spr(int x,int y) 
        {
            return ((x>xmin&&x<xmax)&&(y>ymin&&y<ymax)) ;
        }
        virtual bool IsInner(int x,int y) =0;
        virtual wxPoint* GetPoints() =0;
    };
    

#endif
