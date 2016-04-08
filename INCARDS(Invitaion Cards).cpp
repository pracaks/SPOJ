#if 1
        /// Accepted  .54 Sec 
/* What Needs to find here is Sum of Minimum distance of all NODES from Node 1  and sum of minimum distances from ALL nodes to node 1 
 a,b,c,d   ans = A + B ,  A  = mindist(a->b) + mindist(a->c) + mindist(a->d)
                          B  = mindist(b->a) + mindist(c->a) + mindist(d->a)
 Floyd Warshal will give TLE . Trick here is Running Dijkastra from source 1 to find A 	(Minimum distance of all NODES from Node 1)
  and to find B ( sum of minimum distances from ALL nodes to node 1)  Run Dijkastra on TRANSPOSE of given DIRECTED GRAPH with source 1.
  */
	#include<iostream>
	#include <stdio.h>
	#include <string.h> //memset
	#include <vector>
	using namespace std;
	#define VERTEX 1000000
	#define INT_MAX 0x7FFFFFFF
	typedef struct{
		int v;
		long c;
	}__NODE;
	class PQ
	{
	private:
		int index[VERTEX + 1];
		__NODE heap[VERTEX + 1];
		int size;

		int LEFT(int k) { return 2 * k; }
		int RIGHT(int k) { return 2 * k + 1; }
		int PARENT(int k){ return k / 2; }
		void sink(int k);
		void swim(int k);
		void SWAPI(int a, int b);
		bool IsLess(int a, int b){ return (heap[a].c < heap[b].c) ? true : false; }
		bool IsMore(int a, int b){ return (heap[a].c > heap[b].c) ? true : false; }

	public:
		PQ() :size(0), maxSize(0){};
		int maxSize;
		void decreaseKey(int vertex, int val);
		void InsertKey(int val, int vertex);
		__NODE delTOP(void);
		long getkey(int v);
		bool IsEmpty(void) { return (size == 0) ? true : false; };
		void reset(void);

	};

	class PQ pq;
	typedef vector < pair<int, long> > _LIST;
	long dijkastra(int N, vector < _LIST > &aList)
	{
		long dist = 0;;
		pq.maxSize = N;
		bool done[VERTEX + 1] = { false };
		for (int i = 1; i <= N; i++)
		{
			pq.InsertKey(i, INT_MAX);
			done[i] = false;
		}
		pq.decreaseKey(1, 0);  // source = 0
		while (pq.IsEmpty() == false)
		{
			__NODE U = pq.delTOP();  //EXTRACT- MIN from Priority QUEUE		
			dist = dist + U.c; //Keep acumlating distances
			done[U.v] = true; //set min_v to done 
			////RELAXATION
			for (int i = 0; i < (int)aList[U.v].size(); i++)
			{
				int u = U.v;
				int v = aList[U.v][i].first;
				long Euv = aList[U.v][i].second;
				if (done[v] == false && U.c + Euv < pq.getkey(v))
				{
					//update dist 
					pq.decreaseKey(v, U.c + Euv);
				}
			}
		}
		pq.reset();		//RESET  PQ 
		memset(done, 0, sizeof(done)); // RESET 
		return dist;
	}
	int main()
	{
		//freopen("INCARDS_input.txt","r", stdin);
		int T ,N,E;
		cin >> T;
		while (T--)
		{
			cin >> N >> E;
			vector <_LIST> adjList(N + 1);
			for (int i = 1; i <= E; i++)
			{
				int u, v, c;
				cin>>u>>v>>c;
				adjList[u].push_back(make_pair(v, c));
			}
			//Dijkastra 
			long res = dijkastra(N, adjList);
			//Transpose 
			vector <_LIST> TPadjList(N + 1);
			for (int u = 1; u <= N; u++)
			{
				for (int j = 0; j < (int)adjList[u].size(); j++)
				{
					int v = adjList[u][j].first;
					int c = adjList[u][j].second;
					TPadjList[v].push_back(make_pair(u, c));
				}
			}
			res = res + dijkastra(N, TPadjList);
			cout << res << endl;
		}
		return 0;
	}
	//////
	/* Get Key(distance ) value from Heap of Vertex V*/
	long PQ::getkey(int v)
	{
		return heap[index[v]].c;
	}
	void PQ::reset(void)
	{
		//for (int i = 1; i <= maxSize; i++)
		{
			//	heap[i].v = heap[i].c = index[i] = -1;
		}
		size = 0;
		maxSize = 0;
	}
	/*Swap Two Elements of given indexes Also updateds the index Array*/
	void PQ::SWAPI(int a, int b){
		__NODE t = heap[a]; heap[a] = heap[b]; heap[b] = t;
		index[heap[a].v] = a;
		index[heap[b].v] = b;
	}
	/*Inreases size of Heap and Insert element at Last Index and Maintains the MIN condition of HEAP by SWIM*/
	void PQ::InsertKey(int vertex, int val)
	{
		heap[++size].c = val; //Increase Last Index and Insert Element there 
		heap[size].v = vertex;
		index[vertex] = size;
		swim(size); // Heapify from Last element Bottom UP
	}
	/*Update(decrease) value of Key(Distance) and MAintaince MIN HEAP by Heapifying from updated index.*/
	void PQ::decreaseKey(int vertex, int val)
	{
		int v = index[vertex]; //get Heap Index "v" for given vertex 
		heap[v].c = val;  //update value
		swim(v);  // Heapify 
	}
	/* BOTTOM up HEAPIFY  pushes Larger no to TOP  */
	void PQ::swim(int k)
	{
		while (k > 1 && IsMore(PARENT(k), k))
		{
			SWAPI(k, PARENT(k));
			k = k / 2; 	//k = PARENT(k)
		}
	}
	/*TOP DOWN  HEAPIFY pushes Smaller non to BOTTOM */
	void PQ::sink(int k)
	{
		while (k <= size / 2)
		{
			int j = LEFT(k);
			//if (j + 1 <= size && IsLess(LEFT(k),RIGHT(k)))
			if (j + 1 <= size && IsMore(j, j + 1))
				j++;
			if (IsMore(k, j))
			{
				SWAPI(k, j);
				k = j;
			}
			else
				break;
		}

	}
	/* Deletes TOP of HEAP (MIN Value) Replaces last value with ROOT and HEAPIFY....*/
	__NODE PQ::delTOP(void)
	{
		__NODE ret = heap[1];
		SWAPI(1, size);
		index[heap[size].v] = -1;
		//heap[size].c = -1; // delete last entry	
		//heap[size].v = -1;
		size--;
		sink(1);
		return ret;
	}
	#endif
