#include<bits/stdc++.h>
using namespace std;
const int N = 3e3 + 11;
const int mod = 1e9 + 7;
int f[N][N], n, q, a[N];
inline int A(int x, int y){
    return x + y - (x + y >= mod ? mod : 0);
}
inline int M(int x, int y){
    return 1LL * x * y % mod;
}
int main(){
    cin>>n>>q;
    for(int i = 1;i <= n; i++)cin>>a[i];
    for(int i = 1;i <= n; i++){
        for(int j = 1;j <= n; j++)f[i][j] = a[i] < a[j];
    }
    int inv2 = (mod + 1) / 2, mi = 1;
    for(int i = 1;i <= q; i++){
        mi = (mi << 1) % mod;
        int x, y;
        cin>>x>>y;
        f[x][y] = f[y][x] = M(inv2, A(f[x][y], f[y][x]));
        for(int j = 1;j <= n; j++){
            if(j == x || j == y)continue;
            f[x][j] = f[y][j] = M(inv2, A(f[x][j], f[y][j]));
            f[j][x] = f[j][y] = M(inv2, A(f[j][x], f[j][y]));
        }
    }
    int ans = 0;
    for(int i = 1;i <= n; i++){
        for(int j = i - 1;j >= 1; j--)ans = A(ans, f[i][j]);
    }
    ans = M(ans, mi);
    cout<<ans<<endl;
    return 0;
}