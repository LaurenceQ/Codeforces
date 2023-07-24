#include<bits/stdc++.h>
using namespace std;
int n, ans, s, e;
int dir[22];
struct ddd{
    int x, y;
}node[33];
void dfs(int lev){
    if(lev == n + 1){
        bool flag = 0;
        for(int i = 1;i <= n; i++){
            if(dir[i] == 0 || dir[i] == 1)continue;
            for(int j = 1;j <= n; j++){
                if(dir[j] == 2 || dir[j] == 3)continue;
                if(dir[i] == 2 && dir[j] == 0 && node[j].x < node[i].x && node[j].y > node[i].y){
                    if(e < node[j].y)flag = 1;
                }
                if(dir[i] == 3 && dir[j] == 0 && 
            }
        }
    }
    for(int i = 0;i < 4; i++){
        dir[lev] = i;
        dfs(lev + 1);
    }
}
int main(){
    cin>>n>>s>>e;
    for(int i = 1;i <= n; i++){
        cin>>node[i].x>>node[i].y;
    }
    dfs(1);
    printf("%d\n", ans);
    return 0;
}
