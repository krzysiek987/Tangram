#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <stdio.h>

class Vector3
{
 public:
 double data[3];
 Vector3();
 void Print(void);
 void Set(double d1,double d2);
 double GetX();
 double GetY();
 double GetZ();
};

#endif
