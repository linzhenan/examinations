#include <stdio.h>

#ifdef WIN32
#pragma warning(disable:4996)
#endif

typedef long long int int64_t;

static int64_t max(int64_t a, int64_t b)
{
	if (a > b)
		return a;
	else
		return b;
}

static void process_up_to_down(int64_t max_left_col[500], int64_t max_up_to_down[500], int grid[500][500],
						int n, int m,
						int j, int teleport_enabled)
{
	int i;

	//top, i = 0
	if (grid[0][j] == -1)
	{
		max_up_to_down[0] = -1;
	}
	else
	{
		if (grid[n - 1][j] == -1 || teleport_enabled == 0)//cannot teleport from bottom
		{
			if (max_left_col[0] == -1)
				max_up_to_down[0] = -1;
			else
				max_up_to_down[0] = max_left_col[0] + (int64_t)grid[0][j];
		}
		else
		{
			max_up_to_down[0] = max(max_left_col[0], 0) + (int64_t)grid[0][j];
		}
	}
	//others
	for (i = 1; i < n; i++)
	{
		if (grid[i][j] == -1)
		{
			max_up_to_down[i] = -1;
		}
		else
		{
			if (max_up_to_down[i - 1] == -1)
			{
				if (max_left_col[i] == -1)
					max_up_to_down[i] = -1;
				else
					max_up_to_down[i] = max_left_col[i] + (int64_t)grid[i][j];
			}
			else
			{
				max_up_to_down[i] = max(max_left_col[i], max_up_to_down[i - 1]) + (int64_t)grid[i][j];
			}
		}
	}
}
static void process_down_to_up(int64_t max_left_col[500], int64_t max_down_to_up[500], int grid[500][500],
						int n, int m,
						int j, int teleport_enabled)
{
	int i;

	//bottom, i = n - 1;
	if (grid[n - 1][j] == -1)
	{
		max_down_to_up[n - 1] = -1;
	}
	else
	{
		if (grid[0][j] == -1 || teleport_enabled == 0)//cannot teleport from top
		{
			if (max_left_col[n - 1] == -1)
				max_down_to_up[n - 1] = -1;
			else
				max_down_to_up[n - 1] = max_left_col[n - 1] + (int64_t)grid[n - 1][j];
		}
		else
		{
			max_down_to_up[n - 1] = max(max_left_col[n - 1], 0) + (int64_t)grid[n - 1][j];
		}
	}
	//others
	for (i = n - 2; i >= 0; i--)
	{
		if (grid[i][j] == -1)
		{
			max_down_to_up[i] = -1;
		}
		else
		{
			if (max_down_to_up[i + 1] == -1)
			{
				if (max_left_col[i] == -1)
					max_down_to_up[i] = -1;
				else
					max_down_to_up[i] = max_left_col[i] + (int64_t)grid[i][j];
			}
			else
			{
				max_down_to_up[i] = max(max_left_col[i], max_down_to_up[i + 1]) + (int64_t)grid[i][j];
			}
		}
	}

}
int main()
{
	int m, n;
	int i, j;

	int64_t highest = -1;
	int grid[500][500];
	int64_t max_up_to_down[500];
	int64_t max_down_to_up[500];
	int64_t max_left_col[500] = { 0 };

	scanf("%d %d", &n, &m);
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			scanf("%d", &grid[i][j]);

	for (j = 0; j < m; j++)
	{
		//up to down
		process_up_to_down(max_left_col, max_up_to_down, grid, n, m, j, 0);
		if (max_up_to_down[n - 1] != -1)
			process_up_to_down(max_left_col, max_up_to_down, grid, n, m, j, 1);

		//down to up
		process_down_to_up(max_left_col, max_down_to_up, grid, n, m, j, 0);
		if (max_down_to_up[0] != -1)
			process_down_to_up(max_left_col, max_down_to_up, grid, n, m, j, 1);

		//calc max_left_col for next col
		for (i = 0; i < n; i++)
			max_left_col[i] = max(max_up_to_down[i], max_down_to_up[i]);
	}

	for (i = 0; i < n; i++)
		if (max_left_col[i] > highest)
			highest = max_left_col[i];

#ifdef WIN32
	printf("%I64d\n", highest);
#else
	printf("%lld\n", highest);
#endif

	return 0;
}
