#include<stdio.h>
#define LENGHT1 4                   /*Lenght of i/p samples sequence*/
#define LENGHT2 2                   /*Lenght of impulse response Co-efficients */
#define LENGHT3 LENGHT1+LENGHT2-1   /*Lenght of Output sequence*/

int x[LENGHT3]={1,2,3,4,0}; /*Input Signal Samples*/
int h[LENGHT3]={1,2,0,0,0}; /*Impulse Response Coefficients*/
int y[LENGHT3];
main()
{
    int i=0,j;
    for(i=0;i<LENGHT3;i++)
    {
    y[i]=0;
    for(j=0;j<=i;j++)
    y[i]+=x[j]*h[i-j];
}
for(i=0;i<LENGHT3;i++)
printf("%d\n",y[i]);
}
