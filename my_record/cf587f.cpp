#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e5 + 11;
int n, q, tot, cnt, all;
char *s[N], mem[N], tmp[N];
int len[N], ed[N];
int fail[N], ch[N][27];
int dl[N], sz[N], dfn[N];
LL ans[N], num[N], sum[N];
vector<int> G[N];
struct bit{
    LL t[N];
    void add(int l, int r, int val){
        add(l, val); add(r + 1, -val);
    }
    void add(int x, int val){
        for(;x <= cnt; x += -x & x){
            t[x] += val;
        }
    }
    LL query(int x){
        LL ans = 0;
        for(;x;x -= -x & x){
            ans += t[x];
        }
        return ans;
    }
}T;
struct qst{
    int id, k, val;
    qst(int _id = 0, int _k = 0, int _val = 0){
        id = _id; k = _k; val = _val;
    }
};
vector<qst>Q[N], D[N];
void dfs(int u){
    sz[u] = 1; dfn[u] = ++cnt;
    for(int v : G[u]){
        dfs(v);
        sz[u] += sz[v];
    }
}
void build(){
    int hd = 0, tl = 0;
    for(int i = 0;i < 26; i++){
        if(ch[0][i])dl[++tl] = ch[0][i];
    }
    while(hd < tl){
        int u = dl[++hd];
        G[fail[u]].push_back(u);
        for(int i = 0;i < 26; i++){
            int v = ch[u][i];
            if(v)fail[v] = ch[fail[u]][i], dl[++tl] = v;
            else ch[u][i] = ch[fail[u]][i];
        }
    }
    dfs(0);
}
void insert(char *s, int len, int id){
    int u = 0;
    for(int i = 0;i < len; i++){
        if(!ch[u][s[i]])ch[u][s[i]] = ++all;
        u = ch[u][s[i]];
    }
    ed[id] = u;
}
void check(char *s, int len){
    int u = 0;
    for(int i = 0;i < len; i++){
        u = ch[u][s[i]];
        num[u]++;
    }
}
void dfs0(int u){
    for(int v : G[u]){
        dfs0(v);
        num[u] += num[v];
    }
}
LL checkk(char *s, int len){
    int u = 0;
    LL ans = 0;
    for(int i = 0;i < len; i++){
        u = ch[u][s[i]];
        ans += T.query(dfn[u]);
    }
    return ans;
}
int main(){
    cin>>n>>q;
    char *now = mem;
    for(int i = 1;i <= n; i++){
        scanf("%s", tmp);
        len[i] = strlen(tmp);
        s[i] = now; now += len[i];
        for(int j = 0;j < len[i]; j++)mem[tot++] = tmp[j] - 'a';
        insert(s[i], len[i], i);
    }
    build();
    int block = sqrt(tot);
    for(int i = 1;i <= q; i++){
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        if(len[k] <= block){
            Q[l-1].push_back(qst(i, k, -1));
            Q[r].push_back(qst(i, k, 1));
        }
        else{
            D[k].push_back(qst(i, l, r));
        }
    }
    for(int i = 1;i <= n; i++){
        if(!D[i].size())continue;
        memset(sum, 0, sizeof(sum));
        memset(num, 0, sizeof(num));
        check(s[i], len[i]);
        dfs0(0);
        //printf("i=%d\n", i);
        for(int j = 1;j <= n; j++)sum[j] = sum[j-1] + num[ed[j]];//, printf("j=%d sum=%d num=%d\n", j, sum[j], num[ed[j]]);
        for(int j = 0;j < D[i].size(); j++){
            qst now = D[i][j];
            ans[now.id] = sum[now.val] - sum[now.k-1];
        }
    }
    for(int i = 1;i <= n; i++){
        int u = ed[i];
        T.add(dfn[u], dfn[u] + sz[u] - 1, 1);
        for(int j = 0;j < Q[i].size(); j++){
            qst now = Q[i][j];
            ans[now.id] += checkk(s[now.k], len[now.k]) * now.val;
        }
    }
    for(int i = 1;i <= q; i++){
        printf("%lld\n", ans[i]);
    }
    return 0;
}