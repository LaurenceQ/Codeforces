#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 11;
const int Ma = 200000;
int head[N], nex[N<<1], to[N<<1], id[N<<1], size = 1;
int du[N], ans[N], n;
bool vis[N<<1];
void add(int x, int y, int z){
	to[++size] = y;
	nex[size] = head[x];
	head[x] = size;
	id[size] = z;
	du[x]++;
}
bool dfs(int u, int fl){
	for(int &i = head[u];i;i = nex[i]){
		if(vis[i] || vis[i^1])continue;
		int v = to[i];
		vis[i] = vis[i^1] = 1;
		du[u]--; du[v]--;
		ans[id[i]] = fl;
		if(!(du[v] & 1)){
			return 1;
		}
		if(dfs(v, fl ^ 1))return 1; 
	}
	return 0;
}
void dfs0(int u, int fl){
	for(int &i = head[u];i;i = nex[i]){
		if(vis[i] || vis[i^1])continue;
		int v = to[i];
		du[v]--; du[u]--;
		vis[i] = vis[i^1] = 1;
		ans[id[i]] = fl;
		dfs0(v, fl ^ 1);
	}
}
int main(){
	cin>>n;
	int x, y;
	for(int i = 1;i <= n; i++){
		scanf("%d%d", &x, &y);
		add(x, y + Ma, i);
		add(y + Ma, x, i);
	}
	for(int i = 1;i <= Ma + Ma; i++){
		if(du[i] & 1)dfs(i, 1);
	}
	for(int i = 1;i <= Ma + Ma; i++){
		if(du[i]) dfs0(i, 1);
	}
	for(int i = 1;i <= n; i++){
		printf(ans[i] ? "r" : "b");
	}
	puts("");
	return 0;
}
