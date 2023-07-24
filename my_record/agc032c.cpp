#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 11;
int n, m;
int tong[N], du[N];
int head[N], to[N<<1], nex[N<<1], size = 1;
bool vis[N<<1], flag, ins[N];
void add(int x, int y){
	to[++size] = y;
	nex[size] = head[x];
	head[x] = size;
	du[y]++;
}
void dfs(int u, int st, int fl){
	if(u != st && du[u] == 4)fl = 1;
	for(int i = head[u];i;i = nex[i]){
		if(vis[i])continue;
		vis[i] = vis[i^1] = 1;
		int v = to[i];
		if(v == st && fl == 0)flag = 1; 
		if(v != st)dfs(v, st, fl);
	}
}
int main(){
	cin>>n>>m;
	int u, v;
	for(int i = 1;i <= m; i++){
		scanf("%d%d", &u, &v);
		add(u, v); add(v, u);
	}
	int ma = 0;
	for(int i = 1;i <= n; i++){
		tong[du[i]]++;
		ma = max(ma, du[i]);
		if(du[i] & 1){
			puts("No");
			return 0;
		}
	}
	if(ma >= 6){
		puts("Yes");
		return 0;
	}
	if(tong[4] >= 3){
		puts("Yes");
		return 0;
	}
	if(tong[4] == 1){
		puts("No");
		return 0;
	}
	if(tong[4] == 2){
		for(int i = 1;i <= n; i++){
			if(du[i] == 4){
				dfs(i, i, 0);
			}
		}
		puts(flag ? "Yes" : "No");
		return 0;
	}
	puts("No");
	return 0;
}
