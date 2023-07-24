#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e5 + 11;
int n, m, q;
struct ddd{
    int st, ed;
}ln[N];
LL wei[N], ans;
int head[N], nex[N<<1], to[N<<1], size;
int cha[N], dep[N], f[22][N];
void add(int x, int y){
    nex[++size] = head[x];
    to[size] = y;
    head[x] = size;
}
void dfs(int u){
    dep[u] = dep[f[0][u]] + 1;
    for(int i = 1;i <= 20; i++){
        f[i][u] = f[i-1][f[i-1][u]];
    }
    for(int i = head[u];i ; i = nex[i]){
        int v = to[i];
        if(v == f[0][u])continue;
        f[0][v] = u;
        dfs(v);
    }
}
int LCA(int x, int y){
    if(dep[x] < dep[y])swap(x, y);
    for(int i = 20;i >= 0; i--){
        if(dep[f[i][x]] >= dep[y])x = f[i][x];
    }
    if(x == y)return x;
    for(int i = 20;i >= 0; i--){
        if(f[i][x] != f[i][y])x = f[i][x], y = f[i][y];
    }
    return f[0][x];
}
void dfs0(int u){
    for(int i = head[u];i;i = nex[i]){
        int v = to[i];
        if(v == f[0][u])continue;
        dfs0(v);
        cha[u] += cha[v];
    }
    if(cha[u])ans += wei[u];
}
int main(){
    freopen("star.in", "r", stdin);
    freopen("star.out", "w", stdout);
    cin>>n>>m>>q;
    for(int i = 1;i <= n; i++){
        scanf("%lld", &wei[i]);
    }
    int u, v;
    for(int i = 1;i < n; i++){
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for(int i = 1;i <= m; i++){
        scanf("%d%d", &ln[i].st, &ln[i].ed);
    }
    int l, r;
    dfs(1);
    while(q--){
        scanf("%d%d", &l, &r);
        memset(cha, 0, sizeof(cha));
        for(int i = l;i <= r; i++){
            cha[ln[i].st]++; cha[ln[i].ed]++;
            cha[f[0][LCA(ln[i].st, ln[i].ed)]] -= 2;
        }
        ans = 0;
        dfs0(1);
        printf("%lld\n", ans);
    }
    return 0;
}
