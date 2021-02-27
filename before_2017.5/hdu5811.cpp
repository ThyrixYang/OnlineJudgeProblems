#include <bits/stdc++.h>
struct Reader{
	static const int MSIZE=65536;
	char buffer[MSIZE],c;
	int l,r;
	Reader():l(0),r(0){}
	char readchar(){
		if(l==r){
			l=0;
			r=fread(buffer,1,MSIZE,stdin);
			//
			buffer[r]=0;
			r++;///注意此处是修改过的
			//
		}
		return buffer[l++];
	}
	int readint(){
		c=readchar();
		while(!isdigit(c)) c=readchar();
		int res=0;
		while(isdigit(c)) res=res*10+c-'0',c=readchar();
		return res;
	}
}R;
const int MAXN = 1005;
int n, m;
int mat[MAXN][MAXN];
int tmp[MAXN];
int a[MAXN], b[MAXN];
int c[MAXN], ch;
struct Node {
    int to, next;
}E[MAXN * MAXN * 2];
int head[MAXN];
int d[MAXN];
int inm[MAXN];
int Q[MAXN * MAXN];
int front, back;
int len1, len2;
int eh;
void addEdge(int from, int to) {
    E[eh].to = to, E[eh].next = head[from];
    head[from] = eh++;
}
int arrange(int *a, int len) {
    front = back = 0;
    std::memset(head, -1, sizeof(int) * (n + 3));
    eh = 0;
    std::memcpy(tmp, a, sizeof(int) * (n + 3));
    std::memset(d, 0, sizeof (int) * (n + 3));
    int c = len;
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            if(mat[tmp[i]][tmp[j]]) {
                addEdge(tmp[i], tmp[j]);
				d[tmp[j]]++;
                /*if(d[tmp[j]]++ == 0) {
                    c--;
                    if(c == 0) return 0;
                }*/
            }
        }
    }
    for(int i = 0; i < len; i++) {
        if(d[tmp[i]] == 0) Q[back++] = tmp[i];
    }
    int h = 0;
    while(front < back) {
        int v = Q[front++];
        a[h++] = v;
        for(int i = head[v]; i != -1; i = E[i].next) {
            int u = E[i].to;
            if(--d[u] == 0) Q[back++] = u;
        }
    }
    if(h < len) return 0;
    else return 1;
}
int dp[MAXN];
int cal() {
    ch = 0;
    for(int i = 0; i < len2; i++) {
        int p = 0;
        for(; p <= len1; p++) {
            if(mat[b[i]][a[p]]) break;
        }
        int f = 1;
        for(int j = p; j < len1; j++) {
            if(!mat[b[i]][a[j]]) {
                f = 0;
                break;
            }
        }
        if(f) c[ch++] = p;
    }
    std::memset(dp, -1, sizeof(int) * (n + 3));
    int ans = 0;
    for(int i = 0; i < ch; i++) {
        dp[i] = 1;
        for(int j = 0; j < i; j++) {
            if(c[j] <= c[i]) dp[i] = std::max(dp[i], dp[j] + 1);
        }
        ans = std::max(ans, dp[i]);
    }
    return ans;
}
char s[MAXN * 6];
int main() {
	freopen("./in", "r", stdin);
    while(1) {
		n = R.readint();
		m = R.readint();
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
				mat[i][j] = R.readint();
            }
        }
        std::memset(inm, 0, sizeof(int) *(n + 3));
        for(int i = 0; i < m; i++) {
            int x;
			x = R.readint();
            inm[x] = 1;
        }
        len1 = 0, len2 = 0;
        for(int i = 1; i <= n; i++) {
            if(inm[i]) a[len1++] = i;
            else b[len2++] = i;
        }
        if(arrange(a, len1) && arrange(b, len2)) {
            printf("YES %d\n", cal());
        } else {
            puts("NO");
        }
    }
    return 0;
}
