#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<vector<int>> generateMatrix(int n)
    {
        vector<vector<int>> ans(n, vector<int>(n, -1));
        int value = 1;
        int x = 0, y = 0;
        ans[0][0] = 1;
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        int lastd = 0;
        while (true)
        {
            int f = 0;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[(lastd + i) % 4];
                int ny = y + dy[(lastd + i) % 4];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                {
                    continue;
                }
                if (ans[nx][ny] >= 0)
                    continue;
                x = nx;
                y = ny;
                lastd = lastd + i;
                ans[x][y] = ++value;
                f = 1;
                break;
            }
            if (!f)
                break;
        }
        return ans;
    }
};

int main()
{

    return 0;
}