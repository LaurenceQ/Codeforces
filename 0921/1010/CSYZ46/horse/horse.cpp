#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e5 + 11;
int n;
LL a[N], ans, now;
struct ddd{
    int v;
    LL w;
    bool operator < (const ddd &x)const{
        return w < x.w;
    }
};
vector<ddd> e[N];
int read(){
    int x = 0;
    char ch = getchar();
    while(ch > '9' || ch < '0') ch = getchar();
    while(ch >= '0' && ch <= '9')x = 10 * x + ch - 48, ch = getchar();
    return x;
}
void dfs(int u, int fa){
    //printf("u=%d fa=%d now=%lld\n", u, fa, now);
    int sz = e[u].size();
    now += a[u];
    for(int i = 0;i < sz; i++){
        int v = e[u][i].v;
        LL w = e[u][i].w;
        if(v == fa)continue;
        if(now < w){
            ans += w - now;
            now = 0;
        }
        else now -= w;
        dfs(v, u);
        if(now >= w)now -= w;
        else ans += w - now, now = 0;
    }
}
int main(){
    freopen("horse.in", "r", stdin);
    freopen("horse.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1;i <= n; i++){
        a[i] = read();
    }
    int u, v, w;
    for(int i = 1;i < n; i++){
        u = read(), v = read(), w = read();
        e[u].push_back((ddd){v, w});
        e[v].push_back((ddd){u, w});
    }
    for(int i = 1;i <= n; i++){
        sort(e[i].begin(), e[i].end());
    }
    dfs(1, 0);
    printf("%lld\n", ans);
    return 0;
}
