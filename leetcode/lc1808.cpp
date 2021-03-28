#include <bits/stdc++.h>

using namespace std;

// 二分乱搞

class Solution
{

    double evaluate(int pf, int pn)
    {
        double res = 0;
        if (pf % pn == 0)
        {
            double c = pf / pn;
            return log((double)c) * pn;
        }
        else
        {
            int c1 = pf / pn;
            int c2 = c1 + 1;
            int nc2 = pf % pn;
            int nc1 = pn - nc2;
            double res = log((double)c1) * nc1 + log((double)c2) * nc2;
            return res;
        }
    }

    long long f_exp(long long a, long long p, long long pr)
    {
        long long ans = 1;
        while (p > 0)
        {
            if (p & 1)
            {
                ans = ans * a % pr;
            }
            a = a * a % pr;
            p >>= 1;
        }
        return ans;
    }

public:
    int maxNiceDivisors(int primeFactors)
    {
        long long P = 1e9 + 7;
        int l = 0;
        int r = primeFactors;
        float eps = 1e-9;
        float lv = -1e9;
        float rv = evaluate(primeFactors, r);
        while (r - l > 1)
        {
            int m = (r + l) / 2;
            double mv = evaluate(primeFactors, m);
            double mv2 = evaluate(primeFactors, m + 1);
            // cerr << "m " << m << endl;
            // cerr << mv << " " << mv2 << endl;
            if (mv2 <= mv)
            {
                r = m;
            }
            else
            {
                l = m;
            }
        }
        // cerr << r << endl;
        if (primeFactors % r == 0)
        {
            int c = primeFactors / r;
            return f_exp(c, r, P);
        }
        else
        {
            int c1 = primeFactors / r;
            int c2 = c1 + 1;
            int nc2 = primeFactors % r;
            int nc1 = r - nc2;
            // cerr << c1 << " " << nc1 << " " << c2 << " " << nc2 << endl;
            long long res = f_exp(c1, nc1, P) * f_exp(c2, nc2, P) % P;
            return res;
        }
    }
};

int main()
{
    Solution sol;
    int ans = sol.maxNiceDivisors(545918790);
    cerr << ans << endl;
    return 0;
}