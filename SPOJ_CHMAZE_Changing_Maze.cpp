#if 1
/////ACCEptede with ADJ MAtrix as vector 
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
/****
http://www.spoj.com/problems/CHMAZE/ 
****/
#define SIZE 21
#define SZ_PAT 11
typedef struct __node{
int x;
int y;
int pat;
}NODE;
int level[SZ_PAT][SIZE][SIZE];
NODE que[SIZE*SIZE];
int to_read = 0;
int to_write = 0;
int mat[SZ_PAT][SIZE][SIZE];
//bool visited [PAT][SIZE][SIZE];

//#define TEST
int dx[] = {0,0,0,1,-1};
int dy[] = {0,1,-1,0,0};
int ROW,COL,PAT;
int bfs( int r, int c , int p)
{	
	level[p][r][c] = 1;
	NODE temp;
	temp.x = r;
	temp.y = c;
	temp.pat= p;
	//push in Que
	que[to_write++] = temp;
	while(to_read!=to_write)
	{
		//POP
		NODE u = que[to_read++];
		if(to_read==to_write)
			to_read = to_write = 0;
		//Check all adjacent
		for(int i=0;i<5;i++)
		{
			NODE v;
			v.x = u.x + dx[i];
			v.y = u.y + dy[i];
			v.pat = (u.pat+1)%PAT;
			if(mat[v.pat][v.x][v.y]==1 &&level[v.pat][v.x][v.y]==0)
			{
				level[v.pat][v.x][v.y] = level[u.pat][u.x][u.y] + 1;
				if(v.x == ROW && v.y==COL)
					return level[u.pat][u.x][u.y];
				//push in que
				que[to_write++] = v;
			}
			
		}//for
		
	}
	return -1;
}


int main()
{
#ifdef TEST	
	freopen("CHMAZE_input.txt","r",stdin);
#endif
	
	int cnt=1;
	while(1)
	{		
		cin>>ROW>>COL>>PAT;
		if(ROW== 0 &&COL==0 && PAT==0)
			break;
		
		///reset
		to_read = 0;
		to_write = 0;
		for(int p=0;p<PAT;p++)
		{
			for(int i = 1 ; i<=ROW;i++)
			{
				for(int j = 1 ; j<=COL;j++)
				{
					char ch;
					cin>>ch;
					mat[p][i][j]  = ch -'0' + 1;
				}
			}
		}
		//memset(visited,false,sizeof(visited));
		memset(level,false,sizeof(level));
		int res =-1;
		if(ROW==1 &&COL==1)
		{
			res=0;
		}
		else
		{
			res = bfs(1,1,0);
		}
		if(res==-1)
		{
			printf("Case %d: Luke and Leia cannot escape.\n",cnt);
		}
		else
		{
			 printf("Case %d: Luke and Leia can escape in %d steps.\n",cnt,res);
		}
		cnt++;
	}//while
return 0;
}

#endif
