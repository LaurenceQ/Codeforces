#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 11;
const int M = 5e5 + 11;
int n;
int cnt, tot;
int fail[N], ch[N][27];
int dfn[N], sz[N];
int dl[N], len[N], ed[N];
int ans[M];
char *s[N], mem[N], tmp[N];
vector<int> G[N];
struct qst{
    int id, k, val;
    qst (int _id = 0, int _k = 0, int _val = 0){
        id = _id, k = _k, val = _val;
    }
};
vector<qst> Q[N];
struct bit{
    int t[N];
    int query(int x){
        int ans = 0;
        for(;x;x -= -x & x)ans += t[x];
        return ans;
    }
    int query(int l, int r){
        return query(r) - query(l - 1);
    }
    void add(int x, int v){
        for(;x <= 200000; x += -x & x)t[x] += v;
    }
}T;
void dfs(int u){
    sz[u] = 1;
    dfn[u] = ++cnt;
    for(int v : G[u]){
        dfs(v);
        sz[u] += sz[v];
    }
}
void build(){
    int hd = 0, tl = 0;
    for(int i = 0;i < 26; i++){
        if(ch[0][i]){
            dl[++tl] = ch[0][i];
        }
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
        if(!ch[u][s[i]]) ch[u][s[i]] = ++tot;
        u = ch[u][s[i]];
    }
    ed[id] = u;
}
void check(char *s, int len){
    int u = 0;
    for(int i = 0;i < len; i++){
        u = ch[u][s[i]];
        T.add(dfn[u], 1);
    }
}
int main(){
    int q;
    cin>>n>>q;
    char *tp = mem;
    int now = 0;
    for(int i = 1;i <= n; i++){
        scanf("%s", tmp);
        len[i] = strlen(tmp);
        s[i] = tp;
        tp += len[i];
        for(int j = 0;j < len[i]; j++)mem[now++] = tmp[j], s[i][j] -= 'a';
        insert(s[i], len[i], i);
    }
    build();
    int l, r, k;
    for(int i = 1;i <= q; i++){
        scanf("%d%d%d", &l, &r, &k);
        Q[l-1].push_back(qst(i, k, -1));
        Q[r].push_back(qst(i, k, 1));
    }
    for(int i = 1;i <= n; i++){
        check(s[i], len[i]);
        for(int j = 0;j < Q[i].size(); j++){
            qst now = Q[i][j];
            int u = ed[now.k];
            ans[now.id] += now.val * T.query(dfn[u], dfn[u] + sz[u] - 1);
        }
    }
    for(int i = 1;i <= q; i++){
        printf("%d\n", ans[i]);
    }
    return 0;
}