#ifndef _POINT_UTILS_
#define _POINT_UTILS_

#include <wx/gdicmn.h>

/*
 * Klasa z metodami u¿ytkowymi dotycz¹cymi minimów i maksimów 
 */
class MinMaxUtils{
public:
///////////////////////////////////// MIN / MAX liczb ////////////////////////////////////////
    static int Min(int x,int y){
        return x<y ? x : y;   
    }
    static int Max(int x,int y){
        return x>y ? x : y;   
    }
    static int Min(int x,int y,int z){
        return Min(x,Min(y,z)); 
    }
    static int Max(int x,int y, int z){
        return Max(x,Max(y,z));   
    }
    static int Min(int x,int y,int z, int t){
        return Min(Min(x,y),Min(z,t)); 
    }
    static int Max(int x,int y, int z, int t){
        return Max(Max(x,y),Max(z,t));   
    }
////////////////////////////// MIN / MAX wspó³rzêdnych punktów ////////////////////////////////////////    
    static int MinX(wxPoint &p1, wxPoint &p2, wxPoint &p3){
        return Min(p1.x,p2.x,p3.x);
    }
    static int MinX(wxPoint &p1, wxPoint &p2, wxPoint &p3, wxPoint p4){
        return Min(p1.x,p2.x,p3.x,p4.x);
    }
    static int MinY(wxPoint &p1, wxPoint &p2, wxPoint &p3){
        return Min(p1.y,p2.y,p3.y);
    }
    static int MinY(wxPoint &p1, wxPoint &p2, wxPoint &p3, wxPoint &p4){
        return Min(p1.y,p2.y,p3.y,p4.y);
    }
    static int MaxX(wxPoint &p1, wxPoint &p2, wxPoint &p3){
        return Max(p1.x,p2.x,p3.x);
    }
    static int MaxX(wxPoint &p1, wxPoint &p2, wxPoint &p3, wxPoint &p4){
        return Max(p1.x,p2.x,p3.x,p4.x);
    }
    static int MaxY(wxPoint &p1, wxPoint &p2, wxPoint &p3){
        return Max(p1.y,p2.y,p3.y);
    }
    static int MaxY(wxPoint &p1, wxPoint &p2, wxPoint &p3, wxPoint &p4){
        return Max(p1.y,p2.y,p3.y,p4.y);
    }
};

#endif
