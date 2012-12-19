#include <stdio.h>

class Point
{
public:
    Point();
    Point(int x,int y);
    void Print(void);
    void Set(int x,int y);
    void SetX(int x);
    void SetY(int y);
    int GetX();
    int GetY();
    
 
private:
    int _x;
    int _y;
};
