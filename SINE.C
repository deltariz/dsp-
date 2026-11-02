#include <stdio.h>
#include<math.h>

#define FREQ 500
float m[127];
void main()
{
 int i=0;
 
 for(i=0;i<127;i++)
 {
  m[i]=30000*sin(2*3.14*FREQ*i/24000);
  printf("%f\n",m[i]);
 }
}
  
