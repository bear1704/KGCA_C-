#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main()
{
	int arr[5][5] =
	{ {0,1,0,0,0 } ,
	  {0,0,0,1,0 }, 
	  {0,1,1,1,0 },
	  {0,0,0,1,0 },
	  {0,0,0,1,0 } };

	std::vector<int*> stack_row;
	std::vector<int*> stack_col;
	
	for (int ii = 0; ii < 5; ii++)
	{
		for (int jj = 0; jj < 5; jj++)
		{
			if (arr[ii][jj] == 1)
			{
				stack_row.push_back(&arr[ii][jj]);
			}
			else
			{
				stack_row.clear();
			}


			if (arr[jj][ii] == 1)
			{
				stack_col.push_back(&arr[jj][ii]);
			}
			else
			{
				stack_col.clear();
			}
		}

		if(stack_row.size() >= 1)

	}

	system("pause");
}