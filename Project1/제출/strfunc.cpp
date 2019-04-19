#define _CRT_SECURE_NO_WARNINGS

#ifdef TEST
#include <cstdio>
#include <cstdlib>
#include <string.h>



char* _strcpy(char* str1, char* str2);
long long int _atoi(char* str);
char* _strcat(char* str1, char* str2);

int main()
{
	//char a[199] = "abcdefghijklmnopqrstuvwxyz";
	//char b[100] = "12345678910111";
	//char h[300] = "uuuu";

	//char *c = _strcpy(a, b);
	//printf("%s\n", c);

	//char *d = _strcat(c, b);
	//char *e = _strcat(h, d);

	//printf("%s\n", e);

	//long long int g = _atoi(b);

	//printf("%lld\n", g);


	//getchar();
}

long long int _atoi(char* str)
{
	int sizeSearchIter = 0; //문자열 글자 수
	int position = 1;
	long long int sum = 0;


	while (*(str + sizeSearchIter) != '\0')
		sizeSearchIter++;

	const int lastWordCount = sizeSearchIter - 1;

	for (int i = lastWordCount; i >= 0; i--, position++)
	{
		int integer = (int)*(str + i);
		integer -= 48;

		sum += integer * (long long int)(pow(10, lastWordCount - i));
	}

	return sum;
}


char* _strcat(char* str1, char* str2)
{
	int sizeSearchIter = 0;
	int strSize1;
	int strSize2;

	while (*(str1 + sizeSearchIter) != '\0')
		sizeSearchIter++;

	strSize1 = sizeSearchIter;

	sizeSearchIter = 0;

	while (*(str2 + sizeSearchIter) != '\0')
		sizeSearchIter++;

	strSize2 = sizeSearchIter;


	int concatStringSize = strSize1 + strSize2 + 1;
	char* concatString = (char*)malloc(sizeof(char) * (concatStringSize)); //1은 '\0' 들어갈곳
	
	*(concatString + concatStringSize -1) = '\0'; //끝문자

	for (int i = 0; i < strSize1; i++)
		*(concatString + i) = *(str1 + i);

	for (int j = 0; j < strSize2; j++)
		*(concatString + strSize1 + j) = *(str2 + j);

	//printf("%s\n", concatString);

	return concatString;
}


char* _strcpy(char* str1, char* str2)
{
	int sizeSearchIter = 0;
	int sourceSizePure;

	sizeSearchIter = 0;

	while (*(str2 + sizeSearchIter) != '\0')
		sizeSearchIter++; //str2 문자수 가져오기(\0을 제외한 순수문자)

	sourceSizePure = sizeSearchIter;


	for (int i = 0; i < sourceSizePure; i++)
		*(str1+ i) = *(str2 + i);

	*(str1 + sourceSizePure) = '\0';

	return str1;

}

#endif