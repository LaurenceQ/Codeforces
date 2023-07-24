#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define fs first
#define sc second
#define P pair<int, int>
#define mk_p make_pair
const int N = 1e6 + 11;
int n, m;
LL ans[N];
vector<P> Q1[N], Q2[N], Q[N];
struct bit{
    LL t[N];
    void add(int x, LL val){
        while(x <= m){
            t[x] += val;
            x += -x & x;
        }
    }
    LL query(int x){
        LL ans = 0;
        while(x){
            ans += t[x];
            x -= -x & x;
        }
        return ans;
    }
    LL query(int l, int r){
        return query(r) - query(l - 1);
    }
}T;
struct edge{
    int head[N], nex[N], to[N], size;
    bool vis[N];
    void add(int x, int y){
        to[++size] = y;
        nex[size] = head[x];
        head[x] = size;
    }
    void dfs2(int u){
        vis[u] = 1;
        for(int i = 0;i < Q2[u].size(); i++){
            P now = Q2[u][i];
            T.add(now.fs, now.sc);
        }
        if(u <= n){
            for(int i = 0;i < Q[u].size(); i++){
                P now = Q[u][i];
                int l = 1, r = now.fs, ans = r;
                while(r >= l){
                    int mid = l + r >> 1;
                    if(T.query(mid, now.fs) == 0)r = mid - 1, ans = mid;
                    else l = mid + 1;
                }
                Q[u][i].sc = ans;
            }
        }
        else{
            for(int i = head[u];i;i = nex[i]){
                int v = to[i];
                dfs2(v);
            }
        }
        for(int i = 0;i < Q2[u].size(); i++){
            P now = Q2[u][i];
            T.add(now.fs, -now.sc);
        }
    }
    void dfs1(int u){
        vis[u] = 1;
        for(int i = 0;i < Q1[u].size(); i++){
            P now = Q1[u][i];
            T.add(now.fs, now.sc);
        }
        if(u <= n){
            for(int i = 0;i < Q[u].size(); i++){
                P now = Q[u][i];
                ans[now.fs] = T.query(now.sc, now.fs);
            }
        }
        else {
            for(int i = head[u];i; i = nex[i]){
                dfs1(to[i]);
            }
        }
        for(int i = 0;i < Q1[u].size(); i++){
            P now = Q1[u][i];
            T.add(now.fs, -now.sc);
        }
    }
}G1, G2;
struct DSU{
    int fa[N], sz[N], tot;
    void init(){
        for(int i = 1;i <= n; i++){
            fa[++tot] = i;
            sz[tot] = 1;
        }
    }
    void merge(int u, int v, edge &G){
        int fu = find(u), fv = find(v);
        fa[fu] = fa[fv] = ++tot;
        fa[tot] = tot;
        sz[tot] = sz[fu] + sz[fv];
        G.add(tot, fu); G.add(tot, fv);
    }
    int find(int x){
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
}T1, T2;
int main(){
    cin>>n>>m;
    char s[5];
    int a, b, x;
    T1.init(); T2.init();
    for(int i = 1;i <= m; i++){
        scanf("%s", s);
        if(s[0] == 'U'){
            scanf("%d%d", &a, &b);
            T1.merge(a, b, G1);
        }
        if(s[0] == 'M'){
            scanf("%d%d", &a, &b);
            T2.merge(a, b, G2);
        }
        if(s[0] == 'A'){
            scanf("%d", &x);
            int fx = T1.find(x);
            Q1[fx].push_back(mk_p(i, T1.sz[fx]));
        }
        if(s[0] == 'Z'){
            scanf("%d", &x);
            int fx = T2.find(x);
            Q2[fx].push_back(mk_p(i, 1));
        }
        if(s[0] == 'Q'){
            scanf("%d", &x);
            Q[x].push_back(mk_p(i, 0));
        }
    }
    for(int i = 1;i <= n; i++){
        int fx = T2.find(i);
        if(!G2.vis[fx])G2.dfs2(fx);
    }
    memset(ans, -1, sizeof(ans));
    for(int i = 1;i <= n; i++){
        int fx = T1.find(i);
        if(!G1.vis[fx])G1.dfs1(fx);
    }
    for(int i = 1;i <= m; i++){
        if(ans[i] == -1)continue;
        printf("%lld\n", ans[i]);
    }
    return 0;
}