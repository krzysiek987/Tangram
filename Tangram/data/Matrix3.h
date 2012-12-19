#include<iostream.h>
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
