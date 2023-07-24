#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 11;
const int M = 5e5 + 11;
int head[N], nex[M], to[M], size = 1;
int du[N];
int n, m, tot;
bool vis[M];
struct edge{
	int u, v;
	edge(int _u = 0, int _v = 0){
		u = _u; v = _v;
	}
}e[M];
void add(int x, int y){
	nex[++size] = head[x];
	to[size] = y;
	head[x] = size;
	du[y]++;
} 
void dfs(int u){
	for(int &i = head[u];i;i = nex[i]){
		if(vis[i] || vis[i^1])continue;
		int v = to[i];
		vis[i] = vis[i^1] = 1;
		dfs(v);
		e[++tot] = edge(u, v);
	}
}
int main(){
	cin>>n>>m;
	int u, v;
	for(int i = 1;i <= m; i++){
		scanf("%d%d", &u, &v);
		add(u, v); add(v, u);
	}
	int lst = 0;
	for(int i = 1;i <= n; i++){
		if(du[i] % 2 == 0)continue;
		if(lst)add(lst, i), add(i, lst), lst = 0;
		else lst = i;
	}
	dfs(1);
	if(tot & 1)e[++tot] = (edge){1, 1};
	printf("%d\n", tot);
	bool flag = 0;
	for(int i = 1;i <= tot; i++){
		if(!flag)printf("%d %d\n", e[i].u, e[i].v);
		else printf("%d %d\n", e[i].v, e[i].u);
		flag ^= 1;
	}
	return 0;
}
