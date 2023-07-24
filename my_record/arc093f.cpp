#include<bits/stdc++.h>
using namespace std;
const int MAXN = 18;
const int MAXM = (1 << 17) + 11;
const int mod = 1e9 + 7;
int f[MAXN][MAXM];
int fac[MAXM], inv[MAXM];
int n, m, a[MAXN], ans;
inline int A(int x, int y){
	return x + y - (x + y >= mod ? mod : 0);
}
inline int M(int x, int y){
	return 1LL * x * y % mod;
}
inline int C(int n, int m){
	if(n < m)return 0;
	if(n < 0 || m < 0)return 0;
	return M(fac[n], M(inv[n-m], inv[m]));
}
int main(){
	fac[0] = inv[0] = fac[1] = inv[1] = 1;
	for(int i = 2;i <= 1 << 17; i++){
		fac[i] = M(fac[i-1], i);
		inv[i] = mod - 1LL * mod / i * inv[mod%i] % mod;
	}
	for(int i = 2;i <= 1 << 17; i++){
		inv[i] = M(inv[i-1], inv[i]);
	}
	cin>>n>>m;
	for(int i = 1;i <= m; i++){
		cin>>a[i];
	}
	f[m+1][0] = 1;
	for(int i = m + 1;i > 1; i--){
		for(int s = 0;s < 1 << n; s++){
			if(!f[i][s])continue;
			f[i-1][s] = A(f[i-1][s], f[i][s]);
			for(int j = 0;j < n; j++){
				if(s >> j & 1)continue;
				int S = s | (1 << j);
				f[i-1][S] = A(f[i-1][S], M(f[i][s], M(C((1 << n) - s - a[i-1], (1 << j) - 1), fac[1<<j])));
			}
		}
	}
	for(int i = 0;i < 1 << n; i++){
		int cnt = 0;
		for(int j = 0;j < n; j++)cnt += i >> j & 1;
		int sum = M(f[1][i], M(fac[(1<<n)-i-1], 1 << n));
		if(cnt & 1)ans = A(ans, mod - sum);
		else ans = A(ans, sum);
//		printf("i=%d cnt=%d sum=%d\n", i, cnt, sum);
	}
	cout<<ans<<endl;
	return 0;
}
