#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 11;
const int mod = 998244353;
#define LL long long
int n, m, k, ord[N];
LL a[N], tmp[N], ans, tot;
inline LL A(LL x, LL y){
    return x + y - (x + y >= mod ? mod : 0);
}
bool mark[N];
void dfs(int lev){
    if(lev > m){
        tot++;
        memcpy(tmp, a, sizeof(a));
        for(int i = 1;i <= m; i++){
            int l = ord[i] == 1 ? n : ord[i] - 1;
            int r = ord[i] == n ? 1 : ord[i] + 1;
            tmp[l] += tmp[ord[i]];
            tmp[r] += tmp[ord[i]];
            tmp[ord[i]] = 0;
        }
        if(tmp[1] >= k)ans++;
        return;
    }
    for(int i = 1;i <= n; i++){
        if(mark[i])continue;
        mark[i] = 1;
        ord[lev] = i;
        dfs(lev + 1);
        mark[i] = 0;

    }
}
LL ksm(LL base, LL x){
    base %= mod;
    LL ans = 1;
    while(x){
        if(x & 1){
            ans = ans * base % mod;
        }
        base = base * base % mod;
        x >>= 1;
    }
    return ans;
}

int main(){
    freopen("fake.in", "r", stdin);
    freopen("fake.out", "w", stdout);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        for(int i = 1;i <= n; i++){
            scanf("%lld", &a[i]);
        }
        ans = tot = 0;
        dfs(1);
        ans = ans * ksm(tot, mod - 2) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
