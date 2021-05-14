///////////////////////// Implement of defs.h //////////////////////
////////////////////////////////////////////////////////////////////

#include "defs.h"


#define maxn 1000
#define maxf 1000000000

vector<long> G[1000];
long a[maxn][maxn] = { 0 };

void display()
{

}

vector<long>* DFS(int u, int v)
{
	int visited[maxf] = { 0 };
	vector<long> path;
	path.push_back(u);


	vector<long>* index = new vector<long> [maxn];
	int count = 0;
	visited[u] = 1;
	if (u == v)
	{
		count++;
		for (int i = 0; i < path.size(); i++)
		{
			index[count - 1].push_back(path[i]);
		}
	}

	else
	{
		for (int i = 0; i < path.size(); i++)
		{
			long y = G[u][i];
			if (visited[y] == 0)
			{
				visited[y] = 1;
				path.push_back(y);
				DFS(y, v);
				path.pop_back();
			}
		}
	}
	visited[u] = 0;
	return index;
}

int DFScount(int u, int v)
{
	int visited[maxf] = { 0 };
	vector<long> path;
	path.push_back(u);


	vector<long>* index = new vector<long>[maxn];
	int count = 0;
	visited[u] = 1;
	if (u == v)
	{
		count++;
		for (int i = 0; i < path.size(); i++)
		{
			index[count - 1].push_back(path[i]);
		}
	}

	else
	{
		for (int i = 0; i < path.size(); i++)
		{
			long y = G[u][i];
			if (visited[y] == 0)
			{
				visited[y] = 1;
				path.push_back(y);
				DFScount(y, v);
				path.pop_back();
			}
		}
	}
	visited[u] = 0;
	return count;
}

long MST(int n)
{
	int visited[maxn] = { 0 };
	visited[1] = 1;
	int k = 0;
	long sum = 0;
	while (k < n - 1)
	{
		long min = maxf;
		for (int i = 1; i <= n; i++)
		{
			if (visited[i] == 1)
			{
				for (int j = 1; j <= n; j++)
				{
					if (visited[j] != 1)
					{
						if (a[i][j] != 0 && min > a[i][j])
						{
							min = a[i][j];
							visited[j] = 1;
						}
					}
				}
			}

		}
		sum += min;
		k++;
	}
	return sum;
	
}



int processPole(long N, int k)
{
	long poleStart, HPo, poleFinish;
	if (N == NULL) return -1;
	else
	{
		poleStart = N / 10000;
		N = N % 10000;
		HPo = N / 100;
		poleFinish = N % 100;
	}
	if (k == 1) return poleStart;
	else if (k == 2) return HPo;
	else if (k == 3) return poleFinish;
}


int travel(int N, eventList* pEventList)
{
	if (N > 999 || N < -999) return -1;
	int HPk = (N > 0) ? N : -N;;
	while (pEventList != NULL)
	{
		int pole = 1;
		int polepoint = 2;
		eventList* temp;
		temp = pEventList;
		vector<long> list_events;
		list_events.push_back(temp->nEventCode);
		while (temp->pNext != NULL)
		{
			pole++;
			temp = temp->pNext;
			list_events.push_back(temp->nEventCode);
		}

		long dinh[maxn];
		dinh[1] = processPole(list_events[0], 1);
		dinh[2] = processPole(list_events[0], 3);
		int dem = 2, set;
		while (list_events.size() > 1)
		{
			for (int i = 1; i < pole; i++)
			{
				for (int j = 0; j < i; j++)
				{
					if (processPole(list_events[j], 3) == processPole(list_events[i], 3)) { set = 0; break; }
					else set = 1;
				}
				if (set == 1)
				{
					dem++;
					dinh[dem] = processPole(list_events[i], 3);
				}
			}
		}

		for (int i = 1; i <= dem; i++)
		{
			if (dinh[i] == processPole(list_events[pole - 1], 3))
			{
				long swap = dinh[i];
				dinh[i] = dinh[dem];
				dinh[dem] = swap;
			}
		}

		for (int k = 0; k < pole; k++)
		{
			for (int i = 1; i <= dem; i++)
				for (int j = 1; j <= dem; j++)
				{
					if (dinh[i] == processPole(list_events[k], 1) && dinh[j] == processPole(list_events[k], 3))
					{
						G[i].push_back(j);
						G[j].push_back(i);
						a[i][j] = processPole(list_events[k], 2);
					}
				}
		}

		int count = DFScount(1, dem);


		//case 1
		if (HPk > 0 && HPk < 200)
		{
			long HPo = processPole(list_events[0], 2);
			for (int i = 1; i < pole; i++)
			{
				HPo += processPole(list_events[i], 2);
			}
			return HPk + pole + HPo;
		}

		//case 2
		else if (HPk >= 200 && HPk < 600) 
		{
			for (int i = 0; i < count; i++)
			{
				for (int j = 0; j < DFS(1, dem)[i].size() - 1; j++)
				{
					if (a[j][j + 1] == 99) DFS(1, dem)->erase(DFS(1, dem)->begin() + i);
				}
			}
			if (DFS(1, dem)->size() == 0) return -1;


			long min1 = maxn;
			long min2 = maxn;
			for (int i = 0; i < count; i++)
			{
				int sum1 = 0;
				int sum2 = 0;
				for (int j = 0; j < DFS(1, dem)[i].size() - 1; j++)
				{
					if (a[j][j + 1] == 0)
					{
						for (int k = 0; k < DFS(1, dem)[i].size() - 1; k++) {
							sum2 += a[k][k + 1];
						}
					}
					else sum1 += a[j][j + 1];
				}
				if (min1 > sum1) min1 = sum1;
				if (min2 > sum2) min2 = sum2;
			}

			if(min2 != 0) return (min2 < HPk) ? min2 : -1;
			else return (min1 < HPk) ? min1 : -1;
		}
		//case 3
		else if (HPk >= 600 && HPk < 999) 
		{
			for (int i = 0; i < count; i++)
			{
				for (int j = 0; j < DFS(1, dem)[i].size() - 1; j++)
				{
					if (HPk == 888) {
						long Legolas = 0;
						for (int k = 0; k < DFS(1, dem)[i].size() - 1; k++)
						{
							if (a[j][j + 1] == 99 && a[k][k + 1] == 0) {
								
								for (int r = 0; r < DFS(1, dem)[i].size() - 1; r++) {
									Legolas += a[r][r + 1];
								}
							}
						}
						return Legolas;
					}
					if (a[j][j + 1] == 99) DFS(1, dem)->erase(DFS(1, dem)->begin() + i);
				}
			}
			if (DFS(1, dem)->size() == 0) return -1;


			long max1 = 0;
			long max2 = 0;
			for (int i = 0; i < count; i++)
			{
				int sum1 = 0;
				int sum2 = 0;
				for (int j = 0; j < DFS(1, dem)[i].size() - 1; j++)
				{
					if (a[j][j + 1] == 0)
					{
						for (int k = 0; k < DFS(1, dem)[i].size() - 1; k++) {
							sum2 += a[k][k + 1];
						}
					}
					else sum1 += a[j][j + 1];
				}
				if (max1 < sum1) max1 = sum1;
				if (max2 < sum2) max2 = sum2;
			}

			if (max2 != 0) return (max2 < HPk) ? max2 : -1;
			else return (max1 < HPk) ? max1 : -1;
		}

		else if(HPk == 999) 
		{
			return MST(dem);
		}
	}






	pEventList = NULL;
	return 0;
}

bool checkSCC(int N, eventList* pEventList)
{
	return 0;
}
