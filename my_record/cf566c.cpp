#include<bits/stdc++.h>
using namespace std;
#define N 200010
#define db double
int n, ans1;
int head[N], nex[N<<1], to[N<<1], size;
db wei[N<<1], w[N], d[N];
db ans2, sum;
int sz[N], S, rt, mi;
bool vis[N];
void add(int x, int y, int z){
	to[++size] = y;
	nex[size] = head[x];
	wei[size] = z;
	head[x] = size;
}
void get_sz(int u, int fa){
	sz[u] = 1;
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(v == fa || vis[u])continue;
		get_sz(v, u);
		sz[u] += sz[v];
	}
}
void get_rt(int u, int fa){
	int ma = 0;
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(vis[v] || fa == v)continue;
		get_rt(v, u);
		ma = max(ma, sz[v]); 
	}
	ma = max(ma, S - sz[u]);
	if(ma < mi) mi = ma, rt = u;
}
void cal(int u, int fa, db dis){
	sum += sqrt(dis * dis * dis) * w[u];
	d[u] = 1.5 * sqrt(dis) * w[u];
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(v == fa)continue;
		cal(v, u, dis + wei[i]);
		d[u] += d[v];
	}
}
void dfs(int u, int fa){
	get_sz(u, fa);
	S = sz[u]; mi = 1e9;
	get_rt(u, fa);
	if(vis[rt])return ;
	vis[rt] = 1;
	sum = 0; d[rt] = 0;
	for(int i = head[rt];i;i = nex[i]){
		int v = to[i];
		cal(v, rt, wei[i]);
		d[rt] += d[v];
	}
	if(ans2 - sum >= 1e-18) ans2 = sum, ans1 = rt;
	for(int i = head[rt];i;i = nex[i]){
		int v = to[i];
		if(d[rt] - 2.0 * d[v] < 0){
			dfs(v, rt);
			return ;
		}
	}
}
int main(){
	cin>>n;
	if(n == 1){
		printf("1 0\n");
		return 0;
	}
	for(int i = 1;i <= n; i++){
		scanf("%lf", &w[i]);
	}
	int u, v, l;
	for(int i = 1;i < n; i++){
		scanf("%d%d%d", &u, &v, &l);
		add(u, v, l); add(v, u, l);
	}
	ans2 = 1e42;
	dfs(1, 1);
	printf("%d %.7lf\n", ans1, ans2);
	return 0;
}
