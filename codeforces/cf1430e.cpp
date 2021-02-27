#include <bits/stdc++.h>

using namespace std;

#include <string.h>
#define lowbit(x) ((x) & ((x) ^ ((x)-1)))
const int MAXN = 1e6;
typedef int elem_t;

struct BIT
{
    int a[MAXN], c[MAXN], ret;
    int n;
    void init(int i)
    {
        memset(a, 0, sizeof(a));
        memset(c, 0, sizeof(c));
        n = i;
    }
    void update(int i, elem_t v)
    {
        for (v -= a[i], a[i++] += v; i <= n; c[i - 1] += v, i += lowbit(i))
            ;
    }
    elem_t query(int i)
    {
        for (ret = 0; i; ret += c[i - 1], i ^= lowbit(i))
            ;
        return ret;
    }
};

char s[MAXN];
char rs[MAXN];
int N;
int lastpos[30];
BIT bit;

int main()
{
    cin >> N;
    scanf("%s", s + 1);
    bit.init(MAXN);
    long long ans = 0;
    for (int i = 1; i <= N; i++)
    {
        rs[i] = s[N - i + 1];
    }
    for (int i = N; i >= 1; i--)
    {
        lastpos[s[i] - 'a'] = i;
    }
    for (int i = 1; i <= N; i++)
    {
        bit.update(i, 1);
    }
    // cout << bit.query(0) << " " << bit.query(1) << " " << bit.query(2) << " " << bit.query(6) << " " << bit.query(5) << endl;
    // exit(0);
    for (int i = 1; i <= N; i++)
    {
        int s1 = bit.query(lastpos[rs[i] - 'a'] + 1);
        //cout << s1 << endl;
        ans += s1 - 1;
        int c = rs[i] - 'a';
        bit.update(lastpos[c], 0);
        lastpos[c]++;
        while (lastpos[c] <= N && s[lastpos[c]] - 'a' != c)
            lastpos[c]++;
    }
    cout << ans << endl;

    return 0;
}