#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 11;
int n, m;
int head[N], to[N<<1], nex[N<<1], size = 1;
int tot, cnt, col[N], low[N], dfn[N], zh[N], tp;
int f[N][22], dep[N], cha1[N], cha2[N];
vector<int> G[N];
bool vis[N];
void add(int x, int y){
    to[++size] = y;
    nex[size] = head[x];
    head[x] = size;
}
void tarjan(int u, int lst){
    vis[u] = 1;
    low[u] = dfn[u] = ++cnt;
    zh[++tp] = u;
    for(int i = head[u];i;i = nex[i]){
        if(i == lst || i == (lst ^ 1))continue;
        int v = to[i];
        if(vis[v]){
            low[u] = min(low[u], dfn[v]);
        }
        else{
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
        }
    }
    if(low[u] == dfn[u]){
        tot++;
        col[u] = tot;
        while(zh[tp] != u){
            col[zh[tp--]] = tot;
        }
        tp--;
    }
}
void dfs0(int u, int fa){
    vis[u] = 1;
    dep[u] = dep[fa] + 1;
    for(int i = 1;i <= 20; i++){
        f[u][i] = f[f[u][i-1]][i-1];
    }
    for(int v : G[u]){
        if(vis[v])continue;
        f[v][0] = u;
        dfs0(v, u);
    }
}
int LCA(int u, int v){
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 19;i >= 0; i--){
        if(dep[f[u][i]] >= dep[v])u = f[u][i];
    }
    if(u == v)return u;
    for(int i = 19;i >= 0; i--){
        if(f[u][i] != f[v][i]){
            u = f[u][i]; v = f[v][i];
        }
    }
    return f[u][0];
}
void dfs(int u, int fa){
    vis[u] = 1;
    for(int v : G[u]){
        if(v == fa)continue;
        dfs(v, u);
        cha1[u] += cha1[v];
        cha2[u] += cha2[v];
    }
}
int main(){
    int q;
    cin>>n>>m>>q;
    int u, v;
    for(int i = 1;i <= m; i++){
        scanf("%d%d", &u, &v);
        add(u, v); add(v, u); 
    }
    for(int i = 1;i <= n; i++){
        if(!vis[i]){
            tarjan(i, 0);
        }
    }
    for(int u = 1;u <= n; u++){
        for(int i = head[u];i;i = nex[i]){
            int v = to[i];
            if(col[u] == col[v])continue;
            G[col[u]].push_back(col[v]);
        }
    }
    memset(vis, 0, sizeof(vis));
    for(int i = 1;i <= n; i++){
        if(vis[i])continue;
        dfs0(i, i);
    }
    while(q--){
        scanf("%d%d", &u, &v);
        if(col[u] == col[v])continue;
        u = col[u]; v = col[v];
        int lca = LCA(u, v);
        if(!lca){
            puts("No");
            return 0;
        }
        cha1[u]++; cha2[v]++;
        cha1[lca]--; cha2[lca]--;
    }
    memset(vis, 0, sizeof(vis));
    for(int i = 1;i <= n; i++){
        if(!vis[i])dfs(i, i);
    }
    for(int i = 1;i <= tot; i++){
        if(cha1[i] >= 1 && cha2[i] >= 1){
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}