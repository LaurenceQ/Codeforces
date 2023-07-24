#include<bits/stdc++.h>
using namespace std;
const int N = 111;
const int mod = 1e9 + 7;
int f[N][N];
int h[N], d[N], n, tot;
int ksm(int base, int x){
	int ans = 1;
	while(x){
		if(x & 1)ans = 1LL * ans * base % mod;
		x >>= 1;
		base = 1LL * base * base % mod;
	}
	return ans;
}
int main(){
	cin>>n;
	for(int i = 1;i <= n; i++){
		scanf("%d", &h[i]);
		d[++tot] = h[i];
	}
	sort(d + 1, d + 1 + tot);
	tot = unique(d + 1, d + 1 + tot) - (d + 1);
	f[1][0] = (ksm(2, h[1]) - 2 * ksm(2, h[1] - d[1]) % mod + mod) % mod;
	for(int i = 1;i <= tot && d[i] <= h[1]; i++){
		if(d[i] < h[1])f[1][i] = 2ll * (ksm(2, h[1] - d[i]) - ksm(2, h[1] - d[i+1]) + mod) % mod;
		else f[1][i] = 2;
	}
	for(int i = 1;i < n; i++){
//		printf("i=%d\n", i);
		int x = lower_bound(d + 1, d + 1 + tot, h[i+1]) - d;
		for(int j = 0;d[j] <= h[i] && j <= tot; j++){
			if(h[i] >= h[i+1]){
				if(d[j] < h[i+1])f[i+1][j] = f[i][j];
				else{
					f[i+1][x] = (f[i+1][x] + 2 * f[i][j] % mod) % mod;
				}
			}
			else{
				if(d[j] < h[i]){
					f[i+1][j] = (f[i+1][j] + 1LL * f[i][j] * ksm(2, h[i+1] - h[i]) % mod) % mod;
				}
				if(d[j] == h[i]){
					for(int k = j;k < x; k++){
						f[i+1][k] = (f[i+1][k] + 2LL * f[i][j] * (ksm(2, h[i+1] - d[k]) - ksm(2, h[i+1] - d[k+1]) + mod) % mod);
					}
					f[i+1][x] = 2 * f[i][j] % mod;
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0;i <= tot; i++){
		ans = (ans + f[n][i]) % mod;
	}
	cout<<ans<<endl;
	return 0;
}
