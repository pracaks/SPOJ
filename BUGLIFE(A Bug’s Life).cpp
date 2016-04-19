#if 1
#include <iostream>
#include <cstdio>
using namespace std;
//#define TEST

#define SIZE 2002
int NODES,EDGES;
int mat[SIZE][SIZE];
int color[SIZE];
int que[SIZE];
int to_read =0;
int to_write =0;
int vertex_count = 0;
void reset(void)
{
    for(int i =0 ;i<=NODES;i++)
    {
        for(int j = 0 ; j<=NODES;j++)
        {
            mat[i][j] = 0;
        }
        color[i]=-1;
        que[i]=0;
    }
    to_read =0;
    to_write =0;
	vertex_count =0;
}

bool bfs(int u)
{
    color[u]=1;
	//push
    que[to_write++] =u;
	vertex_count++;
    while (to_read != to_write)
    {
       //pop
       u = que[to_read++];
       if(to_read==to_write)
         to_read = to_write =0;
       for(int v= 1 ;v<=NODES;v++)
        {
            if(mat[u][v]==1)
            {
                if(color[v]==-1)
                {   // ive new color
                    color[v] = 1 - color[u];
                    //push v in que
                    que[to_write++] = v ;
					vertex_count++;
                }
                else if(color[u]==color[v])
                {
                    return false;
                }
            }///
        }///for
   } //while
    return true;
}
int main()
{
 int T; 
#ifdef TEST
 freopen("bugs_life_input.txt","r",stdin);
#endif
 scanf("%d",&T);
 int cnt =1;
 while(T--)
 {
 	scanf("%d %d",&NODES,&EDGES);
 	reset();
 	int start = 0;
 	for(int i=1 ; i<=EDGES;i++)
 	{
 		int a, b;
 		scanf("%d %d",&a,&b);
 		mat[a][b] = 1;
 		mat[b][a] = 1;
		mat[a][0]++;
        start = a;
	}

	bool canBipattite = false;
	do {
		canBipattite = false;
		canBipattite = bfs(start);
		if (canBipattite== true && vertex_count < NODES)
		{ // find new start
			for(int i =1 ; i<=NODES;i++)
			{
				if(color[i]==-1 && mat[i][0]>0)
				{	
					start = i;
					break;
				}
			}//for
		}//if
	}while( vertex_count < NODES && canBipattite==true);
	/////RESULT/////

	printf("Scenario #%d:\n",cnt++);
 	if(canBipattite==true)
 		printf("No suspicious bugs found!\n");
 	else
 		printf("Suspicious bugs found!\n");
 } // while TC
    return 0;
}


#endif
