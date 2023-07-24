#include<bits/stdc++.h>
using namespace std;
const int N = 5010;
#define LL long long
LL f[N][N], a[N], b[N], c[N], d[N], x[N];
int n, s, e;
int main(){
    cin>>n>>s>>e;
    for(int i = 1;i <= n; i++) cin>>x[i];
    for(int i = 1;i <= n; i++) cin>>a[i];
    for(int i = 1;i <= n; i++) cin>>b[i];
    for(int i = 1;i <= n; i++) cin>>c[i];
    for(int i = 1;i <= n; i++) cin>>d[i];
    memset(f, 127, sizeof(f));
    f[0][0] = 0;
    for(int i = 1;i <= n; i++){
        bool fls = i > s;
        bool fle = i > e;
        for(int j = i - 1;j >= 0; j--){
            if(i == s){
                f[i][j+1] = min(f[i][j+1], f[i-1][j] + d[i] - x[i]);
                if(i == n || j - fle > 0) f[i][j] = min(f[i][j], f[i-1][j] + x[i] + c[i]);
            }
            else{
                if(i == e){
                    f[i][j+1] = min(f[i][j+1], f[i-1][j] - x[i] + b[i]);
                    if(i == n || j - fls > 0) f[i][j] = min(f[i][j], f[i-1][j] + x[i] + a[i]);
                }
                else{
                    f[i][j+1] = min(f[i][j+1], f[i-1][j] - 2 * x[i] + d[i] + b[i]);
                    if(j - fls > 0) f[i][j] = min(f[i][j], f[i-1][j] + c[i] + b[i]);
                    if(j - fle > 0) f[i][j] = min(f[i][j], f[i-1][j] + a[i] + d[i]);
                    if(j > 1){
                        if(i == n || j - fle - fls > 0) f[i][j-1] = min(f[i][j-1], f[i-1][j] + 2 * x[i] + c[i] + a[i]);
                    }
                }
            }
        }
    }
    cout<<f[n][1]<<endl;
    return 0;
}