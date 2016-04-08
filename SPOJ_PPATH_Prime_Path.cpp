#if 1
/// BFS  approach 
#include <iostream>
using namespace std;
#define SZ 10000
int A,B;
int primeno[SZ+1];
bool is_Prime[SZ + 1] = {true};
int que[10000];
int level[SZ + 1] = {0};
int MAX_COUNT = 0;
int front=0;
int rear = 0;;

void fillprimetill10k(void)
{
		for (int i = 0; i <= SZ; i++)
			is_Prime[i] = true;   // sert all true
		for (int no = 2; no*no <= SZ; no++)
		{
			if (is_Prime[no] == true)
			{
				//mark_Multiple
				for (int multi = 2; multi*no < SZ; multi++)
				{
					int multiple = multi*no;
					is_Prime[multiple] = false;
				}

			}
		}	
}
bool isSafe(int x)
{
	//cout << "Checking " << x << endl;
	if (x == A)
		return false;
	if (is_Prime[x] == false)
		return false;
	if (level[x] != 0)
		return false;
	//cout << "TRUE " << endl;
	return true;

}
int count_c(void)
{
	while (front != rear)
	{
		//pop
		int no = que[front++];  
		if (no==B)
			return level[no] - 1;
		if (front == rear)
			front = rear = 0 ;
		
		int x = no;
		int x_u = no % 10;
		int x_t = (no % 100)/10  ;
		int x_h = (no % 1000)/100;
	//	int x_th = (no % 10000)/1000;
		///get units different no .
		for (int i = 0; i <= 9; i++)
		{
			x = x / 10;
			x = x * 10 + i;
			//x = x - x_u + i;
			bool res = isSafe(x);
			if (res == true)
			{
				que[rear++] = x;
				level[x] = level[no] + 1;
			}

		}
		////
		///get TENS different no .
		x = no;
		for (int i = 0; i <= 9; i++)
		{
			x = x / 100;
			x = x * 100 + i*10 + x_u;
			bool res = isSafe(x);
			if (res == true)
			{
				que[rear++] = x;
				level[x] = level[no] + 1;
			}

		}
		////
		///get HUNDREDS different no .
		x = no;
		for (int i = 0; i <= 9; i++)
		{
			x = x / 1000;
			x = x * 1000 + i * 100 +x_t*10+ x_u;
			bool res = isSafe(x);
			if (res == true)
			{
				que[rear++] = x;
				level[x] = level[no] + 1;
			}

		}
		///get Thousand different no .
		x = no;
		for (int i = 1; i <= 9; i++)
		{
			x = i * 1000 +x_h* 100 + x_t * 10 + x_u;
			bool res = isSafe(x);
			if (res == true)
			{
				que[rear++] = x;
				level[x] = level[no] + 1;
			}

		}

	}
	return -1;
}
int main()
{
	std::ios_base::sync_with_stdio(false); // Supposedly makes I/O faster
	int T;
	cin >> T;
	int t = 1;
	fillprimetill10k();
	while (T--)
	{
		cin >> A >> B;
		int count = 0;
		if (A != B)
		{
			MAX_COUNT = 0x7FFFFFFF;
			level[A] = 1;
			que[rear++] = A;
			count = count_c();
		}
		if (count ==-1)
			cout << "Impossible" << endl;
		else
			cout << count << endl;
		///reset
		front = rear = 0;
		for (int i = 999; i <= SZ; i++)
			level[i] = 0;
	}
	return 0;
}
#endif
#if 0
///DFS   2/13 TC TLE 
#include <iostream>
#include <math.h> 
using namespace std;
#define SZ 10000
int A,B;
int primeno[SZ+1];
bool is_Prime[SZ + 1] = {true};
bool visited[SZ + 1] = {false};
int counted[SZ + 1] = { 0 };
int MAX_COUNT = 0;
int front=0;
int rear = 0;
//const int N_SZ = 2;
const int N_SZ =4;
const int N_power = N_SZ - 1;
/// debug
int debug[SZ];
void mark_Multiple(int M, int N)
{
	for (int i = 2; i*M < N ; i++)
	{
		int no = i*M;
		is_Prime[no] = false;
	}

}
void fillprimetill10k(void)
{
	for (int i = 0; i <= SZ; i++)
	{
		is_Prime[i] = true;   // set all true
		counted[i] = 0x7fffffff;
	}
	for (int i = 2; i <= sqrt(SZ);i++)
	{
		if (is_Prime[i] == true)
		{
			mark_Multiple(i, SZ);
		}
	}	
}
bool isSafe(int x)
{
	
	if (x == A)
		return false;
	if (is_Prime[x] == false)
		return false;
	if (visited[x] == true)
		return false;
	//cout << "Checking " << x ;
	//cout << "  TRUE " << endl;
	return true;

}
int getNewNumber(int number, int place, int _new)
{
	int no[N_SZ] = { 0 };
	int k = 0;
	while (k <= N_power)
	{
		no[k++] = number % 10;
		number = number / 10;
	}
	no[place] = _new;
	k = N_SZ - 2;
	int ret = no[N_SZ - 1];
	while (k >=0)
	{
		ret= ret*10 +no[k--];		
	}
	return  ret;

}
void count_c(int number, int depth)
{
	//cout <<number << " at depth "<<depth<< endl;
	if (number == B)
	{
		if (MAX_COUNT > depth)
		{
			MAX_COUNT = depth;
#if 0
			//dEBUG
			cout << MAX_COUNT <<" Path: ";
			for (int i = 0; i < MAX_COUNT; i++)
				cout << debug[i] << "-->";
			cout <<B<< endl;
#endif
		}
		return;
	}
	visited[number] = true;
	counted[number] = depth;  // Dp storing depth to avoid  exploring again at same or lower Depths
	debug[depth] = number;
	
	//////
	for (int p = N_power; p >= 0; p--)
	{
		int k = 1;
		if (p < N_power)
			k = 0;
		for (; k <= 9; k++)
		{
			int NN = getNewNumber(number, p, k);
			if (isSafe(NN) == true && depth + 1 < MAX_COUNT && counted[NN] > depth + 1)
			{
				count_c(NN, depth + 1);
			}
		}
	}
	//////
	visited[number] = false;
	debug[depth] = 0;
	return ;
}

int main()
{
	std::ios_base::sync_with_stdio(false); // Supposedly makes I/O faster
	freopen("COBY_SecurityCode.txt", "r", stdin);
	//freopen("COBY_SecurityCode_OP.txt", "w", stdout);
	int T;
	cin >> T;
	int t = 1;
	fillprimetill10k();
	while (T--)
	{
		cin >> A >> B;
		int count = 0;
		if (A != B)
		{
			MAX_COUNT = 0x7FFFFFFF;
			count_c(A, 0);			
		}
		else
		{
			MAX_COUNT = 0;
		}
		cout << "Case #" << t++ << endl;
		if (MAX_COUNT == 0x7FFFFFFF)
			cout << "Impossible" << endl;
		else
			cout << MAX_COUNT << endl;
		///reset
		for (int i = 999; i <= SZ; i++)
		{
			visited[i] = false;
			counted[i] = 0x7fffffff;
		}
	}
	return 0;
}
/*
4
13 43
13 29
19 47
11 53
ans
1
2
2
2
*/
#endif
