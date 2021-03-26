#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        vector<int> ans;
        int maxx = matrix.size();
        int maxy = matrix[0].size();
        int x = 0, y = 0;
        ans.push_back(matrix[0][0]);
        matrix[0][0] = -1001;
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
                if (nx < 0 || nx >= maxx || ny < 0 || ny >= maxy)
                {
                    continue;
                }
                if (matrix[nx][ny] < -1000)
                    continue;
                x = nx;
                y = ny;
                lastd = lastd + i;
                ans.push_back(matrix[x][y]);
                matrix[x][y] = -1001;
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