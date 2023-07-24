#include<bits/stdc++.h>
using namespace std;
const int N = 666;
const int mod = 1e9 + 7;
int f[N][N], g[N], s[N];
int n, K, to[N];
inline int A(int x, int y){
	return x + y - (x + y >= mod ? mod : 0);
}
inline int M(int x, int y){
	return 1LL * x * y % mod;
}
int main(){
	cin>>n>>K;
	n <<= 1;
	int u, v;
	for(int i = 1;i <= K; i++){
		scanf("%d%d", &u, &v);
		to[u] = v;
		to[v] = u;
	}
	g[0] = 1;
	for(int i = 1;i <= n; i++){
		s[i] = (!to[i]) + s[i-1];
		if(i > 1)g[i] = M(i - 1, g[i-2]);
	}
	for(int l = 1;l <= n; l++){
		if(to[l]){
			if(to[l] < l)continue;
			bool fl = 1;
			for(int k = l + 1;k < to[l]; k++)
				if(to[k] && (to[k] > to[l] || to[k] < l))fl = 0;
			f[l][to[l]] = fl ? g[s[to[l]]-s[l-1]] : 0;
		}
		for(int r = max(l + 1, to[l] + 1); r <= n; r++){
			bool fl = 1;
			for(int k = l + 1;k <= r; k++){
				if(to[k] && (to[k] > r || to[k] < l))fl = 0;
			}
			if(!fl)continue;
			int F = g[s[r]-s[l-1]];
			for(int p = l + 1;p < r; p++){
				F = A(F, mod - M(f[l][p], g[s[r]-s[p]]));
			}
			f[l][r] = F;
		}
	}
	int ans = 0;
	for(int i = 1;i <= n; i++){
		for(int j = i + 1;j <= n; j++){
			ans = A(ans, M(f[i][j], g[s[n]-(s[j]-s[i-1])]));
//			printf("f[%d][%d]=%d\n", i, j, f[i][j]);
		}
	}
	cout<<ans<<endl;
	return 0;
}
