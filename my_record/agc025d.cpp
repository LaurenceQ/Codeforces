#include<bits/stdc++.h>
using namespace std;
int n;
int D1, D2;
bool vis[666][666];
void work(int D){
	int t = 0;
	while(D % 4 == 0)t++, D >>= 2;
	if(D % 4 == 1){
		for(int i = 0;i < n; i++){
			for(int j = 0;j < n; j++){
				if((i >> t & 1) + (j >> t & 1) == 1)vis[i][j] = 1;
			}
		}
	}
	if(D % 4 == 2){
		for(int i = 0;i < n; i++){
			for(int j = 0;j < n; j++){
				if(i >> t & 1)vis[i][j] = 1;
			}
		}
	}
}
int main(){
	cin>>n>>D1>>D2;
	n <<= 1;
	work(D1); work(D2);
	int tot = (n >> 1) * (n >> 1);
	for(int i = 0;i < n; i++){
		for(int j = 0;j < n; j++){
			if(!vis[i][j]){
				printf("%d %d\n", i, j);
				tot--;
				if(!tot)exit(0);
			}
		}
	}
	return 0;
}
