#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN=100;

int sa[kMaxN],lcp[kMaxN],tmp[2*kMaxN];
int *rank,*next_rank;
int delta,n;

inline bool CmpByRank(int i,int j){
	if(rank[i]==rank[j]){
		int ri=i+delta<=n?rank[i+delta]:-1;
		int rj=j+delta<=n?rank[j+delta]:-1;
		return ri<rj;
	}
	return rank[i]<rank[j];
}

void ConstructSA(const string &s){
	n=s.length();
	rank=tmp,next_rank=tmp+n+1;
	for(int i=0;i<=n;i++){
		sa[i]=i;
		rank[i]=i<n?s[i]:-1;
	}
	for(delta=1;delta<=n;delta<<=1){
		sort(sa,sa+1+n,CmpByRank);
		next_rank[sa[0]]=0;
		for(int i=1;i<=n;i++){
			next_rank[sa[i]]=next_rank[sa[i-1]]+CmpByRank(sa[i-1],sa[i]);
		}
		swap(next_rank,rank);
	}
}

void ConstructLCP(const string &s){
	int n=s.length();
	for(int i=0;i<=n;i++){
		rank[sa[i]]=i;
	}
	lcp[0]=0;
	for(int i=0,h=0;i<n;i++){
		int j=sa[rank[i]-1];
		for(h>0?h--:0;j+h<n && i+h<n && s[j+h]==s[i+h];h++);
		lcp[rank[i]-1]=h;
	}
}

int Find(const string &pattern,const string &str){
	int l=0,r=n;
	while(l+1<r){
		int m=l+r>>1;
		if(str.compare(sa[m],pattern.length(),pattern)<0){
			l=m;
		}else{
			r=m;
		}
	}
	if(str.compare(sa[r],pattern.length(),pattern)==0){
		return sa[r];
	}
	return -1;
}

int main(){
	string s,p;
	cin>>s;
	ConstructSA(s);
	ConstructLCP(s);
	for(int i=1;i<=n;i++){
		printf("%d ",sa[i]);
	}
	puts("");
	for(int i=0;i<n;i++){
		printf("%d ",lcp[i]);
	}
	//cin>>p;
	//cout<<Find(p,s)<<endl;
	return 0;
}

