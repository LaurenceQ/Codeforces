#include<bits/stdc++.h>
using namespace std;
const int N = 155;
int n, m, dl[N], dis[N];
struct edge{
	int u, v, t;
	edge(int _u = 0, int _v = 0, int _t = 0){
		u = _u; v = _v; t = _t;
	}
}e[N];
struct mat{
	bitset<N> a[N];
	mat operator * (mat b){
		mat ans;
		for(int i = 1;i <= n; i++){
			ans.a[i].reset();
			for(int j = 1;j <= n; j++){
				if(a[i][j])ans.a[i] |= b.a[j];
			}
		}
		return ans;
	}
}f, b, tmp;
ksm(mat &ans, mat &base, int x){
	while(x){
		if(x & 1)ans = ans * base;
		base = base * base;
		x >>= 1;
	}
}
bool cmp(edge x, edge y){
	return x.t < y.t;
}
int main(){
	cin>>n>>m;
	int u, v, t;
	for(int i = 1;i <= m; i++){
		scanf("%d%d%d", &u, &v, &t);
		e[i] = edge(u, v, t);
	}
	sort(e + 1, e + 1 + m, cmp);
	int ans = 2e9;
	for(int i = 1;i <= n; i++)f.a[i][i] = 1;
	for(int i = 1;i <= m; i++){
		u = e[i].u; v = e[i].v;
		tmp = b;
		ksm(f, tmp, e[i].t - e[i-1].t);
		b.a[u][v] = 1;
		int hd = 0, tl = 0;
		for(int j = 1;j <= n; j++){
			if(f.a[1][j])dl[++tl] = j, dis[j] = e[i].t;
			else dis[j] = -1;
		}
		while(hd < tl){
			int u = dl[++hd];
			for(int j = 1;j <= n; j++){
				if(dis[j] != -1 || !b.a[u][j])continue;
				dis[j] = dis[u] + 1;
				dl[++tl] = j;
			}
		}
		if(dis[n] != -1)ans = min(ans, dis[n]);
	}
	if(ans != 2e9)cout<<ans<<endl;
	else puts("Impossible");
	return 0;
}
