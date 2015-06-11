#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
struct Point{
	int _x;
	int _y;
	Point(int x, int y) :_x(x), _y(y){}
};

struct MMap{
	int _max_x;
	int _max_y;
	int _min_x;
	int _min_y;
	MMap(int max_x, int max_y, int min_x, int min_y)
		:_max_x(max_x), _max_y(max_y), _min_x(min_x), _min_y(min_y)
	{
		//
	}
};

int solve(vector<Point> &Userdata, vector<Point> &firm, MMap plat);
int EuclideanDistance(Point a, Point b);
int ManhattanDistance(Point a, Point b);
int Cost(vector<Point> &Userdata, vector<Point> &firm, Point &bs,int minCost);

int inline max(int a, int b)
{
	return a > b ? a : b;
}
int inline min(int a, int b)
{
	return a < b ? a : b;
}

int main(int argc, char* argv[])
{
	int t;
	int n, m, a, b;
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		cin >> n >> m >> a >> b;
		int x, y;
		vector<Point> users;
		vector<Point> firms;
		int sum_x = 0;
		int sum_y = 0;
		int max_x = 0, max_y = 0, min_x = n, min_y = m;
		for (int j = 1; j <= a; j++)
		{
			cin >> x >> y;
			users.push_back(Point(x,y));
			/*if (max_x < x)
			{
				max_x = x;
			}
			if (max_y < y)
			{
				max_y = y;
			}
			if (min_x > x)
			{
				min_x = x;
			}
			if (min_y > y)
			{
				min_y = y;
			}*/
			sum_x += x;
			sum_y += y;
			
		}
		for (int j = 1; j <= b; j++)
		{
			cin >> x >> y;
			firms.push_back(Point(x, y));
			if (max_x < x)
			{
				max_x = x;
			}
			if (max_y < y)
			{
				max_y = y;
			}
			if (min_x > x)
			{
				min_x = x;
			}
			if (min_y > y)
			{
				min_y = y;
			}
		}
		/*
		max_x = max(max_x, sum_x / a + 1);
		max_y = max(max_y, sum_y / a + 1);
		min_x = min(min_x, sum_x / a);
		min_y = min(min_y, sum_y / a);*/
		max_x = n;
		max_y = m;
		min_x = 0;
		min_y = 0;
		int res = solve(users, firms, MMap(max_x, max_y, min_x, min_y));
		cout << "Case #" << i << ": " << res << endl;
	}	
	return 0;
}

int EuclideanDistance(Point a, Point b)
{
	int dis_x = a._x - b._x;
	int dis_y = a._y - b._y;
	int ret = dis_x*dis_x + dis_y*dis_y;
	return ret;
}

int ManhattanDistance(Point a, Point b)
{
	int ret = abs(a._x - b._x) + abs(a._y - b._y);
	return ret;
}

int solve(vector<Point> &Userdata, vector<Point> &firm, MMap plat)
{
	int cost = 0;
	int minCost = 65535;
	int size_u = Userdata.size();
	int size_f = firm.size();
	int gx = plat._max_x;
	int gy = plat._max_y;
	int lx = plat._min_x;
	int ly = plat._min_y;
	for (int i = lx; i <= gx; i++)
	{
		for (int j = ly; j <= gy; j++)
		{
			cost = 65535;
			int mm;
			for (int k = 0; k < size_f; k++)
			{
				mm = ManhattanDistance(Point(i,j), firm[k]);
				if (mm < cost)
				{
					cost = mm;
				}
			}
			if (cost > minCost)
			{
				break;
			}
			for (int k = 0; k < size_u; k++)
			{
				cost += EuclideanDistance(Point(i, j), Userdata[k]);
				if (cost > minCost)
				{
					break;
				}
			}
			//cost = Cost(Userdata, firm, Point(i, j), minCost);
			if (cost < minCost)
			{
				minCost = cost;			
			}
		}
	}
	return minCost;
}
int Cost(vector<Point> &Userdata, vector<Point> &firm, Point &bs,int minCost)
{
	int size_u = Userdata.size();
	int size_f = firm.size();
	int res = 65535;
	int mm;
	for (int i = 0; i < size_f; i++)
	{
		mm = ManhattanDistance(bs, firm[i]);
		if (mm < res)
		{
			res = mm;
		}

	}
	if (minCost < res)
	{
		cout << "manhatten" << endl;
		return minCost;
	}
	for (int i = 0; i < size_u; i++)
	{
		res += EuclideanDistance(bs, Userdata[i]);
		if (minCost < res)
		{
			cout << bs._x << "," << bs._y << "--->";
			cout << i << endl;
			//return minCost;
			break;
		}
		cout << "---->" << i << endl;
	}
	return res;
}