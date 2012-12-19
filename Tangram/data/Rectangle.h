#include <stdio.h>
#include "Point.cpp"

class Rectangle
{
 public:
    Rectangle();
    Rectangle(Point p1,Point p2,Point p3, Point p4);
    void Print(void);
    void Set(Point p1,Point p2,Point p3, Point p4);
    
    void SetP1(Point p1);
    void SetP2(Point p2);
    void SetP3(Point p3);
    void SetP4(Point p4);
    
    Point GetP1();
    Point GetP2();
    Point GetP3();
    Point GetP4();
 
    Point* GetPoints();
    Point points[4];
};
