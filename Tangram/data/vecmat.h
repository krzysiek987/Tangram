#ifndef _VECMAT_H_
#define _VECMAT_H_

#include <stdio.h>
#include <wx/gdicmn.h>
class Vector
{
 public:
 double data[3];
 Vector();
 Vector(double d1,double d2);
 void Print(void);
 void Set(double d1,double d2);
 void Set(wxPoint p);
 double GetX();
 double GetY();
};

class Matrix
{
 public:
 double data[3][3];
 Matrix();
 void Print(void);
 Matrix operator*(const Matrix);
 friend Vector operator*(const Matrix,const Vector);
};

#endif
