#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e5 + 11;
const int M = 401;
#define P pair<LL, int>
#define mk make_pair
#define fs first
#define sc second
int n;
int B, bl[N], p[N];
LL f[N], a[N];
struct block{
    int L, R, l, r;
    LL q[M], k, b;
    double slop(int x, int y){
        if(a[x] == a[y])return f[x] <= f[y] ? 1e18 : -1e18;
        return 1.0 * (f[y] - f[x]) / (a[y] - a[x]);
    }
    void build(){
        for(int i = L;i <= R; i++)f[i] += k * a[i] + b;
        r = b = k = 0;
        l = 1;
        for(int i = L;i <= R; i++){
            while(r > 1 && slop(q[r-1], q[r]) < slop(q[r], p[i]))r--;
            q[++r] = p[i];
        }
    }
    LL F(int x){
        return f[x] + k * a[x] + b;
    }
    P query(){
        if(!r)return mk(-1e18, L);
        while(l + 1 <= r && F(q[l]) <= F(q[l+1]))l++;
        return mk(F(q[l]), q[l]);
    }
}t[M];
bool cmp(int x, int y){
    return a[x] < a[y];
}
int main(){
    cin>>n;
    B = sqrt(n);
    for(int i = 0;i < n; i++){
        scanf("%lld", &a[i]);
        f[i] = a[i];
        p[i] = i;
        bl[i] = i / B;
    }
    for(int i = 0;i <= bl[n-1]; i++){
        int L = i * B, R = min((i + 1) * B - 1, n - 1);
        t[i].L = L; t[i].R = R;
        sort(p + L, p + R + 1, cmp);
        /*printf("i=%d\n", i);
        for(int j = L;j <= R; j++){
            printf("j=%d p=%d\n", j, p[j]);
        }
        */
        t[i].build();
    }
    LL ans = 0, sum = 0;
    for(int i = 1;i <= n; i++){
        P now = (mk(0, 0));
        for(int j = 0;j <= bl[n-1]; j++){
            now = max(now, t[j].query());
        }
        //printf("i=%d now.fs=%lld\n", i, now.fs);
        if(!now.fs)break;
        sum += now.fs;
        ans = max(ans, sum);
        for(int j = 0;j < bl[now.sc]; j++){
            t[j].b += a[now.sc];
        }
        for(int j = bl[now.sc] + 1;j <= bl[n-1]; j++){
            t[j].k++;
        }
        for(int j = t[bl[now.sc]].L;j < now.sc; j++)f[j] += a[now.sc];
        for(int j = t[bl[now.sc]].R;j > now.sc; j--)f[j] += a[j];
        f[now.sc] = -1e18;
        t[bl[now.sc]].build();
    }
    cout<<ans<<endl;
    return 0;
}
/*
5
-3 -2 -3 -3 -2
*/