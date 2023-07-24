#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 11;
int n;
double p[N][N], f[N], w[N];
bool vis[N];
int main(){
	cin>>n;
	if(n == 1){
		puts("0");
		return 0;
	}
	int x;
	for(int i = 1;i <= n; i++){
		for(int j = 1;j <= n; j++){
			scanf("%d", &x);
			p[i][j] = 1.0 * x / 100.0;	
		}
	}
	for(int i = 1;i < n; i++){
		w[i] = 1.0 - p[i][n];
		f[i] = 1;
	}
	for(int i = 1;i <= n; i++){
		int u = 0;
		double mi = 1e19;
		for(int j = 1;j < n; j++){
			if(vis[j])continue;
			if(f[j] / (1.0 - w[j]) < mi)u = j, mi = f[j] / (1.0 - w[j]); 
		}
//		printf("i=%d u=%d mi=%.4lf f=%.4lf mu=%.4lf\n", i, u, mi, f[u], 1.0 - w[u]);
		if(u == 1){
			printf("%.12lf\n", mi);
			return 0;
		}
		vis[u] = 1;
		for(int j = 1;j < n; j++){
			if(vis[j])continue;			
			f[j] += p[j][u] * w[j] * mi;
			w[j] *= (1.0 - p[j][u]);
		}
	}
	return 0;
}
