#include <iostream>
#include <string>


struct LCSTable {

	int **Data;
};

void pr(std::string X, std::string Y, LCSTable* Table)
{
	std::cout << std::endl;
	for (int i = 0; i < X.length() + 1; i++)
	{
		for (int j = 0; j < Y.length() + 1; j++)
		{
			std::cout << Table->Data[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

int lcs(std::string X, std::string Y,  LCSTable* Table)
{
	int m = 0;
	int n = 0;

	for (m = 0; m < X.length() + 1; m++) //한 쪽의 문자 길이가 0일 경우, 비교 불가
	{
		Table->Data[m][0] = 0;
	}
	for (n = 0; n < Y.length() + 1; n++) //한 쪽의 문자 길이가 0일 경우, 비교 불가
	{
		Table->Data[n][0] = 0;
	}


	for (m = 1; m <= Y.length() ; m++) //LCS를 구하기 위해 LCS 테이블 작성(시간복잡도 O(mn))
	{
		for (n = 1; n <= X.length(); n++) 
		{
			if (X[m - 1] == Y[n - 1])//만약, 비교 중인 양쪽 부분문자의 끝자리가 같다면 이전까지의 LCS에 1을 더한다.(자기가 같으므로)
			{
				Table->Data[m][n] = Table->Data[m - 1][n - 1] + 1;
			}
			else if (X[m - 1] != Y[n - 1]) //비교 중인 양쪽 부분문자의 끝자리가 다르다면, LCS(m,n-1)와 LCS(m-1,n) 중 큰 수를 자신의 LCS로 취한다.
			{
				Table->Data[m][n] = Table->Data[m - 1][n] > Table->Data[m][n - 1] ? Table->Data[m - 1][n] : Table->Data[m][n - 1];
			}

		}

	}

	return Table->Data[X.length()][Y.length()];  // LCS의 길이
}
//LCS의 길이는 구했으나 정작 LCS가 뭔지 모르면 의미가 없다.
void LCS_TraceBack(std::string X, std::string Y, LCSTable* Table, std::string* LCS) 
{
	int m = X.length();
	int n = Y.length();

	while (true)
	{
		if (m == 0 || n == 0)
			break;

		if (Table->Data[m][n] > Table->Data[m - 1][n] && Table->Data[m][n] > Table->Data[m][n - 1]
			&& Table->Data[m][n] > Table->Data[m - 1][n - 1])
		{
			*LCS += X[m - 1];
			m--; n--;
		}
		else if (Table->Data[m][n-1] == Table->Data[m][n] && Table->Data[m-1][n] < Table->Data[m][n])
			n--;
		else
			m--;
	}

}

int main()
{
	std::string X = "GOOD MORNING.";
	std::string Y = "GUTEN MORGEN.";
	

	LCSTable Table;
	Table.Data = new int*[X.length() + 1];
	
	for (int i = 0; i < X.length() + 1; i++)
	{
		Table.Data[i] = new int[Y.length() + 1];
		std::fill(Table.Data[i], Table.Data[i] + Y.length() +1, 0);
	}
	std::string lcsString;
	int LCS = lcs(X, Y, &Table);
	LCS_TraceBack(X, Y, &Table, &lcsString);

	std::cout <<"Length : "  << LCS << std::endl;
	
	for (int i = lcsString.length()-1; i >= 0; i--)
		std::cout << lcsString[i] << " ";

	std::cout << std::endl;

	pr(X, Y, &Table);
	
	system("pause");
}

