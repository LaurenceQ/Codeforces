#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e5 + 11;
struct ddd{
    int x, y, r, w;
    bool operator < (const ddd &a) const{
        return r < a.r;
    }
}cir[N];
int n, f[N];
bool mark[N];
int head[N], nex[N], to[N], size;
void add(int x, int y){
    to[++size] = y;
    nex[size] = head[x];
    head[x] = size;
}
int read(){
    int x = 0;
    char ch = getchar();
    while(ch > '9' || ch < '0')ch = getchar();
    while(ch >= '0' && ch <= '9')x = 10 * x + ch - 48, ch = getchar();
    return x;
}
LL dis(int x, int y){
    return 1LL * (cir[x].x - cir[y].x) * (cir[x].x - cir[y].x) + 1LL * (cir[x].y - cir[y].y) * (cir[x].y - cir[y].y);
}
bool judge(int x, int y){
    if(dis(x, y) < 1LL * cir[y].r * cir[y].r){
        return 1;
    }
    else return 0;
}
int dfs(int u){
    if(mark[u])return f[u];
    else mark[u] = 1;
    int res = 0;
    for(int i = head[u];i;i = nex[i]){
        res += dfs(to[i]);
    }
    return f[u] = max(cir[u].w, res);
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("circle.in", "r", stdin);
    freopen("circle.out", "w", stdout);
    #endif
    n = read();
    for(int i = 1; i <= n; i++){
        cir[i].x = read();
        cir[i].y = read();
        cir[i].r = read();
        cir[i].w = read();
    }
    sort(cir + 1,  cir + 1 + n);
    for(int i = 1;i <= n; i++){
        for(int j = i + 1;j <= n; j++){
            if(judge(i, j)){
                add(j, i);
                break;
            }
        }
    }
    int ans = 0;
    for(int i = n;i >= 1; i--){
        if(!mark[i]){
            ans += dfs(i);
        }
    }
    printf("%d\n", ans);
    return 0;
}

