#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 3e4 + 11;
const int inf = 1e9;
int head[N], to[N], nex[N], size = 1;
int dl[N], fr[N];
int n, S = 3000, T = 3001;
LL dis[N], wei[N], cst[N], ans;
bool mark[N];
void add(int x, int y, int z, int k){
	to[++size] = y; nex[size] = head[x]; head[x] = size; cst[size] = k; wei[size] = z;
	to[++size] = x; nex[size] = head[y]; head[y] = size; cst[size] = -k; wei[size] = 0;
}
void spfa(){
	int hd = 0, tl = 1;
	dl[1] = S;
	for(int i = 1;i <= T; i++)dis[i] = -1e18;
	dis[S] = 0; mark[S] = 1;
	while(hd < tl){
		int u = dl[++hd];
		for(int i = head[u];i;i = nex[i]){
			if(wei[i] <= 0)continue;
			int v = to[i];
			if(dis[v] < dis[u] + cst[i]){
				dis[v] = dis[u] + cst[i];
				fr[v] = i;
				if(!mark[v])dl[++tl] = v, mark[v] = 1;
			}
		}
		mark[u] = 0;
	}
}
void MCMF(){
	while(1){
		spfa();
		LL ma = dis[T]; 
		if(ma == -1e18)return ;
		LL flow = 1e9;		
//		printf("ma=%lld ans=%lld\n", ma, ans);
		for(int u = T;u != S;u = to[fr[u]^1])flow = min(flow, wei[fr[u]]);
		ans += flow * ma;
		for(int u = T;u != S;u = to[fr[u]^1])wei[fr[u]] -= flow, wei[fr[u]^1] += flow;
	}
}
int main(){
	cin>>n;
	int x, y, w;
	for(int i = 1;i <= n; i++){
		scanf("%d%d%d", &x, &y, &w);
		add(S, i, w, 0);
		add(i, 2 * n + 1, inf, x + y);
		add(i, 2 * n + 2, inf, x - y);
		add(i, 2 * n + 3, inf, -x + y);
		add(i, 2 * n + 4, inf, -x - y);
	}
	for(int i = 1;i <= n; i++){
		scanf("%d%d%d", &x, &y, &w);
		add(i + n, T, w, 0);
		add(2 * n + 1, i + n, inf, -x - y);
		add(2 * n + 2, i + n, inf, -x + y);
		add(2 * n + 3, i + n, inf, x - y);
		add(2 * n + 4, i + n, inf, x + y);
	}
	MCMF();
	printf("%lld\n", ans);
	return 0;
}
