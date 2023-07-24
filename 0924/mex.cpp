#include<bits/stdc++.h>
using namespace std;
int n, a[10000011], tot;
bool mark[11100001];
vector<int> ins[1111];
int cnt = 0;
void work(int n){
    //printf("n=%d\n", n);
    tot = 0;
    memset(mark, 0, sizeof(mark));
    memset(a, 0, sizeof(a));
    int i = 1;
    while(n / i){
        if(!mark[n/i])a[++tot] = n / i, mark[n/i] = 1;
        i++;
    }
    sort(a + 1, a + 1 + tot);
    bool flag = 1;
    for(int i = 1;i <= tot; i++){
        if(i != a[i]){
            printf("%d, ", i);
            flag = 0;
            break;
        }
    }
    if(flag){
        printf("%d, ", n + 1);
    }
    cnt++;
    if(cnt % 10000 == 0)puts("");
}
int main(){
    freopen("mex.in", "r", stdin);
    freopen("mex.out", "w", stdout);
    int n = 2e7;
    for(int i = 1;i <= n; i++){
        work(i);
    }
    //for(int i = 1;i <= n; i++){
        //printf("i=%d\n", i);
        //int s = ins[i].size();
        //for(int j = 0;j < s; j++){
            //printf("%d ", ins[i][j]);
        //}
        //kjputs("");
    //}
    return 0;
}
