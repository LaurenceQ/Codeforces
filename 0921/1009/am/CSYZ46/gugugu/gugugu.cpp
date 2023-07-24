#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 2e5 + 11;
const int mod = 1e9 + 7;
int n, m;
LL f[N];
struct ddd{
    int l, r, id;
    LL v;
    bool operator < (const ddd &x) const{
        return l < x.l;
    }
}ln[N];
vector<int> add[N], del[N];
set<LL> s;
inline LL A(LL x, LL y){
    return x + y - ( x + y >= mod ? mod : 0);
}
int main(){
    freopen("gugugu.in", "r", stdin);
    freopen("gugugu.out", "w", stdout);
    cin>>n>>m;
    for(int i = 1;i <= m; i++){
        scanf("%d%d%lld", &ln[i].l, &ln[i].r, &ln[i].v);
    }
    sort(ln + 1, ln + 1 + m);
    for(int i = 1;i <= m; i++){
        ln[i].id = i;
        add[ln[i].l].push_back(i);
        del[ln[i].r+1].push_back(i);
        if(ln[i].l == 1)f[i] = ln[i].v;
    }
    set<LL>::iterator it;
    for(int i = 1;i <= n; i++){
        int len = del[i].size();
        for(int j = 0;j < len; j++){
            s.erase(f[del[i][j]]);
        }
        len = add[i].size();
        for(int j = 0;j < len; j++){
            int now = ln[add[i][j]].id;
            for(it = s.begin();it != s.end(); it++){
                f[now] = A(f[now], *it * ln[now].v % mod);
            }
            s.insert(f[now]);
        }
    }
    LL ans = 0;
    if(!s.empty());
        for(it = s.begin();it != s.end(); it++){
            ans = A(ans, *it);
        }
    cout<<ans<<endl;
    return 0;
}
