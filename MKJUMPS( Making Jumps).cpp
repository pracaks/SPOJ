#if 1
// AC first attemtp http://www.spoj.com/problems/MKJUMPS/ 
// in my solution ans of first was coming zero as i was not following the question properly .. you cannot rest on a cell more then once.....
/// by my previos assumption it was basic dfs ...  which was wrong .
//// it is actually backtrack. we neeed to see how long van horse go by one continous path ......
#include <iostream>
#include <cstdio>
using namespace std;
typedef struct
{
	int ymin;
	int ymax;
}LIMIT;
#define SZ 11
LIMIT rowLimit[SZ];
bool done[SZ][SZ];
int N;
int TotalCell = 0;
int doneCount = 0;
inline bool isSafe(int x, int y)
{
	if (x<1 || x>N)
		return false;
	if (y < rowLimit[x].ymin || y > rowLimit[x].ymax)
		return false;
	return true;
}
int dx[] = {-2,-1, 1, 2, 2, 1,-1,-2};
int dy[] = { 1, 2, 2, 1,-1,-2,-2,-1};

void solve(int ux, int uy,int cur_count)
{
	if (cur_count > doneCount)
		doneCount = cur_count ;
	for (int d = 0; d < 8; d++)
	{
		int vx = ux + dx[d];
		int vy = uy + dy[d];
		if (isSafe(vx, vy) == true && done[vx][vy] == false)
		{
			done[vx][vy] = true;
			solve(vx, vy, cur_count+ 1);
			done[vx][vy] = false;
		}
	}
	return ;
}
int main()
{
//	freopen("SPOJ_MKJUMPS.txt", "r", stdin);
	cin >> N;
	int t = 1;
	do{
		// read
		TotalCell = 0;
		for (int i = 1; i <= N; i++)
		{
			int col, len;
			cin >> col >> len;
			rowLimit[i].ymin = col + 1;
			rowLimit[i].ymax = rowLimit[i].ymin + len - 1 ;
			TotalCell = TotalCell + len;
			// reset
			for (int j = rowLimit[i].ymin; j <= rowLimit[i].ymax; j++)
			{
				done[i][j] = false;
			}
		}
		// solve
		doneCount = 0;
		done[1][1] = true;
		solve(1, 1,1);
		cout << "Case " << t++ << ", " << TotalCell - doneCount;
		((TotalCell - doneCount) == 1) ? cout << " square" : cout << " squares";
		cout << " can not be reached." << endl;
		cin >> N;
	} while (N);
	return 0;
}

#endif 
