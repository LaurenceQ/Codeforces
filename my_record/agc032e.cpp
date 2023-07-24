#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 11;
int n, mod;
int a[N<<1];
bool check(int pos){
    int l = pos + 1, r = 2 * n;
    while(l <= r){
        if(a[l] + a[r] < mod)return 0;
        l++; r--;
    }
    return 1;
}
int main(){
    cin>>n>>mod;
    for(int i = 1;i <= n + n; i++){
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + 1 + n + n);
    int l = 0, r = n, ans = n;
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid << 1))r = mid - 1, ans = min(ans, mid);
        else l = mid + 1;
    }
    l = 1, r = 2 * ans;
    int Z = 0;
    while(l <= r){
        Z = max(Z, a[l] + a[r]);
        l++; r--;
    }
    l = 2 * ans + 1;r = 2 * n;
    while(l <= r){
        Z = max(Z, a[l] + a[r] - mod);
        l++; r--;
    }
    //printf("ans=%d Z=%d\n", ans * 2, Z);
    cout<<Z<<endl;
    return 0;
}