#include<stdio.h>
int main(){
  int num,i,j,x[32];
		float  num1;
  long int sum=0;
  printf("\nEnter the number of samples: ");
  scanf("%d",&num);
  printf("\nEnter samples: ");
  for(j=0;j<num;j++)
     scanf("%d",&x[j]);
  for(i=0;i<=num;i++)
  {
            sum+=x[i]*x[i];
  }
  num=num*2;
  num++;
  num1 = sum / (float) num;
  printf("\n the Average power of above samples is\n %.2f",num1);
  return 0;
}
