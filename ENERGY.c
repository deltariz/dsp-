#include<stdio.h>
int main()
{
  int num,i,j,x[32];
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
  printf("\n the energy of above samples is\n %d",sum);
  return 0;
}
