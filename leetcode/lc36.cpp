#include <bits/stdc++.h>

using namespace std;

// 模拟

class Solution
{
public:
    bool isValidSudoku(vector<vector<char>> &board)
    {
        bool ans = true;
        for (int i = 0; i < 9; i++)
        {
            set<char> S;
            for (int j = 0; j < 9; j++)
            {
                char cc = board[i][j];
                if (board[i][j] == '.')
                    continue;
                if (S.find(cc) != S.end())
                    ans = false;
                S.insert(cc);
            }
        }

        for (int j = 0; j < 9; j++)
        {
            set<char> S;
            for (int i = 0; i < 9; i++)
            {
                char cc = board[i][j];
                if (board[i][j] == '.')
                    continue;
                if (S.find(cc) != S.end())
                    ans = false;
                S.insert(cc);
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                set<char> S;
                for (int ii = i * 3; ii < i * 3 + 3; ii++)
                {
                    for (int jj = j * 3; jj < j * 3 + 3; jj++)
                    {
                        char cc = board[ii][jj];
                        if (cc == '.')
                            continue;
                        if (S.find(cc) != S.end())
                            ans = false;
                        S.insert(cc);
                    }
                }
            }
        }
        return ans;
    }
};

int main()
{

    return 0;
}