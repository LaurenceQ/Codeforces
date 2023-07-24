#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 3e3 + 11;
const int M = 1e6 + 11;
const int mod = 1e9 + 7;
int n, m, k, a[N], b[N], c[N*2], tot;
struct ddd{
    int st, ed;
}e[M];
bool mark[2*N][2*N];
LL f[N][N];
inline LL A(LL x, LL y){
    return x + y - (x + y >= mod ? mod : 0);
}
int read(){
    int x = 0;
    char ch = getchar();
    while(ch > '9' || ch < '0')ch = getchar();
    while(ch >= '0' && ch <= '9')x = 10 * x + ch - 48, ch = getchar();
    return x;
}
int find(int x){
    return lower_bound(c + 1, c + 1 + tot, x) - c;
}
int main(){
    cin>>n>>m>>k;
    for(int i = 1;i <= n; i++){
        a[i] = read();
        c[++tot] = a[i];
    }
    for(int i = 1;i <= m; i++){
        b[i] = read();
        c[++tot] = b[i];
    }
    sort(c + 1, c + 1 + tot);
    tot = unique(c + 1, c + 1 + tot) - (c + 1);
    for(int i = 1;i <= n; i++){
        a[i] = find(a[i]);
    }
    for(int i = 1;i <= m; i++){
        b[i] = find(b[i]);
    }
    for(int i = 1;i <= k; i++){
        e[i].st = read(), e[i].ed = read();
        int u = find(e[i].st), v = find(e[i].ed);
        if(u <= tot && v <= tot && e[i].st == c[u] && e[i].ed == c[v] ){
            mark[u][v] = 1;
        }
    }
    for(int i = 1;i <= n; i++){
        LL s = 1;
        for(int j = 1;j <= m; j++){
            f[i][j] = A(f[i][j], f[i-1][j]);
            if(a[i] == b[j]){
                f[i][j] = A(f[i][j], s);
            }
            if(mark[b[j]][a[i]])s = A(f[i-1][j], s);
        }
    }
    LL ans = 0;
    for(int j = 1;j <= m; j++){
        ans = A(ans, f[n][j]);
    }
    printf("%lld\n", ans);
    return 0;
}
