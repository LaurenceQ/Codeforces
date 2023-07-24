#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define P pair<LL, LL>
#define mk make_pair
#define fs first
#define sc second
const int N = 3e5 + 11;
const LL modd[11] = {19260817, 381335473,  252412907, 173275057, 415924151, 490280677, 215695621, 311094167};
bool vis[11];
LL mod1, mod2;
int n, m;
int head[N], nex[N<<1], to[N<<1], size;
int dep[N], sz[N], dfn[N], son[N], id[N], fa[N], top[N], cnt;
char s[N];
P B = mk(127, 23333), h1[N], h2[N], p[N];
vector<P> up, dw, f, g;
P operator * (P a, P b){
    return mk(a.fs * b.fs % mod1, a.sc * b.sc % mod2);
}
P operator + (P a, P b){
    return mk((a.fs + b.fs) % mod1, (a.sc + b.sc) % mod2);
}
P operator - (P a, P b){
    return mk((a.fs + mod1 - b.fs) % mod1, (a.sc + mod2 - b.sc) % mod2);
}
int get_mod(){
    int x;
    do{
        x = rand() % 8;
    }while(vis[x]);
    vis[x] = 1;
    return modd[x];
}
int read(){
    int x = 0;
    char ch = getchar();
    while(ch > '9' || ch < '0')ch = getchar();
    while(ch >= '0' && ch <= '9')x = 10 * x + ch - 48, ch = getchar();
    return x;
}
void print(int x){
    if(x > 9)print(x / 10);
    putchar(x % 10 + 48);
}
void dfs(int u){
    sz[u] = 1;
    dep[u] = dep[fa[u]] + 1;
    for(int i = head[u];i;i = nex[i]){
        int v = to[i];
        if(v == fa[u])continue;
        fa[v] = u;
        dfs(v);
        sz[u] += sz[v];
        if(sz[son[u]] < sz[v])son[u] = v;
    }
}
void dfs(int u, int tp){
    top[u] = tp;
    dfn[u] = ++cnt; 
    id[cnt] = u;
    if(son[u])dfs(son[u], tp);
    for(int i = head[u];i; i = nex[i]){
        int v = to[i];
        if(v == fa[u] || v == son[u])continue;
        dfs(v, v);
    }
}
int LCA(int x, int y){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]])swap(x, y);
        x = fa[top[x]];
    } 
    return dep[x] > dep[y] ? y : x;
}
vector<P> get(int x, int y){
    int lca = LCA(x, y);
    up.clear();
    while(top[x] != top[lca])up.push_back(mk(dfn[x], dfn[top[x]])), x = fa[top[x]];
    up.push_back(mk(dfn[x], dfn[lca]));
    while(top[y] != top[lca])dw.push_back(mk(dfn[top[y]], dfn[y])), y = fa[top[y]];
    if(lca != y){
        dw.push_back(mk(dfn[son[lca]], dfn[y]));
    }
    while(dw.size()) up.push_back(dw.back()), dw.pop_back();
    return up;
}
P get(int fl, int st, int len){
    if(fl)return h2[st-len+1] - h2[st+1] * p[len];
    return h1[st+len-1] - h1[st-1] * p[len];
}
void add(int x, int y){
    to[++size] = y; nex[size] = head[x]; head[x] = size;
}
int main(){
    srand(time(0));
    mod1 = get_mod();
    mod2 = get_mod();
    cin>>n;
    scanf("%s", s + 1);
    p[0] = mk(1, 1); p[1] = B;
    int u, v;
    for(int i = 2;i <= n; i++){
        u = read(); v = read();
        add(u, v);add(v, u);
        p[i] = p[i-1] * B;
    }
    dfs(1);
    dfs(1, 1);
    for(int i = 1;i <= n; i++){
        int x = s[id[i]];
        h1[i] = h1[i-1] * B + mk(x, x);
    }
    for(int i = n;i >= 1; i--){
        int x = s[id[i]];
        h2[i] = h2[i+1] * B + mk(x, x);
    }
    m = read();
    while(m--){
        int a = read(), b = read(), c = read(), d = read();
        f = get(a, b); g = get(c, d);
        int i = 0, j = 0, ans = 0;
        while(i < f.size() && j < g.size()){
            int df1 = f[i].fs, df2 = f[i].sc;
            int dg1 = g[j].fs, dg2 = g[j].sc;
            int flf = df2 < df1, flg = dg2 < dg1;
            int lf = abs(df1 - df2) + 1, lg = abs(dg2 - dg1) + 1;
            int len = min(lf, lg);
            P hf = get(flf, df1, len), hg = get(flg, dg1, len);
            if(hf == hg){
                if(len == lf)i++;
                else f[i].fs = flf == 1 ? df1 - len : df1 + len;
                if(len == lg)j++;
                else g[j].fs = flg == 1 ? dg1 - len : dg1 + len;
                ans += len;
            }
            else{
                int l = 0, r = len, res = 0;
                while(l <= r){
                    int mid = l + r >> 1;
                    if(get(flf, df1, mid) == get(flg, dg1, mid))l = mid + 1, res = mid;
                    else r = mid - 1;
                }
                ans += res;
                break;
            }
        }
        print(ans);
        puts("");
    }
    return 0;
}