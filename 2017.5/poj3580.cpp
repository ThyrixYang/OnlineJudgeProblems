#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> P;
const int MAXN = 2e5 + 3000;
struct Node
{
	int key, value;
	int minValue, addValue, size;
	bool rev;
	int sonl, sonr;
}T[MAXN];
int N, M;
int root = 0;
int nodeP = 0;
void Init()
{
	srand(233);
	T[0].minValue = T[0].value = 1e9;
}
void PushUp(int o)
{
	if(!o) return;
	T[o].size = T[T[o].sonl].size + T[T[o].sonr].size + 1;
	T[o].minValue = min(T[T[o].sonl].minValue, T[T[o].sonr].minValue);
	T[o].minValue = min(T[o].value, T[o].minValue);
}
void PushDown(int o)
{
	if(!o) return;
	int sl = T[o].sonl;
	int sr = T[o].sonr;
	if(T[o].addValue)
	{
		int v = T[o].addValue;
		if(sl)
		{
			T[sl].addValue += v;
			T[sl].value += v;
			T[sl].minValue += v;
		}
		if(sr)
		{
			T[sr].addValue += v;
			T[sr].value += v;
			T[sr].minValue += v;
		}
		T[o].addValue = 0;
	}
	if(T[o].rev)
	{
		T[o].rev = 0;
		if(sl) T[sl].rev ^= 1;
		if(sr) T[sr].rev ^= 1;
		swap(T[o].sonl, T[o].sonr);
	}
}
void Merge(int &rootL, int rootR)
{
	PushDown(rootL);PushDown(rootR);
	if(rootL == 0) swap(rootL, rootR);
	if(rootR == 0) return;
	if(T[rootL].key > T[rootR].key) Merge(T[rootL].sonr, rootR);
	else Merge(rootL, T[rootR].sonl), T[rootR].sonl = rootL,
		rootL = rootR;
	PushUp(rootL);
}
P Split(int o, int n)
{
	if(n == 0) return P(0, o);
	PushDown(o);
	if(T[T[o].sonl].size >= n)
	{
		P res = Split(T[o].sonl, n);
		T[o].sonl = res.second;
		PushUp(o);
		return P(res.first, o);
	}
	else
	{
		P res = Split(T[o].sonr, n - T[T[o].sonl].size - 1);
		T[o].sonr = res.first;
		PushUp(o);
		return P(o, res.second);
	}
}
void Insert(int x, int pos)
{
	nodeP++;
	T[nodeP].value = T[nodeP].minValue = x;
	T[nodeP].size = 1, T[nodeP].key = rand();
	P res = Split(root, pos);
	Merge(res.first, nodeP);
	Merge(res.first, res.second);
	root = res.first;
}
void PrintTree(int);
void GetInterval(int &pl, int &pm, int &pr, int l, int r)
{
	P res = Split(root, l - 1);
	pl = res.first;
	res = Split(res.second, r - l + 1);
	pm = res.first, pr = res.second;
}
void Merge(int &pl, int pm, int pr)
{
	Merge(pl, pm);
	Merge(pl, pr);
	root = pl;
}
void PrintTree(int o)
{
	if(o == 0) return;
	PushDown(o);
	printf("id %d;   key %d;  value %d; size %d\n", 
			o, T[o].key, T[o].value, T[o].size);
	printf("sonl %d;  sonr %d;\n", T[o].sonl, T[o].sonr);
	PrintTree(T[o].sonl);
	PrintTree(T[o].sonr);
}
char sc[100];
int pl, pm, pr;
int main()
{
	Init();
	freopen("./in", "r", stdin);
	scanf("%d", &N);
	for(int i = 0; i < N; i++)
	{
		int x;
		scanf("%d", &x);
		Insert(x, i);
	}
	scanf("%d", &M);
	while(M--)
	{
		scanf("%s", sc);
		if(sc[0] == 'A')
		{
			int x, y, d;
			scanf("%d%d%d", &x, &y, &d);
			GetInterval(pl, pm, pr, x, y);
			T[pm].value += d, T[pm].addValue += d;
			T[pm].minValue += d;
			Merge(pl, pm, pr);
		}
		else if(sc[0] == 'R' && sc[3] == 'E')
		{
			int x, y;
			scanf("%d%d", &x, &y);
			GetInterval(pl, pm, pr, x, y);
			T[pm].rev ^= 1;
			Merge(pl, pm, pr);
		}
		else if(sc[0] == 'R')
		{
			int x, y, t;
			scanf("%d%d%d", &x, &y, &t);
			t %= (y - x + 1);
			if(t)
			{
				GetInterval(pl, pm, pr, x, y);
				P res = Split(pm, y - x + 1 - t);
				Merge(res.second, res.first);
				Merge(pl, res.second, pr);
			}
		}
		else if(sc[0] == 'I')
		{
			int x, pos;
			scanf("%d%d", &pos, &x);
			Insert(x, pos);
		}
		else if(sc[0] == 'D')
		{
			int x;
			scanf("%d", &x);
			GetInterval(pl, pm, pr, x, x);
			Merge(pl, pr);
			root = pl;
		}
		else if(sc[0] == 'M')
		{
			int x, y;
			scanf("%d%d", &x, &y);
			GetInterval(pl, pm, pr, x, y);
			int ans = T[pm].minValue;
			printf("%d\n", ans);
			Merge(pl, pm, pr);
		}
	}
	return 0;
}
