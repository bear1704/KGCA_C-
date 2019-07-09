#pragma once
#include "PParser.h"

int main()
{
	PParser p;
	std::vector<std::pair<string,string>> strmap;
	p.XmlParse("anilist.txt", &strmap);
	//std::string abc("a,b,c,d,e,1");

	//std::vector<string> vec = p.SplitString(abc, ',');

	

	system("pause");

}
