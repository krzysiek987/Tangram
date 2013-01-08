#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include <stdio.h>
#include "Figure.cpp"
class Rect : public Tan
{
 public:
    Rect();
    Rect(wxPoint p1,wxPoint p2,wxPoint p3, wxPoint p4);
    void Print(void);
    
    void Set(wxPoint p1,wxPoint p2,wxPoint p3, wxPoint p4);
    void SetP1(wxPoint p1);
    void SetP2(wxPoint p2);
    void SetP3(wxPoint p3);
    void SetP4(wxPoint p4);

    wxPoint GetP1();
    wxPoint GetP2();
    wxPoint GetP3();
    wxPoint GetP4();
    wxPoint* GetPoints();
    
    bool IsInner(int x,int y);
   
    wxPoint points[4]; 
};
#endif
