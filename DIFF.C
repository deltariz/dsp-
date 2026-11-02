#include <stdio.h>
#include<math.h>
#define FREQ 400
float y[3]={0,0,0};
float x[3]={0,0,0};
float z[128],m[128],n[128],p[128];
main()
{
int i=0,j;
float a[3]={ 0.072231,0.144462,0.072231};
float b[3]={ 1.000000,-1.109229,0.398152};
for(i=0;i<128;i++)
{
m[i]=sin(2*3.14*FREQ*i/24000);
}
for(j=0;j<128;j++)
{
x[0]=m[j];
y[0] = (a[0] *x[0]) +(a[1]* x[1] ) +(x[2]*a[2]) - (y[1]*b[1])-
(y[2]*b[2]);
z[j]=y[0];
y[2]=y[1];
y[1]=y[0];
x[2]=x[1];
x[1] = x[0];
}
}