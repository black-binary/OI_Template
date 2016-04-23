#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int kMaxN=100001;

struct Node{
	Node *left,*right;
	int size;
	Node(){
		size=0;
	}
};

Node *null,*root[kMaxN];
int i2n[kMaxN];
int size;
int a[kMaxN];

Node *CreatNode(){
	static int cnt=-1;
	static Node pool[kMaxN*40];
	cnt++;
	pool[cnt].left=pool[cnt].right=null;
	return pool+cnt;
}

void Maintain(Node *x){
	x->size=0;
	x->size+=x->left->size;
	x->size+=x->right->size;
}

void Insert(Node *&prev,Node *&cur,int begin,int end,int val){
	cur=CreatNode();
	if(begin==end){
		*cur=*prev;
		cur->size++;
	}else{
		int middle=begin+end>>1;
		if(val<=i2n[middle]){
			cur->right=prev->right;
			Insert(prev->left,cur->left,begin,middle,val);
		}else{
			cur->left=prev->left;
			Insert(prev->right,cur->right,middle+1,end,val);
		}
		Maintain(cur);
	}
}

int Find(Node *&s,Node *&t,int begin,int end,int k){
	if(begin==end){
		return i2n[begin];
	}
	int middle=begin+end>>1;
	int rank=t->left->size-s->left->size;
	if(rank<k){
		return Find(s->right,t->right,middle+1,end,k-rank);
	}else{
		return Find(s->left,t->left,begin,middle,k);
	}
}

void Initialize(int *a,int n){
	null=new Node();
	null->left=null->right=null;
	memcpy(i2n,a,sizeof(int)*(n+1));
	sort(i2n+1,i2n+n+1);
	size=unique(i2n+1,i2n+n+1)-i2n-1;
	root[1]=root[0]=null;
	for(int i=1;i<=n;i++){
		Insert(root[i-1],root[i],1,size,a[i]);
	}
}

int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
	}
	Initialize(a,n);
	while(q--){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",Find(root[l-1],root[r],1,size,k));
	}
	return 0;
}


