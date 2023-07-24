#include<bits/stdc++.h>
using namespace std;
#define LL long long
int n, perm[1111][1111], ans[1111], flag, now[1111];
map<LL, int> mp;
LL tong[1011], base = 998244353;
void deal(int* x){
    //for(int i = 1;i <= n; i++){
        //printf("%d ", x[i]);
    //}
    //puts("");
    for(int i = 1;i <= n; i++)mp[tong[i]] = 0;
    for(int i = 1;i <= n; i++){
        mp[tong[i]]++;   
    }
    flag = 1;
    for(int i = 1;i <= n; i++){
        LL now = 0;
        for(int j = 1;j <= n; j++){
            if(i == j)continue;
            if(x[j] > x[i]){
                now = now * base + x[j] - 1;
            }
            else now = now * base + x[j];
        }
        //printf("i=%d now=%lld\n", i, now);
        mp[now]--;
        if(mp[now] < 0)flag = 0;
    }
    //for(int i = 1;i <= n; i++){
        //printf("%d ", mp[tong[i]]);
    //}
    //puts("");
}
int main(){
    freopen("puzzle.in", "r", stdin);
    freopen("puzzle.out", "w", stdout);
    cin>>n;
    for(int i = 1;i <= n; i++){
        for(int j = 1;j < n; j++){
            scanf("%d", &perm[i][j]);
            tong[i] = tong[i] * base + perm[i][j];
        }
        //printf("i=%d tong=%lld\n", i, tong[i]);
    }
    for(int i = 1;i <= n; i++){
        for(int j = 1;j <= n; j++){
            now[j] = n;
            for(int k = 1;k < j; k++){
                now[k] = perm[i][k];
            }
            for(int k = j;k < n; k++){
                now[k+1] = perm[i][k];
            }
            deal(now);
            if(flag){
                for(int k = 1;k <= n; k++){
                    printf("%d ", now[k]);
                }
                puts("");
                return 0;
            }
        }
    }
    return 0;
}
