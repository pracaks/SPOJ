#if 1
#include <iostream>
#include <cstdio>
using namespace std;
#define LL unsigned long long 
const int SZ = 51;
LL startPT[SZ];
LL speed[SZ];
int main()
{
#ifdef _WIN32
	freopen("GCJ101BB.txt", "r", stdin);
#endif
	int T;
	cin >> T;
	int t = 1;
	while (T--)
	{
		int swap = 0;
		int N, K;
		LL B,T;
		cin >> N >> K >> B >> T;
		for (int i = 1; i <= N; i++)
		{
			cin >> startPT[i];
		}
		for (int i = 1; i <= N; i++)
		{
			cin >> speed[i];
		}
		int count = 0;
		int cantReach = 0;
		for (int i = N; i >= 1; i--)
		{
			LL distance = B - startPT[i];
			//LL time = distance / speed[i];   // this was a mistake time was gettig rounded off
			LL canCover = T*speed[i];
			if (distance <= canCover)
			{
				count++;
				if (cantReach > 0)
				{
					swap = swap + cantReach;
					//cantReach = 0; dont reset it swap has to be done for all
				}
			}
			else
			{
				cantReach++;
			}
			if (count == K)
				break;
		}
		if (count < K)
		{
			cout << "Case #" << t++ << ": " << "IMPOSSIBLE" << endl;
		}
		else
		{
			cout << "Case #" << t++ << ": " << swap << endl;
		}

	}
	return 0;
}
#endif
