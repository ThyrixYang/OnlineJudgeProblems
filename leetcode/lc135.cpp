#include <bits/stdc++.h>

using namespace std;

// 拓扑排序

class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        vector<int> ind(ratings.size() + 5, 0);
        vector<vector<int>> G(ratings.size() + 5, vector<int>());
        for (int i = 1; i < ratings.size(); i++)
        {
            int f = i - 1;
            if (ratings[i] > ratings[f])
            {
                G[f].push_back(i);
                ind[i]++;
            }
            if (ratings[i] < ratings[f])
            {
                G[i].push_back(f);
                ind[f]++;
            }
        }
        vector<int> candy(ratings.size(), 1);
        queue<int> Q;
        for (int i = 0; i < ratings.size(); i++)
        {
            if (ind[i] == 0)
                Q.push(i);
        }
        while (!Q.empty())
        {
            int v = Q.front();
            Q.pop();
            for (int i = 0; i < G[v].size(); i++)
            {
                int u = G[v][i];
                ind[u]--;
                candy[u] = max(candy[u], candy[v] + 1);
                if (ind[u] == 0)
                    Q.push(u);
            }
        }
        int ans = 0;
        for (int i = 0; i < candy.size(); i++)
        {
            ans += candy[i];
        }
        return ans;
    }
};

int main()
{

    return 0;
}