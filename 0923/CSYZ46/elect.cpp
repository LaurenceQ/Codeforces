#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e6 + 11;
const int mod = 1e9 + 7;
int n, k, a[N];
LL base[N];
inline LL A(LL x, LL y){
    return x + y - (x + y >= mod ? mod : 0);
}
int read() {
    int x = 0, c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("elect.in", "r", stdin);
    freopen("elect.out", "w", stdout);
    #endif
    n = read();
    k = read();
    int cnt = 0;
    while(cnt != n){
        char ch = getchar();
        if(ch != 'A' && ch != 'B')continue;
        if(ch == 'A')a[++cnt] = 1;
        else a[++cnt] = -1;
    }
    base[0] = 1;
    for(int i = 1;i <= n; i++)base[i] = base[i-1] * 2 % mod;
    LL sum = 0, ans = 0;
    for(int i = n;i >= 1; i--){
        sum += a[i];
        if(sum > 0)sum = 0;
        if(sum < -k){
            ans = A(ans, base[i]);
            sum += 2;
            if(sum > 0)sum = 0;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
