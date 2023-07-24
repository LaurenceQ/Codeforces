#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e3 + 11;
const int M = 300111;
int n, m, q, col[N], fa[N], sz[N], tot, Q[M];
char ss[11];
struct ddd{
    int a, b, l, r, c;
    bool operator < (const ddd &x)const{
        return c < x.c;
    }
}gg[M];
int head[N], nex[M], to[M], size;
int read(){
    int x = 0;
    char ch = getchar();
    while(ch > '9' || ch < '0')ch = getchar();
    while(ch >= '0' && ch <= '9')x = 10 * x + ch - 48, ch = getchar();
    return x;
}
int find(int x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
void clear(){
    memset(head, 0, sizeof(head));
    for(int i = 1;i <= n; i++)fa[i] = i, sz[i] = 1, col[i] = 0;
    size = 0;
}
void add(int x, int y){
    to[++size] = y;
    nex[size] = head[x];
    head[x] = size;
}
void dfs(int u, int fth){
    col[u] ^= 1;
    for(int i = head[u]; i; i = nex[i]){
        int v = to[i];
        if(v == fth)continue;
        dfs(v, u);
    }
}
void work(int id){
    clear();
    int x, y, fx, fy;
    for(int i = m;i >= 1; i--){
        if(gg[i].l > Q[id] || gg[i].r < Q[id])continue;
        x = gg[i].a, y = gg[i].b;
        fx = find(x), fy = find(y);
        if(fx != fy){
            if(col[x] == col[y]){
                if(sz[fx] < sz[fy])dfs(x, 0);
                else dfs(y, 0);
            }
            sz[fx] += sz[fy];
            fa[fy] = fx;
            add(fx, fy);
            add(fy, fx);
        }
        else{
            if(col[x] == col[y]){
                printf("%d\n", gg[i].c);
                return ;
            }
        }
    }
    puts("0");
}
int main(){
    freopen("redgreen.in", "r", stdin);
    freopen("redgreen.out", "w", stdout);
    cin>>n>>m>>q;
    int a, b, c;
    for(int i = 1;i <= m; i++){
        scanf("%d%d%d", &a, &b, &c);
        gg[i].a = a;
        gg[i].b = b;
        gg[i].c = c;
        gg[i].r = i + m + 1;
    }
    for(int i = 1;i <= q; i++){
        scanf("%s", ss + 1);
        if(ss[1] == 'D'){
            gg[read()].r = i;
        }
        if(ss[1] == 'A'){
            gg[++m].a = read();
            gg[m].b = read();
            gg[m].c = read();
            gg[m].l = i; gg[m].r = i + m + 1;
        }
        if(ss[1] == 'Q'){
            Q[++tot] = i;
        }
    }
    sort(gg + 1, gg + 1 + m);
    for(int i = 1;i <= tot; i++){
        work(i);   
    }
    return 0;
}
