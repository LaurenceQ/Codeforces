#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 2e3 + 11;
const int mod = 1e9 + 7;
int head[N], nex[N<<1], to[N<<1],  size;
int fa[N], n, m;
LL X;
LL wei[N<<1], mi[N], t[N];
struct edge{
	int u, v;
	LL w;
}e[N];
bool cmp(edge a, edge b){
	return a.w < b.w;
}
int find(int x){
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void add(int x, int y, int z){
	to[++size] = y, nex[size] = head[x], head[x] = size, wei[size] = z;
}
LL dfs(int u, int ed, int fa){
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(v == fa)continue;
		if(v == ed)return wei[i];
		LL res = dfs(v, ed, u);
		if(res != -1)return max(res, wei[i]);
	}
	return -1;
}
int main(){
	cin>>n>>m>>X;
	mi[0] = 1;
	for(int i = 1;i <= m; i++){
		scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].w);
		mi[i] = (mi[i-1] << 1) % mod;
	}
	sort(e + 1, e + 1 + m, cmp);
	for(int i = 1;i <= n; i++)fa[i] = i;
	LL mn = 0, ans = 0;
	for(int i = 1;i <= m; i++){
		int u = e[i].u, v = e[i].v, w = e[i].w;
		int fu = find(u), fv = find(v);
		if(fu == fv){
//			int res = dfs(u, v, fa)
			t[i] = w - dfs(u, v, u);
		}
		else{
			fa[fu] = fv;
			t[i] = -1;
			mn += w;
			add(u, v, w); add(v, u, w);
		}
	}
//	printf("mn=%lld\n", mn);
	if(X < mn){
		return puts("0"), 0;
	}
	if(mn == X)ans = 1LL * (mi[n-1] - 2) * mi[m-n+1] % mod;
	int cnt1 = 0, cnt2 = 0;
	for(int i = 1;i <= m; i++){
		if(t[i] == -1)continue;
		if(mn + t[i] == X)cnt1++;
		if(mn + t[i] > X)cnt2++;
//		printf("i=%d t=%d\n", i, t[i]);
	}
//	printf("cnt1=%d cnt2=%d\n", cnt1, cnt2);
	ans = (ans + 2LL * (mi[cnt1] - 1) % mod * mi[cnt2] % mod) % mod;
	cout<<ans<<endl;
	return 0;
}
