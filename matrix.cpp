#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int kModNum=7777777;

typedef long long ll;

struct Matrix{
	ll m[20][20];
	int row,col;

	Matrix(int _row,int _col):row(_row),col(_col){
		memset(m,0,sizeof(m));
	}

	friend Matrix operator * (const Matrix &lhs,const Matrix &rhs){
		Matrix ans(lhs.row,rhs.col);
		for(int i=1;i<=lhs.row;i++){
			for(int j=1;j<=rhs.col;j++){
				for(int k=1;k<=lhs.col;k++){
					ans.m[i][j]+=lhs.m[i][k]*rhs.m[k][j]%kModNum;
					ans.m[i][j]%=kModNum;
				}
			}
		}
		return ans;
	}
};

Matrix Pow(Matrix &a,ll b){
	Matrix ans=a;
	Matrix tmp=a;
	b--;
	while(b>0){
		if(b&1){
			ans=ans*tmp;
		}
		tmp=tmp*tmp;
		b>>=1;
	}
	return ans;
}

ll f[100];

int main(){
	ll k,n;
	cin>>k>>n;

	Matrix a(k,k),b(1,k);
	for(int i=1;i<=k;i++){
		a.m[i][k]=1;
		a.m[i][i-1]=1;
	}
	f[0]=1;
	for(int i=1;i<=k;i++){
		for(int j=max(i-k,0ll);j<i;j++){
			f[i]+=f[j];
		}
	}
	for(int i=1;i<=k;i++){
		b.m[1][i]=f[i];
	}
	Matrix c=b*Pow(a,n-1);
	cout<<c.m[1][1]<<endl;
	return 0;
}

