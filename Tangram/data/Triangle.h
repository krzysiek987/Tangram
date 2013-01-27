#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <stdio.h>
#include "Tan.h"

class Triangle : public Tan
{
 public:
    Triangle();
    Triangle(wxPoint p1,wxPoint p2,wxPoint p3);

    ActualMoveInfo Move(int x,int y, Tan** tans);
    
    void Mirroring() {};
    
protected:
    void Set(wxPoint p1,wxPoint p2,wxPoint p3);
    void Set(wxPoint p1,wxPoint p2,wxPoint p3,wxPoint p4);
    void SetP1(wxPoint p1);
    void SetP2(wxPoint p2);
    void SetP3(wxPoint p3);
    void SetP4(wxPoint p4);
};
#endif
