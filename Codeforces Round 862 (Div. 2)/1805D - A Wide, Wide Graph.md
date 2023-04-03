https://codeforces.com/contest/1805/problem/D

Solution: Notice the longest chain(diameter) in the tree. Assume diameter is $L$, then for $k\leq L/2$, there is only one connected component.

Based on property that the ends of diameter are the farthest from any node in the tree, the connected component will add 1 when $k$ exceed the depth of a tree when it's rooted on a certain node.

```
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 11;
vector<int> G[N];
int cha[N];
void dfs(int u, int fa, int d, vector<int>& dep){
    dep[u] = d;
    for(int v : G[u]){
        if(v == fa)continue;
        dfs(v, u, d + 1, dep);
    }
}
int main(){
    int n;
    cin>>n;
    for(int i = 1;i < n; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        G[u-1].push_back(v-1);
        G[v-1].push_back(u-1);
    }
    vector<int> d1(n), d2(n);// Dfs twice to find the ends of the diameter
    dfs(0, -1, 0, d1);
    int u = max_element(d1.begin(), d1.end()) - d1.begin(); 
    // max_element : return the address of the max iterator. 
    dfs(u, -1, 0, d1);
    int v = max_element(d1.begin(), d1.end()) - d1.begin();
    dfs(v, -1, 0, d2);
    cha[0] = 1;
    for(int i = 0;i < n; i++){
        if(i == u)continue;
        d2[i] = max(d2[i], d1[i]);
        cha[d2[i]+1] += 1;
    }
    for(int i = 1;i <= n; i++){
        cha[i] += cha[i-1];
        printf("%d ", cha[i]);
    }
    puts("");
    return 0;
}
