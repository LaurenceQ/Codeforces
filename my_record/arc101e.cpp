#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
const int N = 5e3 + 11;
const int mod = 1e9 + 7;
int g[N], f[N][N];
int sz[N], n;
vector<int> G[N];
inline int A(int x, int y){
	return x + y - (x + y >= mod ? mod : 0);
}
inline int M(int x, int y){
	return 1LL * x * y % mod;
}
void dfs(int u, int fa){
	sz[u] = 1;
	f[u][1] = 1;
	for(int v : G[u]){
		if(v == fa)continue;
		dfs(v, u);
		int sum = 0;
		for(int i = 1;i <= sz[v]; i++)sum = A(sum, M(f[v][i], g[i]));
		for(int i = sz[u];i >= 1; i--){
			int F = f[u][i];
			f[u][i] = 0;
			for(int j = sz[v];j >= 0; j--){
				f[u][i+j] = A(f[u][i+j], M(F, f[v][j]));
			}
			f[u][i] = A(f[u][i], mod - M(F, sum));
		}		
		sz[u] += sz[v];

	}
}
int main(){
	cin>>n;
	int u, v;
	g[0] = 1;
	for(int i = 2;i <= n; i++){
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
		g[i] = M(g[i-2], i - 1);
	}
	dfs(1, 1);
	int ans = 0;
	for(int i = 1;i <= n; i++){
		ans = A(ans, M(g[i], f[1][i]));
	}
	cout<<ans<<endl;
	return 0;
}
