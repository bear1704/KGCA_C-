#include <stdio.h>
#include <stdlib.h>
//#define TEST

#ifdef TEST
void hanoi(int, int,int,int);
static int count = 0;
int main()
{
	int a = 1;
	int b = 2;
	int c = 3;

	hanoi(3, a, b, c);

	printf("\n\n%d", count);

	getchar();
}


void hanoi(int n, int a, int b, int c)
{


	if (n == 1)
		printf("%d번째, :: %d에서 %d로 이동\n", n, a, c);
	else
	{
		hanoi(n - 1, a, c, b);
 		printf("%d번째, :: %d에서 %d(으)로 이동\n", n, a, c);
		hanoi(n - 1, b, a, c);
		count++;
	}
}

#endif