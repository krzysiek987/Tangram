#ifndef _FIGURE_C_
#define _FIGURE_C_
#include <stdio.h>
#include <wx/gdicmn.h>
#include "../utils/MinMaxUtils.cpp"
#include "../utils/VectorUtils.cpp"
#include "Constants.h"
#include "ActualMoveInfo.cpp"

class Tan
{
    public:
        int xmin, xmax, ymin, ymax;
        bool IsIn(int x,int y) 
        {
            //printf("Tan: IsIn ( %d , %d )   ;  [%d,%d] x [%d,%d]",x,y,xmin,xmax,ymin,ymax);
            return ( x>=xmin && x<=xmax && y>=ymin && y<=ymax );
        }
        bool IsInCenterCircle(int x,int y){
            wxPoint center=GetCenter();
            int centerX=center.x;
            int centerY=center.y; 
            printf("Odleglosc [%d,%d] od srodka [%d,%d]\n",x,y,centerX,centerY);                        
            double norm=VectorUtils::Norm(wxPoint(x-centerX,y-centerY));
            printf("norma: %lf /  %lf  , od [%d,%d]\n",norm,VectorUtils::Norm(wxPoint(points[0].x-centerX,y-centerY)),points[0].x,points[0].y);
            if(norm/VectorUtils::Norm(wxPoint(points[0].x-centerX,points[0].y-centerY))<IN_CIRCLE_FACTOR){
                return true;   
            }
            return false;
        }
        wxPoint GetCenter(){
            wxPoint* points=GetPoints();
            int centerX=0;
            int centerY=0;
            for(int i=0;i<GetSize();i++){
                centerX+=points[i].x;
                centerY+=points[i].y;   
            }
            centerX/=GetSize();
            centerY/=GetSize();
            return wxPoint(centerX,centerY);
        }
        
        virtual bool MoveX(int x) =0;
        virtual bool MoveY(int y) =0;
        virtual ActualMoveInfo Move(int x,int y) =0;
        
        virtual bool IsInner(int x,int y) =0;
        virtual wxPoint* GetPoints() =0;
        virtual int GetSize() =0;
    protected:
        int size;
        wxPoint points[4];
    };
    

#endif
