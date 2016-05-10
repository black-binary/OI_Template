#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int kCharSetSize=129;

struct ACAM{
	struct Node{
		Node *next[129],*fail;
		int id,len;
		bool visited;
		Node(){
			memset(next,0,sizeof(Node*)*129);
			fail=NULL;
			id=len=0;
			visited=false;
		}
	};
	Node *root,*tmp;

	ACAM(){
		root=new Node();
		tmp=new Node();
		for(int i=0;i<kCharSetSize;i++){
			tmp->next[i]=root;
		}
	}

	void Insert(char *str,int id){
		int n=strlen(str);
		Node *x=root;
		for(int i=0;i<n;i++){
			char c=str[i];
			if(!x->next[c]){
				x->next[c]=new Node();
			}
			x=x->next[c];
		}
		x->id=id;
		x->len=n;
	}

	void BuildFail(){
		root->fail=tmp;
		queue<Node *> q;
		q.push(root);
		while(!q.empty()){
			Node *u=q.front();
			q.pop();
			for(int i=0;i<kCharSetSize;i++){
				Node *v=u->next[i];
				if(v){
					Node *f=u->fail;
					while(!f->next[i]){
						f=f->fail;
					}
					v->fail=f->next[i];
					q.push(v);
				}
			}
		}
		root->fail=root;
	}

	void Match(char *str,int *ans){
		int n=strlen(str);
		Node *x=root;
		for(int i=0;i<n;i++){
			char c=str[i];
			while(x!=root && !x->next[c]){
				x=x->fail;
			}
			if(x->next[c]){
				x=x->next[c];
				Node *tmp=x;
				while(tmp!=root && !tmp->visited){
					tmp->visited=true;
					if(tmp->id){
						ans[tmp->id]=i-tmp->len+2;
						tmp->id=0;
					}
					tmp=tmp->fail;
				}
			}
		}
	}
};

int main(){
	static char text[600001];
	static char pattern[700];
	scanf("%s",text);
	int n;
	scanf("%d",&n);
	ACAM a;
	for(int i=1;i<=n;i++){
		scanf("%s",pattern);
		a.Insert(pattern,i);
	}
	a.BuildFail();
	static int ans[200];
	a.Match(text,ans);
	for(int i=1;i<=n;i++){
		printf("%d",ans[i]);
	}
	return 0;
}

