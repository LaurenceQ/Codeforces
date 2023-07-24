#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 2e5 + 11;
int n, m, R, B;
int bx[N], by[N];
int totx, toty;
int upx[N], upy[N], lowx[N], lowy[N];
int S = 200000 + 1, T = 200000 + 2, s = 200000 + 3, t = 200000 + 4;
int du[N];
int head[N], nex[N*6], to[N*6], wei[N*6], size = 1;
int dis[N], dl[N], cur[N];
int Sx[N], Sy[N];
struct node{
	int x, y;
}sd[N];
void add(int x, int y, int z){
	to[++size] = y; nex[size] = head[x]; head[x] = size; wei[size] = z;
	to[++size] = x; nex[size] = head[y]; head[y] = size; wei[size] = 0;
}
bool bfs(int s, int t){
	int hd = 0, tl = 1;
	dl[1] = s;
	memset(dis, -1, sizeof(dis));
	dis[s] = 0;
	while(hd < tl){
		int u = dl[++hd];
		for(int i = head[u];i;i = nex[i]){
			int v = to[i];
			if(dis[v] != -1 || wei[i] <= 0)continue;
			dis[v] = dis[u] + 1;
			dl[++tl] = v;
		}
	}
	return dis[t] != -1;
}
int dfs(int u, int w, int t){
	if(u == t || w == 0)return w;
	int s = 0;
	for(int &i = cur[u];i;i = nex[i]){
		int v = to[i];
		if(wei[i] <= 0 || dis[v] != dis[u] + 1)continue;
		int add = dfs(v, min(w, wei[i]), t);
		if(add > 0){
			s += add;
			wei[i] -= add;
			wei[i^1] += add;
			w -= add;
			if(!w)break;
		}
	}
	return s;
}
int dinic(int s, int t){
	int ans = 0;
	while(bfs(s, t)){
		memcpy(cur, head, sizeof(head));
		int add;
		do{
			add = dfs(s, 1e9, t);
			ans += add * (add > 0);
		}while(add > 0);
	}
	return ans;
}
int main(){
	cin>>n>>m>>R>>B;
	bool fl = 0;
	if(R < B)swap(R, B), fl = 1;
	int x,  y;
	for(int i = 1;i <= n; i++){
		scanf("%d%d", &x, &y);
		sd[i].x = x, sd[i].y = y;
		bx[++totx] = x;
		by[++toty] = y;
	}
	sort(bx + 1, bx + 1 + totx);
	sort(by + 1, by + 1 + toty);
	totx = unique(bx + 1, bx + 1 + totx) - (bx + 1);
	toty = unique(by + 1, by + 1 + toty) - (by + 1);
	for(int i = 1;i <= n; i++){
		sd[i].x = lower_bound(bx + 1, bx + 1 + totx, sd[i].x) - bx;
		sd[i].y = lower_bound(by + 1, by + 1 + toty, sd[i].y) - by;
		Sx[sd[i].x]++; Sy[sd[i].y]++;
		add(sd[i].x, sd[i].y + totx, 1);
	}
	for(int i = 1;i <= totx; i++)upx[i] = Sx[i];
	for(int i = 1;i <= toty; i++)upy[i] = Sy[i];
	int typ, l, d;
	for(int i = 1;i <= m; i++){
		scanf("%d%d%d", &typ, &l, &d);
		if(typ == 1){
			x = lower_bound(bx + 1, bx + 1 + totx, l) - bx;
			if(bx[x] != l)continue;
			lowx[x] = max(lowx[x], (Sx[x] - d + 1) / 2);
			upx[x] = min(upx[x], (Sx[x] + d) / 2);
			if(lowx[x] > upx[x]){
				puts("-1");
				return 0;
			}
		}
		if(typ == 2){
			y = lower_bound(by + 1, by + 1 + toty, l) - by;
			if(by[y] != l)continue;
			lowy[y] = max(lowy[y], (Sy[y] - d + 1) / 2);
			upy[y] = min(upy[y], (Sy[y] + d) / 2);
			if(lowy[y] > upy[y]){
				puts("-1");
				return 0;
			}
		}
	}
	for(int i = 1;i <= totx; i++){
		add(S, i, upx[i] - lowx[i]);
		du[S] -= lowx[i];
		du[i] += lowx[i];
	}
	for(int i = 1;i <= toty; i++){
		add(i + totx, T, upy[i] - lowy[i]);
		du[i+totx] -= lowy[i];
		du[T] += lowy[i];
	}
	int s0 = 0;
	for(int i = 1;i <= T; i++){
		if(!du[i])continue;
		if(du[i] < 0)add(i, t, -du[i]);
		if(du[i] > 0)add(s, i, du[i]), s0 += du[i];
	}
	add(T, S, 1e9);
	int tim = dinic(s, t);
	if(tim != s0){
		puts("-1");
		return 0;
	}
	tim = dinic(S, T);
	LL ans = 1LL * R * n - 1LL * tim * (R - B);
	printf("%lld\n", ans);
	for(int i = 1;i <= n; i++){
		if(wei[i*2] == 0){
			printf("%c", fl == 1 ? 'r' : 'b');
		}
		else printf("%c", fl == 1 ? 'b' : 'r');
	}
	puts("");
	return 0;
}
