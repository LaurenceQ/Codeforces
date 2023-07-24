#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 1e6 + 11;
int f[N][3];
int n, fac[N], inv[N];
inline int M(int x, int y){
    return 1LL * x * y % mod;
}
inline int A(int x, int y){
    return x + y - (x + y >= mod ? mod : 0);
}
inline int C(int x, int y){
    if(x < y)return 0;
    return M(fac[x], M(inv[y], inv[x-y]));
}
int ksm(int base, int x){
    int ans = 1;
    while(x){
        if(x & 1)ans = M(ans, base);
        base = M(base, base);
        x >>= 1;
    }
    return ans;
}
int main(){
    cin>>n;
    fac[0] = fac[1] = inv[1] = inv[0] = 1;
    for(int i = 2;i <= n; i++){
        inv[i] = (mod - 1LL * mod / i * inv[mod%i] % mod);
        fac[i] = M(fac[i-1], i);
    }
    for(int i = 2;i <= n; i++)inv[i] = M(inv[i-1], inv[i]);
    f[0][0] = 1;
    for(int i = 1;i <= n; i++){
        for(int j = 0;j <= 2; j++){
            for(int k = 0;k <= 2; k++){
                if(j == k)continue;
                f[i][j] = A(f[i][j], f[i-1][k]);
            }
        }
    }
    int ans = 0;
    int all = ksm(ksm(3, n - 1), mod - 2);
    for(int i = 1;i <= n; i++){
        int res = M(C(n, i), f[i][1]);
        res = M(res, all);
        ans = A(ans, M(res, ksm(M(3 * n, i), mod - 2)));
    }
    cout<<ans<<endl;
    return 0;
}