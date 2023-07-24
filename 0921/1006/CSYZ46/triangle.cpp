#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e6 + 11;
LL a[N];
int n, k;
int main(){
    freopen("triangle.in", "r", stdin);
    freopen("triangle.out", "w", stdout);
    cin>>n>>k;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    sort(a + 1, a + 1 + n);
    LL ans = 0;
    int tot = 0;
    for(int i = n;i >= 1; i--){
        if(a[i] < a[i-1] + a[i-2])ans += a[i] + a[i-1] + a[i-2], i -= 2, tot++;
        if(tot == k)break;
    }
    if(tot == k)
        printf("%lld\n", ans);
    else puts("-1");
    return 0;
}
