#if 1
#include <iostream>
#include <stdio.h>
using namespace std;
const int SZ = 10001;
char str[SZ];
int max_level =0;
int index = 0;
void tree( int level)
{
	index++;
	if (level > max_level)
		max_level = level;
	if (str[index] == '\0')
		return;
	if (str[index] == 'l')
	{
		return;
	}
	if (str[index] == 'n')
	{
		tree( level + 1); ////left
		tree( level + 1); ////right
	}
	return;
}
int main()
{
#ifdef _WIN32
	freopen("NICEBTRE.txt", "r", stdin);
#endif
	int T;
	cin >> T;
	while (T--)
	{
		max_level = 0;
		index = -1;
		cin >> str;
		tree(0);
		cout << max_level << endl;
	}
	return 0;
}
/*  TCs
7
l
nlnll
nlnnlll
nnnllll
nll
nlnlnlnll
nnlnllnlnlnll
//////
0
2
3
3
1
4
4
*/
#endif
