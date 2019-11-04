#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>

bool IsSameString(char* str_a, char* str_b)
{
	if (strlen(str_a) != strlen(str_b))
		return false;

	int alphabet[26] = { 0, }; //97

	for (int i = 0; i < strlen(str_a); i++)
	{
		alphabet[str_a[i] - 97] += 1;
		alphabet[str_b[i] - 97] -= 1;
	}

	for (int j = 0; j < 26; j++)
	{
		if (alphabet[j] > 0)
			return false;
	}

	return true;
}


int main()
{
	char a[10] = "appleb";
	char b[10] = "papelq";
	bool c = IsSameString(a, b);

	system("pause");
}