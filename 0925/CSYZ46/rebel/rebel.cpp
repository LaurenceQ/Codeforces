#include<bits/stdc++.h>
using namespace std;
#define db double
const int N = 1e3 + 11;
int n, s, dl[N*N*10];
struct ddd{
    int x, y, z, vx, vy, vz;
}node[N];
bool mark[N];
db dis[N];
int read(){
    int x = 0;
    char ch = getchar();
    while(ch > '9' || ch < '0')ch = getchar();
    while(ch >= '0' && ch <= '9')x = 10 * x + ch - 48, ch = getchar();
    return x;
}
db sqq(db x){
    return x * x;
}
db get(int u, int v){
    return sqrt(sqq(node[u].x - node[v].x) + sqq(node[u].y - node[v].y) + sqq(node[u].z - node[v].z));
}
void dij(){
    int hd = 0, tl = 1;
    dl[1] = 0;
    for(int i = 1;i < n; i++)dis[i] = 1e9;
    mark[0] = 1;
    while(hd < tl){
        hd++;
        int u = dl[hd];
        for(int i = 1;i < n; i++){
            if(i == u)continue;
            db may = max(dis[u], get(u, i));
            //printf("u=%d v=%d may=%.4lf\n", u, i, may);
            if(may < dis[i]){
                dis[i] = may;
                if(!mark[i]){
                    mark[i] = 1;
                    dl[++tl] = i;
                }
            }
        }
        mark[u] = 0;
    }
    printf("%.7lf\n", dis[1]);
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("rebel.in", "r", stdin);
    freopen("rebel.out", "w", stdout);
    #endif
    n = read(); s = read();
    for(int i = 0;i < n; i++){
        node[i].x = read();
        node[i].y = read();
        node[i].z = read();
        node[i].vx = read();
        node[i].vy = read();
        node[i].vz = read();
    }
    dij();
    return 0;
}
