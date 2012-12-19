#include "Vector3.h"

Vector3::Vector3()
{
 data[0]=0.0; data[1]=0.0; data[2]=1.0;
}

void Vector3::Print(void)
{
 printf("(%2.3lf,%2.3lf,%2.3lf)\n",data[0],data[1],data[2]);
}

void Vector3::Set(double d1,double d2)
{
 data[0]=d1; data[1]=d2;
}

double Vector3::GetX()
{
	return data[0];
}

double Vector3::GetY()
{
	return data[1];
}

double Vector3::GetZ()
{
	return data[2];
}
