#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 11;
#define LL long long
int n, K;
vector<int> on[11][N];
int gg[N], tim, cnt;
int prm[N];
struct node{
	LL x, y;
	node (int _x = 0, int _y = 0){
//		printf("_x=%d _y=%d\n", _x, _y);
		x = _x; y = _y;
	}
	LL operator * (node b){
		return x * b.x + y * b.y; 
	}
	double len(){
		return sqrt(x * x + y * y);
	}
	LL operator ^ (node b){
		return x * b.y - y * b.x;
	}
	node operator - (node b){
		return node(x - b.x, y - b.y);
	}
}sht[22], mst[N];
bool kill(int x){
	cnt++;
	if(cnt > K)return 0;
	if(!on[prm[cnt]][x].size()){
		gg[x] = tim;
		return 1;
	}
	int s = on[prm[cnt]][x].size();
	int lev = cnt;
	for(int i = 0;i < s; i++){
		int v = on[prm[lev]][x][i];
		if(gg[v] != tim){
			if(!kill(v))return 0;
		}
	}
	gg[x] = tim; return 1;
}
int main(){
	cin>>K>>n;
	int x, y;
	for(int i = 1;i <= K; i++){
		scanf("%d%d", &x, &y);
		sht[i] = node(x, y);
	}	
	for(int i = 1;i <= n; i++){
		scanf("%d%d", &x, &y);
		mst[i] = node(x, y);
	}
	for(int i = 1;i <= K; i++){
		for(int j = 1;j <= n; j++){
			for(int k = 1;k <= n; k++){
				if(j == k)continue;
				node a = mst[k] - mst[j], b = mst[k] - sht[i];						
//				printf("i=%d j=%d k=%d a*b + a.len*b.len=%.4lf\n", i, j, k, a * b + a.len() * b.len());
				if(a * b < 0 && (a ^ b) == 0){
					on[i][j].push_back(k);				
//					puts("XBX");
				}
			}
		}
	}
	int ans = 0;
	for(int i = 1;i <= n; i++){
		for(int j = 1;j <= K; j++)prm[j] = j;
		bool fl = 0;
		do{
			tim++; cnt = 0;
			if(kill(i)){
				fl = 1;
				break;
			}
		}while(next_permutation(prm + 1, prm + 1 + K));
		ans += fl;
//		printf("i=%d fl=%d\n", i, fl);
	}
	cout<<ans<<endl;
	return 0;
}
