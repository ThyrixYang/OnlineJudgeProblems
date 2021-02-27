#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1010;
bool used[N][N];
void prepare()
{
}
int main()
{
	for(int i = 1; i <= 1000; ++i)
		for(int j = 1; j <= 1000; ++j)
		{
			for(int k = 1; k < max(i, j); ++k)
			{
				if(i > k && !used[i - k][j])
				{
					used[i][j] = 1;
					break;
				}
				if(j > k && !used[i][j - k])
				{
					used[i][j] = 1;
					break;
				}
				if(i > k && j > k && !used[i - k][j - k])
				{
					used[i][j] = 1;
					break;
				}
			}
			if(!used[i][j] && i < j)
				printf("a[%d][%d] = 1;\n", i, j);
		}
	return 0;
}
