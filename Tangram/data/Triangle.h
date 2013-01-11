#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <stdio.h>
#include "Tan.cpp"

class Triangle : public Tan
{
 public:
    Triangle();
    Triangle(wxPoint p1,wxPoint p2,wxPoint p3);
    void Print(void);
    
    void Set(wxPoint p1,wxPoint p2,wxPoint p3);
    void SetP1(wxPoint p1);
    void SetP2(wxPoint p2);
    void SetP3(wxPoint p3);

    wxPoint GetP1();
    wxPoint GetP2();
    wxPoint GetP3();
    virtual wxPoint* GetPoints();
    int GetSize();
    
    bool IsInner(int x,int y);
    
    bool MoveX(int x);
    bool MoveY(int y);
    ActualMoveInfo Move(int x,int y);
};
#endif
