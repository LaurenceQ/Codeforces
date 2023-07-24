#include<bits/stdc++.h>
using namespace std;
const int N = 111;
const int M = 1e3 + 11;
int head[N], nex[M], to[M], wei[M], cst[M], size = 1;
int ans, S = 0, T = 100 + 1;
int n, m;
int from[N], dl[M], dis[N], du[N];
bool vis[N];
void add(int x, int y, int w, int c){
	to[++size] = y;
	nex[size] = head[x];
	wei[size] = w;
	cst[size] = c;
	head[x] = size;
	to[++size] = x;
	nex[size] = head[y];
	head[y] = size;
	wei[size] = 0;
	cst[size] = -c;
}
void spfa(){
	int hd = 0, tl = 1;
	dl[1] = S;
	vis[S] = 1;	
	memset(dis, 127, sizeof dis);
	dis[S] = 0;
	while(hd < tl){
		int u = dl[++hd];
		for(int i = head[u];i;i = nex[i]){
			int v = to[i];
			if(wei[i] <= 0)continue;
			if(cst[i] + dis[u] < dis[v]){
				dis[v] = dis[u] + cst[i];
				from[v] = i;
				if(!vis[v])dl[++tl] = v, vis[v] = 1;
			}
		}
		vis[u] = 0;
	}
}
void MCMF(){
	while(1){
		spfa();
		int flow = 2e9, sum = 0;
		int now = T, i;
		while(now != S){
			i = from[now];
			flow = min(wei[i], flow);
			sum += cst[i];
			now = to[i^1];
		}
		ans += sum * flow;
		now = T;
		while(now != S){
			i = from[now];
			wei[i] -= flow;
			wei[i^1] += flow;
			now = to[i^1];
		}
		if(!flow)return ;
	}
}
int main(){
	cin>>n>>m;;
	int u, v, f, c;
	for(int i = 1;i <= m; i++){
		cin>>u>>v>>c>>f;
		if(f > c){
			ans += f - c;
			add(v, u, f - c, 0);
			add(v, u, c, 1);
		}
		else {
			add(u, v, c - f, 1);
			add(v, u, f, 1);
		}
		add(u, v, 1e9, 2);
		du[v] += f; du[u] -= f;
	}
	for(int i = 1;i <= n; i++){
		if(du[i] >= 0) add(S, i, du[i], 0);
		else add(i, T, -du[i], 0);
	}
	add(n, 1, 1e9, 0);
	MCMF();
	cout<<ans<<endl;
	return 0;
}
