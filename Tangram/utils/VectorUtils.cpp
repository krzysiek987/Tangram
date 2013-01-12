#ifndef _VECTOR_UTILS_
#define _VECTOR_UTILS_

#include <wx/gdicmn.h>
#include <cmath>

class VectorUtils{
public:
    static int ScalarProduct(wxPoint p1, wxPoint p2){
        return p1.x*p2.x+p1.y*p2.y;
    }
    static double Norm(wxPoint p1){
        return sqrt(p1.x*p1.x+p1.y*p1.y);
    }

    static double AngleBetweenVectors(wxPoint p1,wxPoint p2){
        return std::acos(ScalarProduct(p1,p2)/(Norm(p1)*Norm(p2)));
    }
    static double AngleBetweenPoints(wxPoint p1,wxPoint p2,wxPoint p3){
        return AngleBetweenVectors(wxPoint(p1.x-p2.x,p1.y-p2.y),wxPoint(p3.x-p2.x,p3.y-p2.y))*180/M_PI;
    }
    static double AngleBetweenPointsInRadians(wxPoint p1,wxPoint p2,wxPoint p3){
        return AngleBetweenVectors(wxPoint(p1.x-p2.x,p1.y-p2.y),wxPoint(p3.x-p2.x,p3.y-p2.y));
    }
    
    static int GetBlock(int  eventX,int eventY, int centerX, int centerY){
        if(eventX >= centerX && eventY <= centerY) return 1;
        else if(eventX < centerX && eventY <= centerY) return 2;
        else if(eventX < centerX && eventY > centerY) return 3;
        else return 4;
    }
    
    static int GetDirection(int eventX, int eventY, int centerX, int centerY, int holdedX, int holdedY){        
        int position=(holdedY - centerY)*(eventX - centerX) - (holdedX - centerX)*(eventY - centerY);
        printf("position %d\n",position);
        return position;
    }
};

#endif
