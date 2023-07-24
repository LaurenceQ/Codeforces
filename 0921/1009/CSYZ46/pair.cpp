#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int mod = 998244353;
const int N = 5e5 + 11;
int T, id;
LL base[111];
inline LL A(LL x, LL y){
    return x + y - (x + y >= mod ? mod : 0);
}
LL deal(LL x){
    //printf("x=%lld\n", x);
    LL ans = 0;
    for(int i = 0;i <= 13 && x / base[i]; i++){
        int now = x / base[i] % 10;
        for(int j = i + 1;j <= 13; j++){
            if(now  < x / base[j] % 10)ans++;
        }
    }
    //printf("ans=%lld\n", ans);
    return ans;
}
int main(){
    freopen("pair.in", "r", stdin);
    freopen("pair.out", "w", stdout);
    base[0] = 1;
    for(int i = 1;i <= 18; i++)base[i] = base[i-1] * 10LL;
    cin>>T>>id;
    LL l, r;
    while(T--){
        scanf("%lld%lld", &l, &r);
        LL ans = 0;
        for(LL i = l;i <= r; i++){
            ans = A(ans, deal(i));
        }
        printf("%lld\n", ans);
    }
    return 0;
}
