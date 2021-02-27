

#include <bits/stdc++.h>

using namespace std;

const int maxp=1e6+3000;
struct Node{
	int s;
	int val;
	bool flip;
	Node *ch[2];
	Node():s(0),flip(0){}
	int cmp(const int k)const {
		int d=k-ch[0]->s;
		if(d==1) return -1;
		else return d>0;
	}
	void maintain(){
		s=ch[0]->s+ch[1]->s+1;
	}
	void pushdown(){
		if(flip){
			flip=0;
			swap(ch[0],ch[1]);
			ch[0]->flip^=1;
			ch[1]->flip^=1;
		}
	}
}pool[maxp];
Node *null=new Node();
int ph=0;
Node *newNode(){
	Node *n=&pool[ph++];
	n->flip=n->s=0;
	return n;
}
void rotate(Node *&o,int d){
	Node *k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain();
	k->maintain();
	o=k;
}
void splay(Node *&o,int k){
	o->pushdown();
	int d=o->cmp(k);
	if(d==1) k-=o->ch[0]->s+1;
	if(d!=-1){
		Node *p=o->ch[d];
		p->pushdown();
		int d2=p->cmp(k);
		int k2=(d2==0?k:k-p->ch[0]->s-1);
		if(d2!=-1){
			splay(p->ch[d2],k2);
			if(d==d2) rotate(o,d^1);else rotate(o->ch[d],d);
		}
		rotate(o,d^1);
	}
}
Node* merge(Node *left,Node *right){
	splay(left,left->s);
	left->ch[1]=right;
	left->maintain();
	return left;
}
void split(Node *o,int k,Node *&left,Node *&right){
	splay(o,k);
	left=o;
	right=o->ch[1];
	o->ch[1]=null;
	left->maintain();
}
int num=0;
Node *build(int sz){
	if(sz==0) return null;
	Node *n=newNode();
	n->ch[0]=build(sz/2);
	n->val=num++;
	n->ch[1]=build(sz-sz/2-1);
	n->maintain();
	return n;
}
const int maxn=1e6;
char s[maxn];
void print(Node *n){
	if(n==null) return;
	n->pushdown();
	print(n->ch[0]);
	if(n->val!=0)printf("%c",s[n->val-1]);
	print(n->ch[1]);
}
Node *root;
void reverse(int a,int b){
	Node *l,*r,*m,*o;
	split(root,a,l,o);
	split(o,b-a+1,m,r);
	m->flip^=1;
	root=merge(merge(l,m),r);
}
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	gets(s);
	int len=strlen(s);
	root=build(len+1);
	int n;
	cin>>n;
	while(n--){
		int x;
		scanf("%d",&x);
		if(x>1) reverse(1,x);
		if(x+1<len)	reverse(x+1,len);
	}
	print(root);
	return 0;
}
