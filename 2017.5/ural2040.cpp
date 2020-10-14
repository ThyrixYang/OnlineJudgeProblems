#include <bits/stdc++.h>

const int MAXN = 1e5 + 30;
const int N = 26;
  
struct Palindromic_Tree {  
    int next[MAXN][N] ;//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成  
    int fail[MAXN] ;//fail指针，失配后跳转到fail指针指向的节点  
    int len[MAXN] ;//len[i]表示节点i表示的回文串的长度  
    char S[MAXN] ;//存放添加的字符  
    int last ;//指向上一个字符所在的节点，方便下一次add  
    int n ;//字符数组指针  
    int p ;//节点指针  
  
    inline int newnode ( int l ) {//新建节点  
        for ( int i = 0 ; i < N ; ++ i ) next[p][i] = 0 ;  
        len[p] = l ;  
        return p ++ ;  
    }  
  
    void init () {//初始化  
        p = 0 ;  
        newnode (  0 ) ;  
        newnode ( -1 ) ;  
        last = 0 ;  
        n = 0 ;  
        S[n] = -1 ;//开头放一个字符集中没有的字符，减少特判  
        fail[0] = 1 ;  
    }  
  
    inline int get_fail ( int x ) {//和KMP一样，失配后找一个尽量最长的  
        while ( S[n - len[x] - 1] != S[n] ) x = fail[x] ;  
        return x ;  
    }  
  
    inline void add ( int c ) {  
        c -= 'a' ;  
        S[++ n] = c ;  
        int cur = get_fail ( last ) ;//通过上一个回文串找这个回文串的匹配位置  
        if ( !next[cur][c] ) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串  
            int now = newnode ( len[cur] + 2 ) ;//新建节点  
            fail[now] = next[get_fail ( fail[cur] )][c] ;//和AC自动机一样建立fail指针，以便失配后跳转  
            next[cur][c] = now ;  
        }  
        last = next[cur][c] ;  
    }  
}T;

const int maxlen = 1e5 + 300;
char s[maxlen];
int main() {
	freopen("./in", "r", stdin);
	T.init();
	gets(s);
	int len = strlen(s);
	int last = 2;
	int ans = 0;
	for(int i = 0; i < len; i++) {
		T.add(s[i]);
		printf("%d ",(ans += T.p - last));
		last = T.p;
	}
	return 0;
}
