#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define P pair<LL, LL>
#define fs first
#define sc second
const int N = 2e2 + 11;
int dep[N], du[N], maxdu[N], n;
vector<int> G[N];
queue<int> dl;
LL bfs(int u, int v){
	memset(dep, 0, sizeof dep);
	memset(maxdu, 0, sizeof(maxdu));
	dep[u] = 1; dl.push(u);
	if(v)dep[v] = 1, dl.push(v);
	int ma = 0;
	while(dl.size()){
		int x = dl.front(); dl.pop();
		ma = max(ma, dep[x]);
		maxdu[dep[x]] = max(maxdu[dep[x]], du[x]);
		for(int y : G[x]){
			if(dep[y] != 0)continue;
			dep[y] = dep[x] + 1;
			dl.push(y);
		}
	}
	return ma;
}
P get(int u, int v){
	P ans;
	ans.fs = bfs(u, v);
	ans.sc = maxdu[1] - (v != 0);
//	printf("madu1=%d ans.sc=%lld\n", maxdu[1] - (v != 0), ans.sc);
	for(int i = 2;i <= n; i++){
		if(maxdu[i] <= 1)break;
		ans.sc *= maxdu[i] - 1;
	}
	if(v != 0)ans.sc *= 2;
//	printf("u=%d v=%d fs=%lld sc=%lld\n", u, v, ans.fs, ans.sc);
	return ans;
}
int main(){
	cin>>n;
	if(n == 2){
		puts("1 2");
		return 0;
	}
	int u, v;
	for(int i = 1;i < n; i++){
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
		du[u]++; du[v]++;
	}
	P ans = P(1e18, 1e18);
//	printf("ans.fs=%lld ans.sc=%lld\n", ans.fs, ans.sc);
	for(int i = 1;i <= n; i++){
		ans = min(ans, get(i, 0));
		for(int v : G[i]){
			ans = min(ans, get(i, v));
		}
	}
	cout<<ans.fs<<" "<<ans.sc<<endl;
	return 0;
}
