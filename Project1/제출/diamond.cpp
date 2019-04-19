
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

int main()
{
	int starCount = 1;
	float signWithCos = 0.0f;

	int maxLine;
	int maxStar;
	int sideBlank;
	int plusMinusVar = 2;
	float piStart = 0;

	char starCharacter[50];
	char blankCharacter[50];
	std::fill(starCharacter, starCharacter + 50, '*');
	std::fill(blankCharacter, blankCharacter + 50, ' ');
	std::cin >> maxLine;

	while (maxLine % 2 != 1)
	{
		std::cout << "È¦¼ö¸¸ ÀÔ·Â" << std::endl;
		std::cin >> maxLine;
	}

	maxStar = maxLine;
	float n = M_PI / maxLine;

	for (int i = 0; i < maxLine; i++)
	{
			sideBlank = (maxStar - starCount) / 2;
			
			char *b = new char[sideBlank];
			memcpy(b, blankCharacter, sideBlank);
			b[sideBlank ] = '\0';

			char *p = new char[starCount];
			memcpy(p, starCharacter, starCount);
			p[starCount] = '\0';
			std::cout << b << "" << p << std::endl;
			
			piStart += n;
			signWithCos = cos(piStart);

			starCount += (plusMinusVar) * (signWithCos / abs(signWithCos));

			std::cout << std::endl;
	}
	system("pause");
}
