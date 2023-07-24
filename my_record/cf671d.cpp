#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 3e5 + 11;
const LL inf = 1e16;
int n, m, tot;
int head[N], to[N<<1], nex[N<<1], size;
int id[N], L[N], R[N];
LL c[N], f[N];
vector<int> st[N], ed[N];
struct seg{
#define ls (p << 1)
#define rs (p << 1 | 1)
	LL t[N<<2], tag[N<<2];
	void add_tag(int p, LL c){
		tag[p] += c;
		t[p] += c;
	}
	void push_down(int p){
		if(!tag[p])return ;
		add_tag(ls, tag[p]);
		add_tag(rs, tag[p]);
		tag[p] = 0;
 	}
	void build(int p, int l, int r){
		if(l == r){
			t[p] = 1e16;
			return ;
		}
		int mid = l + r >> 1;
		build(ls, l, mid); build(rs, mid + 1, r);
		t[p] = min(t[ls], t[rs]);
	}
	void modify(int p, int l, int r, int x, LL c){
		if(l > x || r < x)return ;
		if(l == r && l == x){
			t[p] = c;
			return ;
		}
		push_down(p);
		int mid = l + r >> 1;
		modify(ls, l, mid, x, c);
		modify(rs, mid + 1, r, x, c);
		t[p] = min(t[ls], t[rs]);
	}
	void add(int p, int l, int r, int x, int y, LL c){
		if(l > y || r < x)return ;
		if(l >= x && r <= y){
			add_tag(p, c);
			return ;
		}
		push_down(p);
		int mid = l + r >> 1;
		add(ls, l, mid, x, y, c);
		add(rs, mid + 1, r, x, y, c);
		t[p] = min(t[ls], t[rs]);
	}
	LL query(int p, int l, int r, int x, int y){
		if(l > y || r < x)return inf;
		if(l >= x && r <= y){
			return t[p];
		}
		push_down(p);
		int mid = l + r >> 1;
		return min(query(ls, l, mid, x, y), query(rs, mid + 1, r, x, y));
	}
#undef ls
#undef rs
}T;
void dfs(int u, int fa){
	L[u] = m + 1; 
	for(int i = 0;i < st[u].size(); i++){
		id[st[u][i]] = ++tot;
		L[u] = min(L[u], tot);
		R[u] = max(R[u], tot);
	}
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(v == fa)continue;
		dfs(v, u);
		L[u] = min(L[u], L[v]);
		R[u] = max(R[u], R[v]);
	}
	if(L[u] == m + 1 || !R[u]){
		puts("-1");
		exit(0);
	}
}
void dp(int u, int fa){
	LL sum = 0;
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(v == fa)continue;
		dp(v, u);
		sum += f[v];
	}
	for(int i = 0;i < st[u].size(); i++){
		int now = st[u][i];
		T.modify(1, 1, m, id[st[u][i]], c[st[u][i]]);
	}
	T.add(1, 1, m, L[u], R[u], sum);
	for(int i = 0;i < ed[u].size(); i++){
		int now = ed[u][i];
		T.modify(1, 1, m, id[now], 1e16);
	}
	if(u != 1)f[u] = T.query(1, 1, m, L[u], R[u]);
	else f[u] = sum;
	T.add(1, 1, m, L[u], R[u], -f[u]);
}
void add(int u, int v){
	to[++size] = v;
	nex[size] = head[u];
	head[u] = size;
}
int main(){
	cin>>n>>m;
	if(n == 1){
		puts("0");
		return 0;
	}
	int u, v;
	for(int i = 1;i < n; i++){
		scanf("%d%d", &u, &v);
		add(u, v); add(v, u);
	}
	for(int i = 1;i <= m; i++){
		scanf("%d%d%lld", &u, &v, &c[i]);
		if(u == v){
			i--, m--;
			continue;
		}
		st[u].push_back(i);
		ed[v].push_back(i);
	}
	dfs(1, 1);
	T.build(1, 1, m);
	dp(1, 1);
	if(f[1] < inf)printf("%lld\n", f[1]);
	else puts("-1");
	return 0;
}
