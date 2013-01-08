#include "Matrix3.h"

Matrix3::Matrix3()
{
 data[0][0]=0.0; data[0][1]=0.0; data[0][2]=0.0; 
 data[1][0]=0.0; data[1][1]=0.0; data[1][2]=0.0; 
 data[2][0]=0.0; data[2][1]=0.0; data[2][2]=1.0;
}

void Matrix3::Print(void)
{
 printf("\n|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n",data[0][0], data[0][1], data[0][2]);
 printf("|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n",data[1][0], data[1][1], data[1][2]);
 printf("|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n",data[2][0], data[2][1], data[2][2]);
}

Matrix3 Matrix3::operator* (const Matrix3 gMatrix)
{
 int i,j,k;
 Matrix3 tmp;

 for (i=0;i<3;i++)
    for (j=0;j<3;j++)
     {
      tmp.data[i][j]=0.0;
      for (k=0;k<3;k++)
       tmp.data[i][j]=tmp.data[i][j]+(data[i][k]*gMatrix.data[k][j]);
     }
 return tmp;
}

Vector3 operator* (const Matrix3 gMatrix,const Vector3 gVector)
{
 unsigned int i,j;
 Vector3 tmp;

 for (i=0;i<3;i++)
  {
   tmp.data[i]=0.0;
   for (j=0;j<3;j++) tmp.data[i]=tmp.data[i]+(gMatrix.data[i][j]*gVector.data[j]);
  }
 return tmp;
}
