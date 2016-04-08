#if 1
/// AC  MISTAKE :  i was not checking adjacent cells availability caused 3 WA 
#include <iostream>
using namespace std;
int max_count = 0;
int noOFWAYS = 0;
int input[7][8];
bool cell_taken[7][8];
bool bone_taken[7][7];
void count_c(int i, int j, int cnt)
{
	max_count = (cnt > max_count) ? cnt : max_count;
	if (cnt == 28)
	{
		noOFWAYS++;
		//	cout << "Done noOFWAYS Incremented " << noOFWAYS<<endl;
		return;
	}
	if (i >= 7 || j >= 8)
		return;

	cell_taken[i][j] = true;
	int sqRow, sQCol;
	///check HORIZONTAL
	if (j + 1 < 8)
	{
		if (input[i][j] > input[i][j + 1])
		{
			sqRow = input[i][j + 1];
			sQCol = input[i][j];
		}
		else
		{
			sqRow = input[i][j];
			sQCol = input[i][j + 1];
		}
		//if (bone_taken[sqRow][sQCol] == false ) MISTAKE i was not checking adjacent cells availability caused 3 WA 
		if (bone_taken[sqRow][sQCol] == false && cell_taken[i][j + 1]==false)
		{
			bone_taken[sqRow][sQCol] = true;
			cell_taken[i][j + 1] = true;
			int next_i = 0, next_j = 0;
			bool found = false;
			for (int _i = i; _i < 7; _i++)
			{
				for (int _j = 0; _j < 8; _j++)
				{
					if (cell_taken[_i][_j] == false)
					{
						next_i = _i, next_j = _j;
						found = true;;
						break;
					}
				}
				if (found == true)
					break;
			}
			//if (found == true)
			count_c(next_i, next_j, cnt + 1);
			cell_taken[i][j + 1] = false;
			bone_taken[sqRow][sQCol] = false;
		}
	}
	///check VERTICAL
	if (i + 1 < 7)
	{
		if (input[i][j] > input[i + 1][j])
		{
			sqRow = input[i + 1][j];
			sQCol = input[i][j];
		}
		else
		{
			sqRow = input[i][j];
			sQCol = input[i + 1][j];
		}
		bool found = false;
		if (bone_taken[sqRow][sQCol] == false && cell_taken[i + 1][j] == false)
		{
			bone_taken[sqRow][sQCol] = true;
			cell_taken[i + 1][j] = true;
			int next_i = 0, next_j = 0;
			for (int _i = i; _i < 7; _i++)
			{
				for (int _j = 0; _j < 8; _j++)
				{
					if (cell_taken[_i][_j] == false)
					{
						next_i = _i, next_j = _j;
						found = true;
						break;
					}
				}
				if (found == true)
					break;
			}
			//if (found == true)
			count_c(next_i, next_j, cnt + 1);
			cell_taken[i + 1][j] = false;
			bone_taken[sqRow][sQCol] = false;
		}
	}
	cell_taken[i][j] = false;
}
//int main()
int SPOJ_VONNY_vonnyandherdominos()
{
	std::ios_base::sync_with_stdio(false); // Supposedly makes I/O faster
	freopen("SPOJ_VONNY.txt","r",stdin);
	int T;
	cin >> T;
	while (T--)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cin >> input[i][j];
				cell_taken[i][j] = false;
				if(j < 7 )
					bone_taken[i][j] = false;
			}
		}
		max_count = 0; //reset
		noOFWAYS = 0;
		count_c(0, 0, 0);
		//cout << max_count << endl;
		cout << noOFWAYS << endl;
	}
	return 0;
}
#endif
