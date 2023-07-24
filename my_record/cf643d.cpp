#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 11;
#define LL long long
int n, q;
int fa[N], du[N];
LL t[N], tag[N], res[N], sum[N];
multiset<LL> son[N], ans;
vector<int> G[N];
void del(int x, int y){
	int z = fa[y], k = fa[z];
	ans.erase(ans.find(*son[k].begin() + tag[k]));
	ans.erase(ans.find(*(--son[k].end()) + tag[k]));
	ans.erase(ans.find(*son[z].begin() + tag[z]));
	ans.erase(ans.find(*(--son[z].end()) + tag[z]));
	ans.erase(ans.find(*son[y].begin() + tag[y]));
	ans.erase(ans.find(*(--son[y].end()) + tag[y]));
	son[k].erase(son[k].find(sum[z] + res[z]));
	son[z].erase(son[z].find(sum[y] + res[y]));	
	son[y].erase(son[y].find(sum[x] + res[x]));	
	sum[z] -= tag[y];
	du[y]--; sum[y] -= tag[x];
	tag[y] = t[y] / (du[y] + 1);
	res[y] = t[y] - tag[y] * du[y];
	sum[z] += tag[y];
	son[z].insert(sum[y] + res[y]);
	son[k].insert(sum[z] + res[z]);
	if(son[y].size())ans.insert(*son[y].begin() + tag[y]), ans.insert(*(--son[y].end()) + tag[y]);
	ans.insert(*son[z].begin() + tag[z]);
	ans.insert(*(--son[z].end()) + tag[z]);
	ans.insert(*son[k].begin() + tag[k]);
	ans.insert(*(--son[k].end()) + tag[k]);
}
void add(int x, int y){
	fa[x] = y;
	int z = fa[y], k = fa[z];
	ans.erase(ans.find(*son[k].begin() + tag[k]));
	ans.erase(ans.find(*(--son[k].end()) + tag[k]));
	ans.erase(ans.find(*son[z].begin() + tag[z]));
	ans.erase(ans.find(*(--son[z].end()) + tag[z]));
	if(son[y].size())ans.erase(ans.find(*son[y].begin() + tag[y])), ans.erase(ans.find(*(--son[y].end()) + tag[y]));
	son[k].erase(son[k].find(sum[z] + res[z]));
	son[z].erase(son[z].find(sum[y] + res[y]));	
	sum[z] -= tag[y];
	du[y]++; sum[y] += tag[x];
	tag[y] = t[y] / (du[y] + 1);
	res[y] = t[y] - tag[y] * du[y];
	sum[z] += tag[y];
	son[y].insert(sum[x] + res[x]);
	son[z].insert(sum[y] + res[y]);
	son[k].insert(sum[z] + res[z]);
	ans.insert(*son[y].begin() + tag[y]);
	ans.insert(*(--son[y].end()) + tag[y]);
	ans.insert(*son[z].begin() + tag[z]);
	ans.insert(*(--son[z].end()) + tag[z]);
	ans.insert(*son[k].begin() + tag[k]);
	ans.insert(*(--son[k].end()) + tag[k]);
}
int main(){
	cin>>n>>q;
	for(int i = 1;i <= n; i++){
		scanf("%lld", &t[i]);
	}
	for(int i = 1;i <= n; i++){
		scanf("%d", &fa[i]);
		du[i]++; du[fa[i]]++;
		G[fa[i]].push_back(i);
	}
	for(int i = 1;i <= n; i++){
		res[i] = t[i] - t[i] / (du[i] + 1) * du[i];
		tag[i] = t[i] / (du[i] + 1);
	}
	for(int i = 1;i <= n; i++){
		sum[i] = 0;
		for(vector<int>::iterator v = G[i].begin();v != G[i].end(); v++){
			sum[i] += tag[*v];
		}
		son[fa[i]].insert(sum[i] + res[i]);
	}
	for(int i = 1;i <= n; i++)if(son[i].size())ans.insert(*son[i].begin() + tag[i]), ans.insert(*(--son[i].end()) + tag[i]);
	int fl, x, y, cnt = 1;
	while(q--){
		scanf("%d", &fl);
		if(fl == 1){
			scanf("%d%d", &x, &y);
			del(x, fa[x]);
			add(x, y);
		}
		if(fl == 2) scanf("%d", &x), printf("%lld\n", sum[x] + tag[fa[x]] + res[x]);
		if(fl == 3) printf("%lld %lld\n", *ans.begin(), *(--ans.end()));
	}
	return 0;
}
