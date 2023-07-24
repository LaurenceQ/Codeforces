#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 11;
#define LL long long
LL a[N], p[N], s, ans;
int n;
LL dfs(int l, int r){
    if(a[l] > s || a[r] < s){
        if(a[l] > s){
            ans += a[r] - s;
            return a[r];
        }
        if(a[r] < s){
            ans += s - a[l];
            return a[l];
        }
    }
    LL now, pos;
    if(p[l] >= p[r]){
        now = r;
        p[l] += p[r];
        pos = dfs(l, r - 1);
    }
    else {
        now = l;
        p[r] += p[l];
        pos = dfs(l + 1, r);
    }
    ans += abs(a[now] - pos);
    return a[now];
}
int main(){
    cin>>n>>s;
    for(int i = 1;i <= n; i++){
        scanf("%lld%lld", &a[i], &p[i]);
    }
    dfs(1, n);
    cout<<ans<<endl;
    return 0;
}