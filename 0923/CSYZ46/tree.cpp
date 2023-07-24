#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define rg register
const int N = 2e6 + 11;
const int M = 5e5 + 11;
int n, m;
LL p[N];
int head[N], nex[N<<1], to[N<<1], size; 
struct ddd{
    int v, k;
}q[M];
LL read() {
    rg LL x = 0;
    rg char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') x = x * 10LL + c - '0', c = getchar();
    return x;
}
inline void add(int x, int y){
    to[++size] = y;
    nex[size] = head[x];
    head[x] = size;
}
LL dfs(int u, int fa, int k){
    if(k == 0)return p[u];
    LL res = p[u];
    for(int i = head[u];i; i = nex[i]){
        rg int v = to[i];
        if(v == fa)continue;
        res += dfs(v, u, k - 1);
    } 
    return res;
}
void work1(){
    for(rg int i = 1;i <= m; i++){
        printf("%lld\n", dfs(q[i].v, q[i].v, q[i].k));
    }
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    #endif
    n = read();
    for(rg int i = 1;i <= n; i++)p[i] = read();
    rg int u, v;
    for(rg int i = 1;i < n; i++){
        u = read(); v = read();
        add(u, v);
        add(v, u);
    }
    rg int ma = 0;
    m = read();
    for(rg int i = 1;i <= m; i++){
        q[i].v = read();
        q[i].k = read();
        ma = max(ma, q[i].k);
    }
    work1();
    //cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;
    return 0;
}
