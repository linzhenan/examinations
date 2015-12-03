#include <stdio.h>
#include <memory.h>
#include <malloc.h>

#ifdef WIN32
#pragma warning(disable:4996)
#endif

//use a link-list to store neighbor cities for each city
typedef struct CityContext
{
	int id;
	struct CityContext *next;
}
City;

//use a array for random access to each city's neighbor cities link-list
typedef struct CityEntryContext
{
	int start;//0 not start, 1 started
	int distance;
	City *pFirstNeighborCity;
	City *pLastNeighborCity;
}
CityEntry;

typedef struct CityQueueContext
{
	City *front;
	City *rear;
}
CityQueue;

static int InitQueue(CityQueue *q)
{
	q->front = q->rear = (City *)malloc(sizeof(City));
	if (!q->front)
		return 0;
	q->front->next = NULL;
	return 1;
}

static void DestroyQueue(CityQueue *q)
{
	while (q->front)
	{
		q->rear = q->front->next;
		free(q->front);
		q->front = q->rear;
	}
}

static int IsEmptyQueue(CityQueue *q)
{
	return (q->front->next == NULL && q->rear->next == NULL);
}

static int InsertQueue(CityQueue *q, int id)
{
	City *pCity = (City *)malloc(sizeof(City));
	if (!pCity)
		return 0;

	pCity->id = id;
	pCity->next = NULL;

	if (IsEmptyQueue(q))
	{
		q->front->next = pCity;
		q->rear = pCity;
	}
	else
	{
		q->rear->next = pCity;
		q->rear = pCity;
	}
	return 1;
}

static int DeQueue(CityQueue *q, int *id)
{
	City *tmp;
	tmp = q->front->next;
	*id = tmp->id;

	q->front->next = tmp->next;
	if (q->rear == tmp)
		q->rear = q->front;

	free(tmp);

	return 1;
}

int main()
{
	CityEntry *CityEntries;
	City *pCity;

	int n, m;
	int i, j;
	int id1, id2;
	int q, c;
	int distance;

	scanf("%d %d", &n, &m);//2 <= n <= 100000, 1 <= m <= 100000
	
	CityEntries = (CityEntry *)malloc(n * sizeof(CityEntry));
	memset(CityEntries, 0, n * sizeof(CityEntry));

	for (i = 0; i < n - 1; i++)
	{
		scanf("%d %d", &id1, &id2);//1 <= id <= n
		id1--;//0 <= id <= n - 1, for zero-based index
		id2--;//0 <= id <= n - 1, for zero-based index

		//add City2 to City1's neighbor cities link-list
		pCity = (City *)malloc(sizeof(City));
		memset(pCity, 0, sizeof(City));
		pCity->id = id2;
		if (!CityEntries[id1].pFirstNeighborCity)
		{
			CityEntries[id1].pFirstNeighborCity = pCity;
			CityEntries[id1].pLastNeighborCity = pCity;
		}
		else
		{
			CityEntries[id1].pLastNeighborCity->next = pCity;
			CityEntries[id1].pLastNeighborCity = pCity;
		}

		//add City1 to City2's neighbor cities link-list
		pCity = (City *)malloc(sizeof(City));
		memset(pCity, 0, sizeof(City));
		pCity->id = id1;
		if (!CityEntries[id2].pFirstNeighborCity)
		{

			CityEntries[id2].pFirstNeighborCity = pCity;
			CityEntries[id2].pLastNeighborCity = pCity;
		}
		else
		{
			CityEntries[id2].pLastNeighborCity->next = pCity;
			CityEntries[id2].pLastNeighborCity = pCity;
		}
	}

	CityEntries[0].start = 1;//at the beginning, only city No.1 is festive city;

	for (i = 0; i < m; i++)
	{
		scanf("%d %d", &q, &c);//q == 1 or 2, 1 <= c <= n
		c--;//0 <= c <= n - 1, for zero-based index

		if (q == 1)//add the new festive City c
		{
			CityEntries[c].start = 1;
		}
		else if (q == 2)//find shortest distance from City c to closest festive city
		{
			for (j = 0; j < n; j++)
				CityEntries[j].distance = -1;

			CityQueue CityQ;
			InitQueue(&CityQ);
			InsertQueue(&CityQ, c);//add City c into the queue for BFS
			CityEntries[c].distance = 0;
			while (!IsEmptyQueue(&CityQ))
			{
				DeQueue(&CityQ, &c);
				distance = CityEntries[c].distance;

				if (CityEntries[c].start)
				{
					printf("%d\n", distance);
					break;
				}
				else
				{
					distance++;
					//add neighbors of City c into link-list for BFS
					pCity = CityEntries[c].pFirstNeighborCity;
					while (pCity)
					{
						if (CityEntries[pCity->id].distance == -1)//avoid loop
						{
							InsertQueue(&CityQ, pCity->id);
							CityEntries[pCity->id].distance = distance;
						}
						pCity = pCity->next;
					}
				}
			}
			DestroyQueue(&CityQ);
		}
	}

	//free malloc
	for (i = 0; i < n; i++)
	{
		while (CityEntries[i].pFirstNeighborCity)
		{
			CityEntries[i].pLastNeighborCity = CityEntries[i].pFirstNeighborCity->next;
			free(CityEntries[i].pFirstNeighborCity);
			CityEntries[i].pFirstNeighborCity = CityEntries[i].pLastNeighborCity;
		}
	}
	free(CityEntries);

	return 0;
}
