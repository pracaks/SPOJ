#if 1
/*   accepted after 4 WA.
mistake 1 :i was keeping wt(time) in nodes in queue .which is wrong as sometime it got updated by other edge but node in 
           Queue still has old value.. dont keep distance at two places I removed it from queue.
mistake 2 : I was deleting edge (both a--b and b--a) once either of them is done its wrong again from some another path d[a] 
           be decreased at that point of time a--b is not there d[b] will never got updated. 
*/
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
using namespace std;
int F, L;
const int SZ = 1001;
#define LL long long int 
bool mat[SZ][SZ] = {false};
LL timeTaken[SZ];
int que[SZ*SZ];
int qread = 0, qwrite = 0;
LL calc_time(int src, int dest)
{
	if (timeTaken[src] > 0)
	{
		LL wt_time = 0;
		LL tDiff = (src > dest) ? src - dest : dest - src;
		LL travel_time = tDiff;
		LL cycle = 0;
		if (src < dest)  // lift always strat from lower floor 
		{
			cycle = 2*tDiff;			
		}
		else
		{
			cycle = tDiff;			
		}
		while (cycle < timeTaken[src])
		{
			cycle = cycle + 2 * tDiff;
		}
		wt_time = cycle - timeTaken[src];
		return wt_time + travel_time;
	}
	else
	{
		return dest - src;
	}
}
LL bsf(int st)
{
	LL min_time = LLONG_MAX;
	//PUSH
	que[qwrite++] = st;
	timeTaken[st] = 0;
	while (qread != qwrite)
	{
		int u = que[qread++]; ///POP
		//find neighbour
		for (int v = 1; v <= F; v++)
		{
			if (mat[u][v] == true)
			{
				LL t = calc_time(u, v);
				t = t + timeTaken[u];
				if (t < timeTaken[v])
				{
					timeTaken[v] = t;
					if(v!=F)  // dont insert last node 
						que[qwrite++] = v;
				}
				//mat[u][v] = mat[v][u] = false; // this was a mistake 
				if (v == F  && timeTaken[F] < min_time)
				{
					min_time = timeTaken[F];
				}
			}////if			
		}// nbr loop
	}
	return min_time;
}
int main()
{
	std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
	freopen("SPOJ_MELE3.txt", "r", stdin);
#endif
	//	memset(timeTaken, 9999, sizeof(timeTaken));
		cin >> F >> L;
		for (int i = 1; i <= L; i++)
		{
			int a, b;
			cin >> a >> b;
			mat[a][b] = mat[b][a] = true;
		}
		for (int i = 1; i <= F; i++)
			timeTaken[i] = LLONG_MAX;
		LL res = bsf(1);
		cout << res*5 ;
	return 0;
}
#endif
/*
my TC 
10 7
1 5
3 5
1 3
5 7
7 10
3 7
3 10
///45
10 4
1 5
5 10
5 7
7 10
////45
20 5
1 7
7 20
4 7
4 10
10 20
///150

10 3
1 5
3 5
3 10
///105
*/
