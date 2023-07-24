#include<bits/stdc++.h>
using namespace std;
#define cp(x) (x > n ? x - n : x + n)
const int N = 211;
const int M = 160010;
int n, m;
int head[N<<1], to[M<<1], nex[M<<1], size;
int vis[N<<1];
int bl[33], len, lst[33][2];
char aph[33], s[N], ans[N];
bool dfs(int u){
	if(vis[cp(u)] == 1)return 0;
	if(vis[u] == 1)return 1;
	vis[u] = 1; vis[cp(u)] = 0;
	for(int i = head[u];i;i = nex[i]){
		int v = to[i];
		if(!dfs(v)){
			vis[u] = -1; vis[cp(u)] = -1;
			return 0;
		}
	}
	return 1;
}
bool check(int p){
	memset(vis, -1, sizeof(vis));
	for(int i = 1;i <= p; i++){
		int u = i + bl[s[i]-'a'+1] * n;
		if(!dfs(u))return 0;
	}
	int mi = min(lst[1][0], lst[1][1]), ma = max(lst[1][0], lst[1][1]);
//	printf("ma=%c ==%d\n", ma + '/a' - 1, ma == len + 1);
	for(int i = p + 1;i <= n; i++){
		if(vis[i] != -1){
			if(vis[i] == 1 && lst[1][0] != len + 1) s[i] = lst[1][0] + 'a' - 1;
			else if(vis[i+n] == 1 && lst[1][1] != len + 1) s[i] = lst[1][1] + 'a' - 1;
			else return 0;
		}	
		else{
			if(dfs(i + bl[mi] * n)){
				s[i] = mi + 'a' - 1;
			}
			else if(ma == len + 1)return 0;
			else if(!dfs(i + bl[ma] * n)){
				puts("-1");
				exit(0);
			}
		}
	}
	return 1;
}
void add(int x, int y){
	to[++size] = y;
	nex[size] = head[x];
	head[x] = size;
}
int main(){
	cin>>aph + 1;
	len = strlen(aph + 1);
	lst[len+1][0] = lst[len+1][1] = len + 1;
	for(int i = len;i >= 1; i--){
		if(aph[i] == 'V')bl[i] = 0;
		else bl[i] = 1;
		lst[i][bl[i]] = i; 
		lst[i][bl[i]^1] = lst[i+1][bl[i]^1];
	}
	cin>>n>>m;
	int pos1, pos2;
	char t1[5], t2[5];
	for(int i = 1;i <= m; i++){
		scanf("%d%s%d%s", &pos1, t1, &pos2, t2);
		if(t1[0] == 'C')pos1 += n;
		if(t2[0] == 'C')pos2 += n;
		add(pos1, pos2);
		add(cp(pos2), cp(pos1));
	}
	cin>> s + 1;
	if(check(n)){
		puts(s + 1);
		return 0;
	}
	for(int i = n;i >= 1; i--){
		if(s[i] - 'a' + 1 == len)continue;
		int now = s[i] - 'a' + 1, mi = min(lst[now+1][0], lst[now+1][1]), ma = max(lst[now+1][0], lst[now+1][1]);
		s[i] = mi + 'a' - 1;
		if(check(i)){
			puts(s + 1);
			return 0;
		}
		if(ma <= len){
			s[i] = ma + 'a' - 1;
			if(check(i)){
				puts(s + 1);
				return 0;
			}
		}
	}
	puts("-1");
	return 0;
}
