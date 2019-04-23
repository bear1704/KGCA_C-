#pragma once

#include <iostream>
#include "Ship.h"
#include "BattleShip.h"
#include "SubMarine.h"
#include "SmallSubmarine.h"


int main()
{

	Ship* ship;
	ship = new Ship();

	std::cout << _msize(ship) << std::endl;
	
/*

	for (int i = 0; i < 4; i++)
	{
		ship[i]->Print();

	}
*/

	system("pause");


}