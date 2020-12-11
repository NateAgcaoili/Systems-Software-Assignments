#include <stdio.h>
void square(int *num, int *result){
    int ogNum;
    ogNum = *num;
    ogNum = (ogNum*ogNum);
    *result = ogNum;
}
int main()
{
int x,result=0;
	scanf("%d",&x);
	square(&x,&result);
	printf("The square of the number is %d",result);
	return 0;
}


