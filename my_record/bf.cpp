#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e6 + 11;
LL mod, m, K, s[N], f[N];
int main(){
	freopen("a.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	memset(s, -1, sizeof(s));
	cin>>K>>mod>>m;
	for(int i = 0;i < m; i++){
		cin>>s[i];
	}
	int q;
	cin>>q;
	LL pos, v;
	for(int i = 1;i <= q; i++){
		cin>>pos>>v;
		s[pos] = v;
	}
	f[1] = 1;
	for(int i = 2;i <= K; i++){
		f[i] = 1LL * (1LL * f[i-1] * s[i-1] % mod + 1LL * f[i-2] * s[i-2] % mod) % mod;
		s[i] = s[i] == -1 ? s[i%m] : s[i];
//		printf("i=%d f=%lld\n", i, f[i]);
	}
	cout<<f[K]<<endl;
	return 0;
}
