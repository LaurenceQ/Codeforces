#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e3 + 11;
const int M = 300111;
int n, m, q, col[N];
char ss[11];
struct ddd{
    int a, b, id;
    LL c;
    bool operator < (const ddd &x)const{
        return c < x.c;
    }
}gg[M], tmp[M];
set<ddd> s;
bool flag;
int head[N], nex[M], to[M], size;
void clear(){
    memset(head, 0, sizeof(head));
    memset(to, 0, sizeof(to));
    memset(nex, 0, sizeof(nex));
    size = 0;
}
void add(int x, int y){
    to[++size] = y;
    nex[size] = head[x];
    head[x] = size;
}
void dfs(int u, int fl){
    //printf("u=%d\n", u);
    col[u] = fl;
    for(int i = head[u]; i; i = nex[i]){
        int v = to[i];
        if(col[v] != -1){
            if((col[v] ^ col[u]) == 0){
                //printf("u=%d v=%d\n", u, v);
                flag = 0; return ;

            }
            else continue;
        }
        dfs(v, fl ^ 1);
        if(!flag)return ;
    }
}
void work(){
    set<ddd>::iterator it;
    int tot = 0;
    for(it = s.begin();it != s.end(); it++){
        tmp[++tot] = *it;
    }
    int ans = tot, l = 1, r = tot;
    while(l <= r){
        int mid = (l + r) >> 1;
        flag = 1;
        clear();
        for(int i = mid;i <= tot; i++){
            add(tmp[i].a, tmp[i].b);
            add(tmp[i].b, tmp[i].a);
        }
        memset(col, -1, sizeof(col));
        for(int i = 1;i <= n; i++){
            if(col[i] == -1)dfs(i, 0);
        }
        //printf("mid=%d c=%d flag=%d\n", mid, tmp[mid].c, flag);
        if(flag){
            ans = min(ans, mid);
            r = mid - 1;
        }
        else l = mid + 1;
    }
    printf("%lld\n", tmp[ans-1].c);
}
int main(){
    freopen("redgreen.in", "r", stdin);
    freopen("redgreen.out", "w", stdout);
    cin>>n>>m>>q;
    int a, b, c;
    for(int i = 1;i <= m; i++){
        scanf("%d%d%d", &a, &b, &c);
        gg[i].a = a;
        gg[i].b = b;
        gg[i].c = c;
        gg[i].id = i;
        s.insert(gg[i]);
    }
    int id;
    while(q--){
        scanf("%s", ss + 1);
        
        if(ss[1] == 'D'){
            scanf("%d", &id);
            s.erase(gg[id]);
        }
        if(ss[1] == 'A'){
            scanf("%d%d%d", &a, &b, &c);
            gg[++m].a = a;
            gg[m].b = b; gg[m].c = c; gg[m].id = m;
            s.insert(gg[m]);
        }
        if(ss[1] == 'Q'){
            work();
        }
    }
    return 0;
}
