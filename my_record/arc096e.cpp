#include<bits/stdc++.h>
using namespace std;
const int N = 3e3 + 11;
int S[N][N], C[N][N];
int n, mod;
inline int A(int x, int y){
    return x + y - (x + y >= mod ? mod : 0);
}
inline int M(int x, int y){
    return 1LL * x * y % mod;
}
inline int ksm(int base, int x, int mod){
    int ans = 1;
    while(x){
        if(x & 1)ans = 1LL * ans * base % mod;
        base = 1LL * base * base % mod;
        x >>= 1;
    }
    return ans;
}
int main(){
    cin>>n>>mod;
    C[0][0] = S[0][0] = 1;
    for(int i = 1;i <= n + 1; i++){
        C[i][0] = 1;
        for(int j = 1;j <= i; j++){
            C[i][j] = A(C[i-1][j-1], C[i-1][j]);
            S[i][j] = A(S[i-1][j-1], M(S[i-1][j], j));
        }
    }
    int ans = ksm(2, ksm(2, n, mod - 1), mod);
    //printf("ans=%d\n", ans);
    for(int i = 1;i <= n; i++){
        int res = 0;
        for(int j = 0;j <= i; j++){
            res = A(res, M(S[i+1][j+1], ksm(2, 1LL * (n - i) * j % (mod - 1), mod)));
        }
        res = M(res, M(C[n][i], ksm(2, ksm(2, n - i, mod - 1), mod)));
        //printf("i=%d res=%d\n", i, res);
        if(i & 1)ans = A(ans, mod - res);
        else ans = A(ans, res);
    }
    cout<<ans<<endl;
    return 0;
}