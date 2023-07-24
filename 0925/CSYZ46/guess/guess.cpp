#include<bits/stdc++.h>
using namespace std;
#define P pair<int,int>
int n, perm[66];
int tx[100010], ty[100010];
struct ddd{
    int x, y;
}node[66], tmp[66];
bool operator == (struct ddd a, struct ddd b){
    return a.x == b.x && a.y == b.y;
}
bool check(){
    for(int i = 1;i <= n; i++)if(perm[i] != i)return 1;
    return 0;
}
void work1(){
    int k = n;
    next_permutation(perm + 1, perm + 1 + n);
    while(check()){
        int now = 0, fl = 1;
        for(int i = 1;i <= n; i++){
            tmp[i].x = node[i].x;
            tmp[i].y = node[perm[i]].y;
            for(int j = i - 1;j >= 1; j--){
                if(tmp[i] == tmp[j]){
                    fl = 0;
                    break;
                }
            }
            if(fl == 0)break;
        }
        for(int i = 1;i <= n; i++){
            for(int j = 1;j <= n; j++){
                if(tmp[i] == node[j])now++;
            }
        }
        if(fl)
            k = min(now, k);
        next_permutation(perm + 1, perm + 1 + n);
    }
    cout<<k<<endl;
}
void work3(){
    int ans = 0;
    for(int i = 1;i <= 100000; i++){
        ans = max(ans, 2 * ty[i] - n);
    }
    cout<<ans<<endl;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("guess.in", "r", stdin);
    freopen("guess.out", "w", stdout);
    #endif
    cin>>n;
    int flag1 = 1, flag2 = 1;
    for(int i = 1;i <= n; i++){
        cin>>node[i].x>>node[i].y;
        perm[i] = i;
        tx[node[i].x]++;
        ty[node[i].y]++;
        if(tx[node[i].x] > 1)flag1 = 0;
        if(ty[node[i].y] > 1)flag2 = 0;
    }
    //work3();
    if(n <= 8)work1();
    else{
        if(flag1 && flag2)puts("0");
        else{
            if(flag1 || flag2){
                if(flag2)swap(tx, ty);
                work3();
            }
            else printf("%d\n", n);
        }
    }
    return 0;
}   
