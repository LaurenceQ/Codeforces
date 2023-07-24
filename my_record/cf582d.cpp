#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int mod = 1e9 + 7;
const int N = 3511;
int f[N][N][2][2];
int aph, n, len;
LL p;
vector<int> a, b, c;
char s[N];
int A(int x, int y){
    return x + y - (x + y >= mod ? mod : 0);
}
int M(int x, int y){
    return 1LL * x * y % mod;
}
int cal1(int x, int r, int nr){
    if(r) return A(M(p, p), mod - cal1(x, !r, nr));
    return (1LL * (x + 1 - nr) * (x + 2 - nr) / 2) % mod;
}
int cal2(int x, int r, int nr){
    if(!r)return x + 1 - nr;
    else return p - cal2(x, !r, nr);
}
int cal3(int x, int nr){
    return A(M(p, p), mod - A((max(0ll, 1LL * (p - x) * (p - x - 1) / 2)) % mod, (1LL * (p - nr) * (p + 1 - nr) / 2) % mod));
}
int deal(){
    b.clear();
    int len = a.size() - 1;
    LL res = 0;
    for(int i = len;i >= 0; i--){
        res = res * 10ll + a[i];
        if(res >= p || b.size())b.push_back(res / p);
        res %= p;
    }
    reverse(b.begin(), b.end());
    a = b;
    return res;
}
int main(){
    cin>>p>>aph;
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    reverse(s + 1, s + 1 + len);
    for(int i = 1;i <= len; i++){
        a.push_back(s[i] - '0');
    }
    while(a.size()){
        c.push_back(deal());
    }
    c.push_back(0);
    reverse(c.begin(), c.end());
    f[0][0][1][0] = 1;
    n = c.size() - 1;
    if(aph > n){
        puts("0");
        return 0;
    }
    for(int i = 0;i <= n; i++){
        int Z = c[i+1];
        for(int j = 0;j <= min(i + 2, aph); j++){
            for(int eq = 0;eq < 2; eq++){
                for(int r = 0;r < 2; r++){
                    int F = f[i][j][eq][r];
                    if(!F)continue;
                    if(i == n)continue;
                    for(int nr = 0;nr < 2; nr++){
                        int nt = min(aph, j + nr);
                        if(!eq){
                            f[i+1][nt][eq][nr] = A(f[i+1][nt][eq][nr], M(F, cal1(p - 1, r, nr)));
                        }
                        else{
                            f[i+1][nt][eq][nr] = A(f[i+1][nt][eq][nr], M(F, cal2(Z, r, nr)));
                            if(!Z)continue;
                            if(!r){
                                f[i+1][nt][!eq][nr] = A(f[i+1][nt][!eq][nr], M(F, cal1(Z - 1, r, nr)));
                            }
                            else{
                                f[i+1][nt][!eq][nr] = A(f[i+1][nt][!eq][nr], M(F, cal3(Z - nr, nr)));
                            }
                        }
                    }
                }
            }
        }
   }
   int ans = 0;
   ans = A(f[n][aph][0][0], f[n][aph][1][0]);
   cout<<ans<<endl;
   return 0;
}