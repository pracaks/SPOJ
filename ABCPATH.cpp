# if 1 
//Accepted   http://www.spoj.com/problems/ABCPATH/  1st attemt TLE 2nd attempt with mat[ux][uy] = '@'; AC
// its not backtrack 
// how ever we set @ so that we do not traverse a path again
#include <iostream>
#include <cstdio>
using namespace std;
int R, C;
#define SZ 51
char mat[SZ][SZ];
int pathLen = 0;
int dx[] = { -1,-1,0,1,1, 1, 0,-1};
int dy[] = {  0, 1,1,1,0,-1,-1,-1};
inline bool isSafe(int a, int b)
{
	if (a<1 || a>R || b<1 || b>C)
		return false;
	return true;
}
void countPath(int ux, int uy, int cur_len)
{
	if (cur_len > pathLen)
	{
		pathLen = cur_len;
	}
	//int backup = mat[ux][uy]; 
	mat[ux][uy] = '@';  // this is required as no need to traverse  path again if its already calcualted will save time 
	for (int d = 0; d <= 7; d++)
	{
		int vx = ux + dx[d];
		int vy = uy + dy[d];
		if (isSafe(vx, vy) == true && mat[vx][vy] == 'A' + cur_len)
		{
			countPath(vx, vy, cur_len+1);
		}
	}
	//mat[ux][uy] = backup;
}
int main()
{
	//freopen("SPOJ_ABCPATH.txt","r",stdin);
	cin >> R >> C;
	int t = 1;
	do{
		//read
		for (int i = 1; i <= R;i++)
		{
			for (int j = 1; j <= C; j++)
			{
				cin >> mat[i][j];
			}
		}
		pathLen = 0;
		//find A 
		for (int i = 1; i <= R; i++)
		{
			for (int j = 1; j <= C; j++)
			{
				if (mat[i][j] == 'A')
					countPath(i,j,1);
			}
		}
		cout << "Case " << t++ << ": " << pathLen << endl;;
		cin >> R >> C;
	} while (R>0 && C>0);
	return 0;
}
#endif
