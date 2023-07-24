#include<bits/stdc++.h>
using namespace std;
#define LL long long
LL k, fac[22];
int num[100000], flag, tot, rt[10000], cnt, ans;
void dfs(LL x, int lev,int lim){
    if(x == 1){
        tot = lev - 1;
        flag = 1;
        return ;
    }
    for(int i = lim;i > 1; i--){
        //printf("x=%lld i=%d\n", x, i);
        if(x % fac[i] == 0){
            num[lev] = i;
            ans += i + 1;
            dfs(x / fac[i], lev + 1,i);
            if(flag){
                return ;
            }
            ans -= i + 1;
        }
    }
}
int main(){
    int T;
    fac[0] = 1;
    for(int i = 1;i <= 20; i++){
        fac[i] = fac[i-1] * (1LL * i);
    }
    scanf("%d", &T);
    while(T--){
        scanf("%lld", &k);
        //printf("%lld\n", k);
        if(k == 1){
            puts("1");
            continue;
        }
        flag = 0;
        tot = 0;
        ans = 2;
        dfs(k, 1,19);
        if(!flag)puts("-1");
        else{
            /*for(int i = 1;i <= tot; i++){
                printf("%d ", num[i]);
            }
            puts("");*/
            
            printf("%d\n", ans);
            cnt = 0;
            for(int i = 1;i <= tot; i++){
                rt[i] = ++cnt;
                if(i > 1)printf("%d %d\n", rt[i], rt[i-1]);
                for(int j = 1;j <= num[i]; j++){
                    printf("%d %d\n", rt[i], ++cnt);
                }
            }
            printf("%d %d\n", rt[tot], ++cnt);
            printf("%d %d\n", cnt, cnt + 1);
        }
    }
    return 0;
}
