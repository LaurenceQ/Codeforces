#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 11;
int head[N], nex[N], to[N], size;
int lcol[N], col[N], cnt, dfn[N], low[N], tot;
int zh[N], tp;
int tmp[N], all;
int n, m, num;
bool ins[N];
struct edge{
	int u, v, c, w;
}e[N];
vector<int> G[N];
void add(int x, int y){
	to[++size] = y;
	nex[size] = head[x];
	head[x] = size;
}
void build(int x){
	num = 2 * m;
	size = 0;
	memset(head, 0, sizeof(head));
	
	for(int i = 1;i <= n; i++){
		int s = G[i].size();
		int lst1 = 0, lst2 = 0;
		for(int j = 0;j < s; j++){
			int id = G[i][j];
			edge now = e[id];
			if(now.w > x){
				add(id, id + m);
			}
			num += 2;
			add(id, num); add(num ^ 1, id + m);
			if(lst1){
				add(lst1, num), add(num ^ 1, lst1 ^ 1);
				add(id, lst1 ^ 1); add(lst1, id + m);
			}
			lst1 = num;
			num += 2;
			add(id + m, num ^ 1); add(num, id);
			if(lst2 && e[G[i][j-1]].c == now.c){
				add(lst2 ^ 1, num ^ 1), add(num, lst2);
				add(id + m, lst2); add(lst2 ^ 1, id);
			}
			lst2 = num;
		}
	}
}
void tarjan(int u){
	zh[++tp] = u;
	ins[u] = 1;
	low[u] = dfn[u] = ++tot;
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(ins[v])low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]){
		col[u] = ++cnt;
//		printf("u=%d cnt=%d\n", u, cnt);
		while(zh[tp] != u){
			ins[zh[tp]] = 0;
			col[zh[tp]] = cnt;
			tp--;
		}
		tp--;
		ins[u] = 0;
	}
}
bool check(int x){
	build(x);
	memset(dfn, 0, sizeof(dfn));
	memset(col, 0, sizeof(col));
	tot = cnt = 0;
	for(int i = 1;i <= num; i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i = 1;i <= m; i++){
		if(col[i] == col[i+m])return 0;
	}
	memcpy(lcol, col, sizeof(col));
	return 1;
}
bool cmp(int x, int y){
	return e[x].c < e[y].c;
}
int main(){
	cin>>n>>m;
	int u, v, w, c;
	for(int i = 1;i <= m; i++){
		scanf("%d%d%d%d", &u, &v, &c, &w);
		G[u].push_back(i);
		G[v].push_back(i);
		e[i] = (edge){u, v, c, w};
	}
	for(int i = 1;i <= n; i++)sort(G[i].begin(), G[i].end(), cmp);
	int l = 0, r = 1e9, ans = 1e9 + 1;
	while(l <= r){
		int mid = l + r >> 1;
		if(check(mid))r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	if(ans == 1e9 + 1){
		puts("No");
	}
	else{
		puts("Yes");
//		printf("num=%d cnt=%d\n", num, cnt);
		for(int i = 1;i <= m; i++){
			if(lcol[i] < lcol[i+m])tmp[++all] = i;
//			printf("i=%d coli=%d col!i=%d\n", i, lcol[i], lcol[i+m]);
		}
		printf("%d %d\n", ans, all);
		for(int i = 1;i <= all; i++){
			printf("%d ", tmp[i]);
		}
		puts("");
	}
	return 0;
}
