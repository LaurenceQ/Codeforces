#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 2e3 + 11;
const int M = 1e5 + 11;
#define P pair<LL, int>
#define sc second
#define mk_p make_pair
int n, m;
int a[N], b[N];
int cnta[N][N], cntb[N][N], pa[N], pb[N];
LL dis[N], f[N][N][2];
LL Sb[N][N], Sa[N][N];
LL mi[N], ma[N];
int head[N], nex[M<<1], to[M<<1], size;
LL wei[M<<1], val[N];
bool vis[N];
priority_queue<P, vector<P>, greater<P> > q;
void add(int x, int y, LL w){
	to[++size] = y;
	nex[size] = head[x];
	wei[size] = w;
	head[x] = size;
}
void dij(int st, int *x){
	q.push(mk_p(0, st));
	memset(vis, 0, sizeof(vis));
	memset(dis, 127, sizeof(dis));
	dis[st] = 0;
	int tot = 0;
	while(q.size()){
		int u = q.top().sc;
		q.pop();
		if(vis[u])continue;
		x[++tot] = u;
		vis[u] = 1;
		for(int i = head[u];i;i = nex[i]){
			int v = to[i];
			if(dis[v] > dis[u] + wei[i]){
				dis[v] = dis[u] + wei[i];
				q.push(mk_p(dis[v], v));
			}
		}
	}
}
int main(){
	cin>>n>>m;
	int s, t;
	LL sum = 0;
	cin>>s>>t;
	for(int i = 1;i <= n; i++){
		scanf("%lld", &val[i]);
		sum += val[i];
	}
	int u, v, w;
	for(int i = 1;i <= m; i++){
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w); add(v, u, w);
	}
	dij(s, a); dij(t, b);
	for(int i = 1;i <= n; i++){
		pa[a[i]] = i; pb[b[i]] = i;
		//printf("i=%d pa=%d pb=%d\n", i, a[i], b[i]);
	}
	for(int i = 0;i <= n; i++){
		for(int j = 0;j <= n; j++){
			if(i)Sa[i][j] = Sa[i-1][j], cnta[i][j] = cnta[i-1][j];
			if(i)Sb[i][j] = Sb[i-1][j], cntb[i][j] = cntb[i-1][j];
			if(i && pb[a[i]] > j)Sa[i][j] += val[a[i]], cnta[i][j]++;
			if(i && pa[b[i]] > j)Sb[i][j] += val[b[i]], cntb[i][j]++;
		}
	}
	for(int i = 1;i <= n + 1; i++)pa[i] = pb[i] = n + 1, ma[i] = -1e13, mi[i] = 1e13;
	for(int i = n + 1;i >= 1; i--){
		for(int j = n + 1;j >= 1; j--){
			while(cnta[pa[j]-1][j-1] > cnta[i-1][j-1])pa[j]--, ma[j] = max(ma[j], f[pa[j]+1][j][1] + Sa[pa[j]][j-1]);//, printf("i=%d pa=%d ma=%d\n", i, pa[j], ma[j]);
			f[i][j][0] = ma[j] == -1e13 ? 0 : ma[j] - Sa[i-1][j-1];
			while(cntb[pb[i]-1][i-1] > cntb[j-1][i-1])pb[i]--, mi[i] = min(mi[i], f[i][pb[i]+1][0]);
			f[i][j][1] = mi[i] == 1e13 ? 0 : mi[i];
			//printf("i=%d j=%d f0=%lld f1=%lld pa=%d pb=%d\n", i, j, f[i][j][0], f[i][j][1], pa[j], pb[i]);
		}
	}
	if(f[1][1][0] > sum - f[1][1][0])puts("Break a heart");
	else if(f[1][1][0] == sum - f[1][1][0])puts("Flowers");
	else puts("Cry");
	return 0;
}
