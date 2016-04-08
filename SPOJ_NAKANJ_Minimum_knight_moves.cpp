#if 1
#include <stdio.h>
#include <iostream>
using namespace std;

typedef struct __PT{
	int x;
	int y;
	int level;
}PT;
#define SZ 9

PT que[SZ * SZ] ;
int SIZE = 8;
int visited[SZ][SZ] = {0};
int mov_x[] ={2,2,1,1,-1,-1,-2,-2};
int mov_y[] ={1,-1,2,-2,2,-2,1,-1};
int main()
{
	int T;
#ifdef TEST
	freopen("NAKANJ.txt","r",stdin);
#endif
	cin>>T;
	while(T--)
	{
		int answer  = -1 ;
		bool ReachedDest = false;
		int to_read =0;
        int to_write = 0;
		PT st , ed;
		char ch ;
		cin>>ch>>st.y;
		st.x = ch -'a' + 1 ;
		cin>>ch>>ed.y;
		ed.x = ch -'a' + 1 ;
		
		///////
		if(st.x==ed.x && st.y==ed.y)
		{
			answer =0;
		}
		else
		{
			st.level = 0;
			que[to_write++] = st;
			visited[st.x][st.y] = 1 ;
		}
		while(to_read!=to_write && answer == -1)
		{
			///pop 
			PT u = que[to_read++];
		
			//for ALL neighbours
			for(int i=0;i<8;i++)
			{
				int x = u.x + mov_x[i];
				int y = u.y + mov_y[i];
				if(x ==ed.x &&  y==ed.y)
				{
					ReachedDest = true;
					answer = u.level + 1;
					break;
				}
				if(x<1 || y<1 || x>SIZE || y>SIZE || visited[x][y]==1)
				{
					////Ignore that point
				}
				else
				{
					//Increase level and insert valid point in QUEUE
					PT v;
					v.x = x;
					v.y = y;
					v.level = u.level+1;
					visited[v.x][v.y] = 1 ;
					que[to_write++] =v;
				}
			}//for

			if(ReachedDest==true)
			   break;

		}//while que
		////RESULT
		cout<<answer<<endl;
		////////////RESET///
		for(int i=1;i<=SIZE;i++)
		{
			for(int j=1;j<=SIZE;j++)
			{
				visited[i][j] = 0;
			}
		}
	}//while Testcase
	return 0;
}
#endif
