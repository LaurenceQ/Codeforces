#include<bits/stdc++.h>
using namespace std;
#define ls (p << 1)
#define rs (p << 1 | 1)
const int N = 5e5 + 11;
int n, m, K, q, tp;
int lst[N], nxt[N];
vector<int> t[N<<2];
struct edge{
	int u, v;
	edge(int _u = 0, int _v = 0){
		u = _u; v = _v;
	}
}e[N];
struct modi{
	int id, c; 
	modi(int _id = 0, int _c = 0){
		id = _id; c = _c; 
	}
}Q[N], zh[N<<1];
struct sett{
	int fa[N<<1], sz[N<<1];
	int c;
	int find(int x){
		return x == fa[x] ? x : find(fa[x]);
	}
	void merge(int x, int y){
		int fx = find(x), fy = find(y);
		if(fx == fy)return ;
		if(sz[fx] < sz[fy])swap(fx, fy);
		fa[fy] = fx;
		sz[fx] += sz[fy];
		zh[++tp] = modi(fy, c);
	}
	void init(int _c){
		for(int i = 1;i <= n + n; i++)fa[i] = i, sz[i] = 1;
		c = _c;
	}
	void del(int u){
		sz[fa[u]] -= sz[u];
		fa[u] = u;
		
	}
}G[51];
int read(){
	int x = 0;
	char ch = getchar();
	while(ch > '9' || ch < '0')ch = getchar();
	while(ch >= '0' && ch <= '9')x = 10 * x + ch - 48, ch = getchar();
	return x;
}
void insert(int p, int l, int r, int x, int y, int id){
	if(l > y || r < x || l > r)return ;
	if(l >= x && r <= y){
		t[p].push_back(id);
		return ;
	}
	int mid = l + r >> 1;
	insert(ls, l, mid, x, y, id);
	insert(rs, mid + 1, r, x, y, id);
}
void dfs(int p, int l, int r){

	int s = t[p].size(), X = tp;
	for(int i = 0;i < s; i++){
		int cur = t[p][i], id = Q[cur].id, c = Q[cur].c;
		int u = e[id].u, v = e[id].v;
		G[c].merge(u, v + n); 
		G[c].merge(v, u + n);
		
	}	
	if(l == r){
		int id = Q[l].id, c = Q[l].c;
		int u = e[id].u, v = e[id].v;
//		printf("l=%d nxt=%d u+n=%d v=%d v+n=%d u=%d\n", l, nxt[l], G[c].find(u + n), G[c].find(v), G[c].find(v + n), G[c].find(u));
		if(G[c].find(u) == G[c].find(v) || G[c].find(v + n) == G[c].find(u + n)){
			if(lst[id]){
				Q[l].c = Q[lst[id]].c;
				insert(1, 1, q, l + 1, nxt[l], l);
			}
			puts("NO");
		}
		else{
			lst[id] = l;
			puts("YES");
			insert(1, 1, q, l + 1, nxt[l], l);
		}
		
	}
	if(l != r){
		int mid = l + r >> 1;
		dfs(ls, l, mid); dfs(rs, mid + 1, r);
	}
	while(tp > X){
		int u = zh[tp].id, c = zh[tp].c;
		G[c].del(u);
		tp--;
	}
}
int main(){
	n = read(); m = read(); K = read(); q = read();
	for(int i = 1;i <= K; i++)G[i].init(i);
	int u, v;
	for(int i = 1;i <= m; i++){
		u = read(); v = read();
		e[i] = edge(u, v);
	}
	int id, c;
	for(int i = 1;i <= q; i++){
		id = read(); c = read();
		Q[i] = modi(id, c);
		if(lst[id]){
			nxt[lst[id]] = i - 1;
		}
		lst[id] = i;
	}
	for(int i = 1;i <= m; i++){
		if(lst[i]){
			nxt[lst[i]] = q;
			lst[i] = 0;
		}
	}
	dfs(1, 1, q);
	return 0;
}
