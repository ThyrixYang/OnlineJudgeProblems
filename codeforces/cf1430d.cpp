#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;
char ss[MAXN];
int a[MAXN];

int main()
{

    int T, N;
    cin >> T;
    for (int Case = 0; Case < T; Case++)
    {
        cin >> N;
        scanf("%s", ss);
        int len = N;
        int cnt = 0;
        int p = 1;
        a[0] = 1;
        for (int i = 1; i < N; i++)
        {
            if (ss[i] == ss[i - 1])
            {
                a[p - 1]++;
            }
            else
            {
                a[p] = 1;
                p++;
            }
        }
        // for (int i = 0; i < p; i++)
        // {
        //     printf("%d", a[i]);
        // }
        // puts("");
        int f = 0, t = f + 1;
        for (int i = 0; i < p; i++)
        {
            if (a[i] > 1)
            {
                cnt++;
            }
            else
            {
                while (t < i)
                    t++;
                while (t < p && a[t] == 1)
                    t++;
                if (t < p)
                {
                    cnt++;
                    a[t]--;
                }
                else
                {
                    cnt += (p - i + 1) / 2;
                    break;
                }
            }
        }
        printf("%d\n", cnt);
    }

    return 0;
}