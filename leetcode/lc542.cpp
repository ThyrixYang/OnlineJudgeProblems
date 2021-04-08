#include <bits/stdc++.h>

using namespace std;

// 最短路

class Solution
{
public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dist(matrix.size(), vector<int>(matrix[0].size(), 1e9));
        queue<pair<int, int>> Q;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == 0)
                {
                    Q.push(make_pair(i, j));
                    dist[i][j] = 0;
                }
            }
        }
        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {-1, 1, 0, 0};
        while (!Q.empty())
        {
            auto p = Q.front();
            int x = p.first;
            int y = p.second;
            Q.pop();
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    continue;
                if (dist[nx][ny] > dist[x][y] + 1)
                {
                    dist[nx][ny] = dist[x][y] + 1;
                    Q.push(make_pair(nx, ny));
                }
            }
        }
        return dist;
    }
};

int main()
{

    return 0;
}