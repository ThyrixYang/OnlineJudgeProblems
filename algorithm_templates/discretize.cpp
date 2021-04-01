#include <bits/stdc++.h>

using namespace std;

struct Discretize
{
    vector<int> value;
    int back;
    void add(int v)
    {
        value.push_back(v);
    }
    void discretize()
    {
        sort(value.begin(), value.end());
        back = unique(value.begin(), value.end()) - value.begin();
    }
    int get_id(int v)
    {
        return lower_bound(value.begin(), value.begin() + back, v) - value.begin();
    }
    int get_size()
    {
        return back;
    }
};