#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N = 32;
    int cnt = 0;
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = i; j < N; j++)
    //     {
    //         int ij = i * j;
    //         int ijx = (i | j) * (j & i);
    //         if (ij == ijx)
    //             cnt++;
    //         if (ij == ijx)
    //         {
    //             assert((i | j) == j && (i & j) == i);
    //             cout << i << " " << j << " " << i * j << " " << ijx << " " << (i | j) << " " << (j & i) << endl;
    //         }
    //     }
    // }
    // cout << cnt << endl;
    for (int i = 1; i <= 31; i++)
    {
        int cnt1 = 0;
        int x = i;
        while (x > 0)
        {
            cnt1 += x & 1;
            x /= 2;
        }
        cnt += 1 << cnt1;
    }
    cout << cnt << endl;
    return 0;
}
