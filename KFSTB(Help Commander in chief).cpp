#if 1
/**** 10 WAs **********/
#include <iostream>
#include <cstdio>
using namespace std;
int const SZ = 10005
int mat[SZ][SZ];
bool visited[SZ];
long long  path[SZ];
int NODES,EDGES;
#define MOD 1000000007

void reset(void)
{
	for (int i =1;i<=NODES;i++)
		{
			for (int j =1;j<=NODES;j++)
			{
				mat[i][j]=0;			
			}
			visited[i]=false;
			path[i] = 0;
		}
}


long long  count_path(int u , int ed ,int parent)
{
	long long pathFromMe = 0;
	long long  pathfrom_child = 0;
	if(u==ed && parent!=-1)
	{
		return 1;
	}
	/// for all adjacent 
	for (int v =1 ; v<=NODES;v++)
	{
		if(mat[u][v]==1 && visited[v]==false )
		{
			if( path[v]==0)
			{ 
				visited[v]=true;
				pathfrom_child = count_path(v,ed,u);				
				visited[v]=false;
			}
			else
			{
				pathfrom_child  =  (path[v]%MOD);
			}
			//ADD child count to current node's path
			pathFromMe =  ((pathFromMe%MOD) + (pathfrom_child%MOD))%MOD;
		}//if
	}//for
	path[u] = pathFromMe;
	return pathFromMe;
}
int main()
{
#ifdef _WIN32
	freopen("KFSTB_cont_input.txt","r",stdin);
#endif
	int T;
	cin>>T;
	while(T--)
	{
		cin>>NODES>>EDGES;
		int st,ed;
		cin>>st>>ed;
		reset();
		for (int i =1;i<=EDGES;i++)
		{
			int x,y;
			cin>>x>>y;
			mat[x][y]=1;	///directed one way			
		}
		long long path_count = 0;
		visited[st]=true;
		if (st != ed)
			path_count = count_path(st, ed, -1);
		else
			path_count = 1;
		/////answer/////
		cout<<path_count<<endl;
		reset();

	}
	return 0;
}
#endif
