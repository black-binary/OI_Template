#include <cstdio>
#include <climits>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

struct Node{
	Node *left,*right;
	ll begin,end;
	ll sum,delta;
	Node(ll _begin,ll _end,Node *_left=NULL,Node *_right=NULL){
		left=_left;
		right=_right;
		begin=_begin;
		end=_end;
		sum=delta=0;
	}
};

Node *BuildTree(ll begin,ll end){
	if(begin==end){
		return new Node(begin,end);
	}else{
		ll mid=begin+end>>1;
		return new Node(begin,end,BuildTree(begin,mid),BuildTree(mid+1,end));
	}
}

inline void PushDown(Node *x){
	if(x->delta){
		if(x->left){
			x->left->delta+=x->delta;
			x->left->sum+=x->delta*(x->left->end-x->left->begin+1);
			x->right->delta+=x->delta;
			x->right->sum+=x->delta*(x->right->end-x->right->begin+1);
		}
		x->delta=0;
	}
}

void Update(Node *x,ll begin,ll end,ll val){
	if(!x || begin>end || x->begin>end || x->end<begin){
		return;
	}
	if(x->begin>=begin && x->end<=end){
		x->delta+=val;
		x->sum+=val*(x->end-x->begin+1);
	}else{
		PushDown(x);
		Update(x->left,begin,end,val);
		Update(x->right,begin,end,val);
		x->sum=0;
		if(x->left){
			x->sum+=x->left->sum;
			x->sum+=x->right->sum;
		}
	}
}

ll Query(Node *x,ll begin,ll end){
	if(!x || begin>end || x->begin>end || x->end<begin){
		return 0;
	}
	if(x->begin>=begin && x->end<=end){
		return x->sum;
	}else{
		PushDown(x);
		return Query(x->left,begin,end)+Query(x->right,begin,end);
	}
}

int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	Node *root=BuildTree(1,n);
	for(int i=1;i<=n;i++){
		int t;
		scanf("%d",&t);
		Update(root,i,i,t);
	}
	while(q--){
		char buf[20];
		int b,e;
		scanf("%s%d%d",buf,&b,&e);
		if(*buf=='Q'){
			printf("%lld\n",Query(root,b,e));
		}else{
			int val;
			scanf("%d",&val);
			Update(root,b,e,val);
		}
	}
	return 0;
}

