#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 11;
int n, m;
int cha[N], fa[N];
int dfn[N], tot, sz[N];
int U, V;
int head[N], nex[N<<1], to[N<<1], size = 1;
bool vis[N<<1];
int fr[N];
int dl[N], zh[N], tp;
void add(int x, int y){
	to[++size] = y;
	nex[size] = head[x];
	head[x] = size;
}
void dfs(int u){
	dfn[u] = ++tot;
	sz[u] = 1;
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(v == fa[u])continue;
		if(!dfn[v]){
			fa[v] = u;
			dfs(v);
			sz[u] += sz[v];
			cha[u] += cha[v];	
		}
		else if(dfn[v] < dfn[u]){
			cha[u]++; cha[v]--;
		}
	}
	if(!U && cha[u] > 1){
		U = u;
		return ;
	}

}
void bfs(int x, int id){
	int hd = 0, tl = 1;
	dl[1] = x;
	for(int i = 1;i <= n; i++)fr[i] = 0;
	fr[x] = -1;	
	while(hd < tl){			
		int u = dl[++hd];
		for(int i = head[u];i;i = nex[i]){
			int v = to[i];
			if(fr[v] != 0 || vis[i])continue;
			fr[v] = i;
			if(v == V)break;
			dl[++tl] = v;
		}
	}

	for(int v = V;v != U; v = to[fr[v]^1]){
		zh[++tp] = v;
		vis[fr[v]] = vis[fr[v]^1] = 1;
	}
	zh[++tp] = U;
}
void get_V(){
	for(int u = fa[U];u;u = fa[u]){
		int cnt = 0;
		for(int i = head[u];i;i = nex[i]){
			int v = to[i];
			if(dfn[v] >= dfn[U] + (u == fa[U]) && dfn[v] <= dfn[U] + sz[U] - 1){
				cnt++;
			}
		}
		if(cnt >= 1){
			V = u;
			return ;
		}
	}
}
int main(){
	cin>>n>>m;
	int u, v;
	for(int i = 1;i <= m; i++){
		scanf("%d%d", &u, &v);
		add(u, v); add(v, u);
	}
	for(int i = 1;i <= n; i++){
		if(!dfn[i])
			dfs(i);
	}
	if(!U){
		puts("NO");
	}
	else{
		puts("YES");
		get_V();
		for(int i = 1;i <= 3; i++){
			bfs(U, i);
			printf("%d ", tp);
			while(tp){
				printf("%d ", zh[tp]);
				tp--;
			}
			puts("");
		}
	}
	return 0;
}
