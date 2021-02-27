#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * 最小树形图
 * int型
 * 复杂度O(NM)
 * 点从0开始
 */
const int INF = 0x3f3f3f3f;
const int MAXN = 600;
const int MAXM = 400100;
struct Edge
{
	int u, v, cost;
	Edge(int u = 0, int v = 0, int cost = 0): u(u), v(v), cost(cost) {}
};
Edge edge[MAXM];
int pre[MAXN],id[MAXN],visit[MAXN],in[MAXN];
int zhuliu(int root,int n,int m,Edge edge[])
{
	int res = 0,u,v;
	while(1)
	{
		for(int i = 0;i < n;i++)
			in[i] = INF;
		for(int i = 0;i < m;i++){
			if(edge[i].u != edge[i].v && edge[i].cost < in[edge[i].v])
			{
				pre[edge[i].v] = edge[i].u;
				in[edge[i].v] = edge[i].cost;
			}
		}
		for(int i = 0;i < n;i++)
			if(i != root && in[i] == INF) {
				return -1;//不存在最小树形图
			}
		int tn = 0;
		memset(id,-1,sizeof(id));
		memset(visit,-1,sizeof(visit));
		in[root] = 0;
		for(int i = 0;i < n;i++)
		{
			res += in[i];
			v = i;
			while( visit[v] != i && id[v] == -1 && v != root)
			{
				visit[v] = i;
				v = pre[v];
			}
			if( v != root && id[v] == -1 )
			{
				for(int u = pre[v]; u != v ;u = pre[u])
					id[u] = tn;
					id[v] = tn++;
			}
		}
		if(tn == 0)break;//没有有向环
		for(int i = 0;i < n;i++)
			if(id[i] == -1)
				id[i] = tn++;
		for(int i = 0;i < m;)
		{
			v = edge[i].v;
			edge[i].u = id[edge[i].u];
			edge[i].v = id[edge[i].v];
			if(edge[i].u != edge[i].v)
				edge[i++].cost -= in[v];
			else
				swap(edge[i],edge[--m]);
		}
		n = tn;
		root = id[root];
	}
	return res;
}
int n, m;
int a[1000];
int sum[1000];
int eh = 0;
void addEdge(int from, int to, int w) {
	edge[eh++] = Edge(from, to, w);
}
int main()
{	
	freopen("./in", "r", stdin);
	while(scanf("%d%d", &n, &m) != EOF) {
		if(n == 0 && m == 0) break;
		sum[0] = 1;
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i] + 1;
		int root = 0;
		eh = 0;
		for(int i = 1; i <= n; i++) {
			addEdge(root, sum[i - 1], 0);
			for(int j = 0; j < a[i]; j++) {
				addEdge(sum[i - 1] + j + 1, sum[i - 1]  + j, 0);
			}
		}
		for(int i = 0; i < m; i++) {
			int c, l1, l2, d, y;
			scanf("%d%d%d%d%d", &c, &l1, &d, &l2, &y);
			int id1 = sum[c - 1] + l1;
			int id2 = sum[d - 1] + l2;
			addEdge(id1, id2, y);
		}
		int res = zhuliu(root, sum[n], eh, edge);
		printf("%d\n", res);
	}
	return 0;
}
