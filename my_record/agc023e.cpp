#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 2e5 + 11;
int n, a[N];
int cnt[N], zo[N], s[N], D[N], invD[N];
inline int A(int x, int y){
	return x + y - (x + y >= mod ? mod : 0);
}
inline int M(int x, int y){
	return 1LL * x * y % mod;
}
struct bit{
	int tree[N];
	void add(int x, int v){
		for(;x <= n;x += -x & x)tree[x] = A(tree[x], v);
	}
	int query(int x){
		int ans = 0;
		for(;x;x -= -x & x)ans = A(ans, tree[x]);
		return ans;
	}
	void clear(){
		memset(tree, 0, sizeof(tree));
	}
}T, G;
int ksm(int base, int x){
	int ans = 1;
	while(x){
		if(x & 1)
			ans = M(ans, base);
		base = M(base, base);
		x >>= 1;
	}
	return ans;
}
int main(){
	cin>>n;
	for(int i = 1;i <= n; i++){
		scanf("%d", &a[i]);
		cnt[a[i]]++;
	}
	for(int i = n;i >= 1; i--)cnt[i] += cnt[i+1];
	int tot = 1;
	D[0] = s[0] = 1;
	for(int i = 1;i <= n; i++){
		cnt[i] -= n - i;
		if(cnt[i] <= 0){
			puts("0");
			return 0;
		}
		tot = M(tot, cnt[i]);
		int x = M(cnt[i] - 1, ksm(cnt[i], mod - 2));
		if(x == 0){
			zo[i] = zo[i-1] + 1;
			s[zo[i]] = i;
			D[i] = D[i-1];
		}
		else zo[i] = zo[i-1], D[i] = M(D[i-1], x);
		invD[i] = ksm(D[i], mod - 2);
	}
	tot = M(tot, ksm(2, mod - 2));
	int ans = 0;
	for(int i = 1;i <= n; i++){
		ans = A(ans, M(A(T.query(a[i]), mod - T.query(s[zo[a[i]]] - 1)), M(tot, D[a[i]])));
		T.add(a[i], invD[a[i]]);
	}
	T.clear();
	for(int i = n;i >= 1; i--){
		ans = A(ans, M(G.query(a[i] - 1), tot * 2 % mod));
		ans = A(ans, mod - M(M(tot, D[a[i]]), A(T.query(a[i] - 1), mod - T.query(s[zo[a[i]]] - 1))));
		T.add(a[i], invD[a[i]]);
		G.add(a[i], 1);
	}
	cout<<ans<<endl;
	return 0;
}
