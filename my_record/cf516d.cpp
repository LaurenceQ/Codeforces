#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e5 + 11;
int n;
int head[N], nex[N<<1], to[N<<1], size;
LL dis[N], d[N], wei[N<<1];
int id[N], fa[N];
struct sett{
	int fa[N], sz[N];
	void init(){
		for(int i = 1;i <= n; i++)fa[i] = i, sz[i] = 1;
	}
	int find(int x){
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	void merge(int x, int y){
		int fx = find(x), fy = find(y);
		fa[fx] = fy;
		sz[fy] += sz[fx];
	}
}G;
bool cmp(int x, int y){
	return d[x] == d[y] ? x < y : d[x] < d[y];
}
void add(int x, int y, int z){
	to[++size] = y;
	nex[size] = head[x];
	head[x] = size;
	wei[size] = z;
}
void dfs(int u, int fa, int &rt){
	if(dis[u] >= dis[rt])rt = u;
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(v == fa)continue;
		dis[v] = dis[u] + wei[i];
		dfs(v, u, rt);
	}
}
void cal(int u, int fa, LL dis){
	d[u] = max(d[u], dis);
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(v == fa)continue;
		cal(v, u, dis + wei[i]);
	}
}
void dfs2(int u){
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(v == fa[u])continue;
		fa[v] = u;
		dfs2(v);
	}
}
int main(){
//	freopen("a.in", "r", stdin);
	cin>>n;
	int u, v, w;
	for(int i = 1;i < n; i++){
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	u = 0;v = 0;
	memset(dis, 0, sizeof(dis));
	dfs(1, 1, u);
	cal(u, u, 0);
	memset(dis, 0, sizeof(dis));
	dfs(u, u, v);
	cal(v, v, 0);
	int rt = 0;
	d[0] = 1e13;
	for(int i = 1;i <= n; i++){
		if(d[i] < d[rt])rt = i;
		id[i] = i;
	}
	dfs2(rt);
	sort(id + 1, id + 1 + n, cmp);
	int q;
	LL L;
	cin>>q;
	while(q--){
		cin>>L;
		G.init();
		int ans = 0;
		for(int l = n, r = n;l >= 1; l--){
			while(d[id[r]] - d[id[l]] > L) G.sz[G.find(id[r])]--, r--;
			ans = max(ans, G.sz[G.find(id[l])]);
			G.merge(id[l], fa[id[l]]);
//			printf("l=%d r=%d dl=%d dr=%d\n", l, r, d[id[l]], d[id[r]]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
