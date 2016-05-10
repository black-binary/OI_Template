#include <cstdio>
#include <cstring>

using namespace std;
char pattern[1000];
char text[1000];
int fail[1000];

void GetFail(char *p,int *f){
	int n=strlen(p);
	f[0]=0;
	for(int i=2,j=0;i<n;i++){
		while(j && p[i]!=p[j]){
			j=f[j-1];
		}
		if(p[i]==p[j]){
			j++;
		}
		f[i]=j;
	}
}

int Match(char *p,char *t,int *f){
	int n=strlen(p);
	int m=strlen(t);
	for(int i=0,j=0;i<m;i++){
		while(j && t[i]!=p[j]){
			j=f[j-1];
		}
		if(t[i]==p[j]){
			j++;
		}
		if(j==n){
			return i-n+1;
		}
	}
	return -1;
}

int main(){
	puts("Enter the pattern");
	scanf("%s",pattern);
	GetFail(pattern,fail);
	puts("Enter the text");
	scanf("%s",text);
	printf("Matched Position: %d",Match(pattern,text,fail));
	getchar();
	getchar();
	return 0;
}

