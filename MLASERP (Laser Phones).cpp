#if 1
/* faced two SIGSEGV due to smaller Quesize SZ*SZ*4 --->changed it and got AC */
#include <iostream>
#include <string.h>
using namespace std;
const int SZ = 102;
char inpt[SZ][SZ] ;
int cnt[4][SZ][SZ] ;
enum DIR{ N,E,S,W };
#define MOD(a,b) ((a>b)?a-b:b-a)
typedef struct{
	int x;
	int y;
	int turn;
	DIR dir;
}_PT;
_PT que[SZ*SZ*4*5];
int frnt = 0, rear = 0;
int R, C;
int SX = 0, SY = 0, DX = 0, DY = 0;
int MIN_DIST = 1 << 30;
void read()
{
	for (int r = 1; r <= R; r++)
	{
		cin >> inpt[r] + 1;//keep first char empty
		if (SX == 0 || DX == 0)
		{
			for (int c = 1; c <= C; c++)
			{
				if (inpt[r][c] == 'C')
				{
					if (SX == 0)
					{
						SX = r; SY = c;
					}
					else
					{
						DX = r; DY = c;
					}
				}
			}
		}
	}
}
inline bool isSafe(int x, int y)
{
	if (x < 1 || x>R || y<1 || y>C||inpt[x][y]=='*')
		return false;
	return true;
}
int dx[] = { -1,0,1,0 }; //// N,E,S,W
int dy[] = { 0,1,0,-1 }; //// N,E,S,W
void bsf()
{
	cnt[0][SX][SY] = cnt[1][SX][SY] = cnt[2][SX][SY] = cnt[3][SX][SY] = 0; //start is always zero
	//push all nbrs of start in Que
	for (int d = 0; d < 4; d++)
	{
		int vx = SX + dx[d] ,vy = SY + dy[d];
		if (isSafe(vx,vy ))
		{
			_PT t; t.x = vx; t.y = vy; t.dir = (DIR)d; t.turn=0;
			que[rear++] = t;
			cnt[d][vx][vy] = 1;
		}
	}
	while (frnt != rear)
	{
		_PT u = que[frnt++];
		if (frnt == rear)
			frnt = rear = 0;
		//push all nbrs of start in Que
		for (int d = 0; d < 4; d++)
		{
			if (MOD(u.dir, d) != 2) ///// only push if its not U turn as that will already be counted
			{	
				_PT v;
				v.x = u.x + dx[d];
				v.y = u.y + dy[d];
				if (isSafe(v.x, v.y))
				{
					v.dir = (DIR)d;
					if (d != u.dir)
						v.turn = u.turn + 1; /// if direction is not same increase turn count
					else
						v.turn = u.turn;
										
					if (v.x == DX && v.y == DY) // no need to push DESTination in QUEUE
					{
						if (MIN_DIST > v.turn)
							MIN_DIST = v.turn;
					}
					else
					{
						if (cnt[d][v.x][v.y] > v.turn) //if prev count for same direction was more only then update and push in Que
						{
							que[rear++] = v;
							cnt[d][v.x][v.y] = v.turn;
						}
					}

				}//safe
			}
		}///for direction
			
	}
}
int main()
{
	std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
	freopen("SPOJ_MLASERP.txt", "r", stdin);
#endif
	cin >> C >> R;
	read();
	memset(cnt, 99, sizeof(int) * 4 * SZ*SZ);
	bsf();
	cout << MIN_DIST;
	return 0;
}
#endif
