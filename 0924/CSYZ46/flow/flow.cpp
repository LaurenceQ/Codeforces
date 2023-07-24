#include<bits/stdc++.h>
using namespace std;
int n, a, b, id;
int main(){
    #ifndef ONLINE_JUDGE
    freopen("flow.in", "r", stdin);
    freopen("flow.out", "w", stdout);
    #endif
    cin>>id;
    int T, ans = 0;
    cin>>T;
    while(T--){
        int flag = 0;
        scanf("%d%d%d", &n, &a, &b);
        if(a == 0 && b == 0){
            puts("0");
            continue;
        }
        if(a == 0){
            if(b >= n && b != 1 + n)puts("1"), ans++;
            else puts("0");
            continue;
        }
        if(b == 0){
            if(a != 1 + n && a >= n)puts("1"), ans++;
            else puts("0");
            continue;
        }
        if(a == 1){
            puts("0");
            continue;
        }
        if(n == 2){
            if(a % 2 == 1)puts("0");
            else puts("1"), ans++;
            continue;
        }
        if(b >= n){
            flag |= 1;
        }
        else{
            if(a >= (n - b) * 2 && a - (n - b) * 2 != 1)flag |= 1;
        }
        if(a == n && b != 1)flag |= 1;
        if(a > n + 1)flag |= 1;
        ans += flag;
        printf("%d\n", flag);
    }
    //printf("ans=%d\n", ans);
    return 0;
}   
