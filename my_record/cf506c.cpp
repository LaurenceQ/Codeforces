#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 11;
const int M = 5e3 + 11;
#define LL long long
#define P pair<LL, int>
#define fs first
#define sc second
#define mk_p make_pair
int n, m, K;
LL p, a[N], h[N], f[N];
priority_queue<P, vector<P>, greater<P> >q;
bool check(LL x){
    while(q.size())q.pop();
    memset(f, 0, sizeof(f));
    for(int i = 1;i <= n; i++){
        if(x - a[i] * m >= h[i])continue;
        q.push(mk_p(x / a[i], i));
    }
    for(int i = 1;i <= m; i++){
        for(int j = 1;j <= K; j++){
            if(q.empty())continue;
            P now = q.top();
            if(now.fs < i)return 0;
            q.pop();
            f[now.sc]++;
            if(p * f[now.sc] + x - m * a[now.sc] >= h[now.sc])continue;
            now.fs = (p * f[now.sc] + x) / a[now.sc];
            q.push(now);
        }
    }
    return q.empty();
}
int main(){
    cin>>n>>m>>K>>p;
    for(int i = 1;i <= n; i++){
        scanf("%lld%lld", &h[i], &a[i]);
    }
    LL l = 0, r = 1e14, ans = 1e14;
    while(l <= r){
        LL mid = l + r >> 1;
        if(check(mid))r = mid - 1, ans = min(ans, mid);
        else l = mid + 1;
    }
    cout<<ans<<endl;
    return 0;
}