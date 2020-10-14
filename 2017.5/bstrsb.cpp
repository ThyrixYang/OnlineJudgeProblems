#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

const int maxs=1e6;
int n;
int ch[maxs][26];
int val[maxs];
char s[300];
int sz;
int main(){
	freopen("./in","r",stdin);
	while(cin>>n){
		memset(ch[0],0,sizeof(int)*26);
		sz=1;
		for(int i=0;i<n;i++){
			scanf("%s",s);
			if(s[0]=='i'){
				scanf("%s",s);
				int len=strlen(s);
				int v=0;
				for(int j=0;j<len;j++){
					int c=s[j]-'a';
					if(ch[v][c]==0){
						memset(ch[sz],0,sizeof(int)*26);
						ch[v][c]=sz;
						val[sz++]=0;
					}
					v=ch[v][c];
					val[v]++;
				}
			}else if(s[0]=='d'){
				scanf("%s",s);
				int len=strlen(s);
				int cnt=0;
				int v=0;
				for(int j=0;j<len;j++){
					int c=s[j]-'a';
					if(ch[v][c]==0){
						v=0;
						break;
					}
					v=ch[v][c];
				}
				if(v==0) continue;
				cnt=val[v];
				v=0;
				for(int j=0;j<len;j++){
					int c=s[j]-'a';
					v=ch[v][c];
					val[v]-=cnt;
				}
				memset(ch[v],0,sizeof(int)*26);
			}else{
				scanf("%s",s);
				int len=strlen(s);
				int v=0;
				for(int j=0;j<len;j++){
					int c=s[j]-'a';
					if(ch[v][c]==0){
						v=0;
						break;
					}
					v=ch[v][c];
				}
				if(val[v]) puts("Yes");
				else puts("No");
			}
		}
	}
	return 0;
}
