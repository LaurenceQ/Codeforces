#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e5 + 11;
int n, m;
int fa[N], id[N];
LL a[N], b[N], c[N], sum[N], f[N];
bool vis[N];
vector<int> to[N], son;
int find(int x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
bool cmp(int x, int y){
	return c[x] < c[y];
}
int main(){
	cin>>n>>m;
	for(int i = 1;i <= n; i++){
		scanf("%lld%lld", &a[i], &b[i]);
		c[i] = max(0ll, a[i] - b[i]);
	}
	int u, v;
	for(int i = 1;i <= m; i++){
		scanf("%d%d", &u, &v);
		to[u].push_back(v);
		to[v].push_back(u);
	}
	for(int i = 1;i <= n; i++){
		fa[i] = i, id[i] = i;
	}
	sort(id + 1, id + 1 + n, cmp);
	for(int i = 1;i <= n; i++){
		int u = id[i];
		int sz = to[u].size();
		sum[u] = b[u];
		vis[u] = 1;
		son.clear();
 		for(int j = 0;j < sz; j++){
			int v = to[u][j];
			int fu = find(u), fv = find(v);
			if(fu == fv || !vis[v])continue;
			sum[u] += sum[fv];
			fa[fv] = fu;
			son.push_back(fv);
		}
		f[u] = c[u] + sum[u];
		sz = son.size();
		for(int j = 0;j < sz; j++){
			int v = son[j];
			f[u] = min(f[u], sum[u] - sum[v] + max(c[u], f[v]));
		}
	}
	cout<<f[id[n]]<<endl;
	return 0;
}
