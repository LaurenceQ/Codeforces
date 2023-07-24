#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 2e5 + 8;
int head[N], nex[N<<1], to[N<<1], size;
int a[N], n, st;
LL ans, sum[N], tot, sz[N];
struct ddd{
    int v;
    LL a, b;
};
vector<ddd> e[N];
int read(){
    int x = 0;
    char ch = getchar();
    while(ch > '9' || ch < '0')ch = getchar();
    while(ch >= '0' && ch <= '9')x = 10 * x + ch - 48, ch = getchar();
    return x;
}
void add(int x, int y){
    to[++size] = y;
    nex[size] = head[x];
    head[x] = size;
}
bool cmp(struct ddd x, struct ddd y){
    if(x.a * y.b != x.b * y.a)
        return x.a * y.b < x.b * y.a;
    else 
        return x.b == y.b ? x.a > y.a : x.b > y.b;
}
void dfs1(int u, int fa){
    //printf("u=%d\n", u);
    sum[u] = a[u];
    for(int i = head[u];i;i = nex[i]){
        int v = to[i];
        if(v == fa)continue;
        dfs1(v, u);
        e[u].push_back((ddd){v, sz[v], sum[v]});
        sum[u] += sum[v];
        sz[u] += sz[v] + 1;
    }
}
void dfs2(int u, int fa){
    //printf("u=%d\n", u);
    int s = e[u].size();
    sort(e[u].begin(), e[u].end(), cmp);
    //for(int i = 0;i < s; i++)printf("v=%d s=%lld\n", e[u][i].v, e[u][i].b);
    tot++;
    ans += a[u] * tot;
    for(int i = 0;i < s; i++){
        int v = e[u][i].v;
        dfs2(v, u);
    }
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("signin.in", "r", stdin);
    freopen("signin.out", "w", stdout);
    #endif
    n = read();
    int u, v;
    for(int i = 1;i < n; i++){
        u = read();
        v = read();
        add(u, v);
        add(v, u);
    }
    for(int i = 1;i <= n; i++){
        a[i] = read();
        if(a[i] > a[st]) st = i;
    }
    dfs1(st, st);
    dfs2(st, st);
    printf("%lld\n", ans);
    return 0;
}
