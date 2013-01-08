#ifndef _MATRIX3_H_
#define _MATRIX3_H_
#include<stdio.h>
#include "Vector3.cpp"

class Matrix3
{
 public:
 double data[3][3];
 Matrix3();
 void Print(void);
 Matrix3 operator*(const Matrix3);
 friend Vector3 operator*(const Matrix3,const Vector3);
};
#endif
