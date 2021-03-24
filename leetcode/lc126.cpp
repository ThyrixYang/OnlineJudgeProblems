#include <bits/stdc++.h>

using namespace std;

class Solution
{

    vector<vector<int>> revG;
    int stk[6000];
    int stkp;
    unordered_map<string, int> id_map; //存字符串编号

    vector<string> id_rev_map;

    vector<vector<string>> ans;
    int start_id;
    // 要输出所有最短路，所以需要dfs枚举一下
    void dfs(int v)
    {
        stk[stkp++] = v;
        if (v == start_id)
        {
            vector<string> tans;
            for (int i = stkp - 1; i >= 0; i--)
            {
                tans.push_back(id_rev_map[stk[i]]);
            }
            ans.push_back(tans);
            stkp--;
            return;
        }
        for (int i = 0; i < revG[v].size(); i++)
        {
            dfs(revG[v][i]);
        }
        stkp--;
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        int find_end = -1, find_start = -1;
        for (int i = 0; i < wordList.size(); i++)
        {
            if (wordList[i] == beginWord)
                find_start = i;
            if (wordList[i] == endWord)
                find_end = i;
        }
        if (find_end == -1)
            return vector<vector<string>>();
        if (find_start == -1)
        {
            wordList.push_back(beginWord);
            find_start = wordList.size() - 1;
        }
        start_id = find_start;
        stkp = 0;
        // leetcode 126
        // 邻接表存图
        vector<vector<int>> G(wordList.size() + 10, vector<int>());
        id_rev_map = vector<string>(wordList.size() + 10);
        vector<int> dist(wordList.size() + 10, 1e9);
        id_map.clear();
        id_rev_map.clear();
        ans.clear();
        revG.clear();
        // 这题直接两两字符比较建图的话是5000*5000的复杂度
        // 但是由于单词长度只有10,所以枚举相邻的单词只要10*26，这样建图就是5000*260的复杂度
        // 但是map可能有点慢，先试试吧。。。
        for (int i = 0; i < wordList.size(); i++)
        {
            string w = wordList[i];
            id_map[wordList[i]] = i;
            id_rev_map[i] = wordList[i];
        }
        dist[find_start] = 0;
        for (int i = 0; i < wordList.size(); i++)
        {
            string w = wordList[i];
            for (int j = 0; j < wordList[i].length(); j++)
            {
                for (int k = 0; k < 26; k++)
                {
                    char c = 'a' + k;
                    w = wordList[i];
                    w[j] = c;
                    auto it = id_map.find(w);
                    if (it == id_map.end())
                    {
                        continue;
                    }
                    else
                    {
                        int idn = it->second;
                        G[i].push_back(idn);
                    }
                }
            }
        }

        //最短路dijkstra
        priority_queue<pair<int, int>> Q;
        Q.push(make_pair(0, find_start));
        while (!Q.empty())
        {
            int d = -Q.top().first;
            int v = Q.top().second;
            //cerr << "dij " << v << endl;
            Q.pop();
            for (int i = 0; i < G[v].size(); i++)
            {
                int u = G[v][i];
                if (dist[u] > dist[v] + 1)
                {
                    dist[u] = dist[v] + 1;
                    //cerr << "update " << u << " " << dist[u] << endl;
                    Q.push(make_pair(-dist[u], u));
                }
            }
        }

        revG = vector<vector<int>>(wordList.size() + 10, vector<int>());
        for (int i = 0; i < wordList.size(); i++)
        {
            for (int j = 0; j < G[i].size(); j++)
            {
                int u = G[i][j];
                if (dist[u] == dist[i] + 1)
                {
                    revG[u].push_back(i);
                }
            }
        }
        // for (int i = 1; i <= N; i++)
        //     cerr << dist[i] << " ";
        //exit(0);
        if (dist[find_end] > 6000)
            return vector<vector<string>>();
        dfs(find_end);
        return ans;
    }
};

int main()
{
    vector<string> wordList{"hot", "dot", "dog", "lot", "log", "cog"};
    string bw = "hit";
    string ew = "cog";
    Solution sol;
    auto ans = sol.findLadders(bw, ew, wordList);
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}