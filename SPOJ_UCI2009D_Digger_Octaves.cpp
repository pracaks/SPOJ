
/*
http://www.spoj.com/problems/UCI2009D/
AC in second attempt
how ans is 5 for second TC
XXX        XXX      XXX      XX_       _XX
XXX        X_X      XXX      XXX       XXX
XX_        XXX      _XX      XXX       XXX
12365478 12369874 12369854  14789652  23654789
conditions: 
Each octate must be unique.
We can start from anywhere.
We cannot revisit a MINE again . 
*/
#include <iostream>
#include <string>
#include <set>

using namespace std;
#define SZ 9
#define OCT 8
char mat[SZ][SZ];
#define AXE 'X'
#define DOT '.'
int octave = 0;
int N;
typedef struct {
	int x;
	int y;
}_PT;
_PT pt[SZ];

inline bool isSafe(int x, int y)
{
	if (x<1 || x>N || y<1 || y>N)
		return false;
	return true;
}
string mysort(void)
{
	_PT arr[SZ];
	for (int i = 1; i <= OCT ; i++)
	{
		arr[i] = pt[i];
	}
	for (int i = 1; i <= OCT - 1; i++)
	{		
		for (int j = 1; j <= OCT -i; j++)
		{
			if (arr[j].x > arr[j + 1].x || (arr[j].x == arr[j + 1].x   && arr[j].y > arr[j + 1].y))
			{
				_PT temp = arr[j + 1];
				arr[j + 1]= arr[j];
				arr[j] = temp;
				
			}
		}
	}
	string s1("");
	int k = 0;
	for (int i = 1; i <= OCT; i++)
	{
		s1.insert(s1.end(), 'a' + arr[i].x);
		s1.insert(s1.end(), 'k' + arr[i].y);
	}
	return s1;
}
int dx[] = {-1,0,1, 0};
int dy[] = { 0,1,0,-1};
set<string>my;
void count_oct(int ux, int uy, int done)
{
	if (done == OCT)
	{
		octave++;
		//// sort pt array
		 string ss = mysort();
		 my.insert(ss);
		return;
	}
	for (int d = 0; d < 4; d++)
	{
		int vx = ux + dx[d];
		int vy = uy + dy[d];
		if (true == isSafe(vx, vy) && mat[vx][vy] == AXE)
		{
			mat[vx][vy] = DOT;
			pt[done + 1].x = vx;
			pt[done + 1].y = vy;
			count_oct(vx, vy, done + 1);
			mat[vx][vy] = AXE; //backtrack
		}
	}
}
void SPOJ_UCI2009D_Digger_Octaves(void)
{
	int T;
	freopen("SPOJ_UCI2009D_Digger_Octaves.txt", "r", stdin);
	cin >> T;
	while (T--)
	{
		cin >> N;
		octave = 0;
		my.clear();
		pt[1].x = pt[1].y = pt[2].x = pt[2].y = pt[3].x = pt[3].y = pt[4].x = pt[4].y = 0;
		pt[5].x = pt[5].y = pt[6].x = pt[6].y = pt[7].x = pt[7].y = pt[8].x = pt[8].y = 0;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> mat[i][j];
			}
		}
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (AXE == mat[i][j])
				{
					mat[i][j] = DOT;
					pt[1].x = i;
					pt[1].y = j;
					count_oct(i,j,1);
					mat[i][j] = AXE; // this was missing earlier
				};
			}
		}//for
		cout << my.size() << endl;
	}
}
int main()
{
	SPOJ_UCI2009D_Digger_Octaves();
	return 0;
}
