#include<bits/stdc++.h>
using namespace std;
char s[5050], zh[5050], best[5055], now[5050];
int tp, len, ans = 1e9, tot, n;
void dfs(int lev, int stp){
    //if(lev > 1)return ;
    if(tot > ans)return ;
    if(tot + (len - lev + 1) > ans)return ;
    if(lev > len){
        //printf("%d\n", tot + tp);
        //for(int i = 1;i <= tot; i++){
            //printf("%c", now[i]);
        //}
        //for(int i = 1;i <= tp; i++){
            //printf("P");
        //}
        //puts("");
        if(ans > tot + tp){
            ans = tot + tp;
            for(int i = 1;i <= tot; i++){
                best[i] = now[i];
            }
            for(int i = tot + 1;i <= tot + tp; i++)best[i] = 'P';
        }
        return ;
    }
    char tmp[44];
    int add = 0, cnt = 0;
    bool flag = 0;
    while(tp && zh[tp] != s[lev]){
        now[++tot] = 'P';
        tmp[++cnt] = zh[tp];
        add++;
        tp--;
    }
    if(!tp){
        zh[++tp] = s[lev], now[++tot] = s[lev], add++;
        flag = 1;
    }
    now[++tot] = 'Q';
    dfs(lev + 1, stp + add);
    --tot;
    if(flag)--tot, tp--;
    for(int i = cnt;i >= 1; i--){
        zh[++tp] = tmp[i]; 
        tot--;
    }
    //printf("cnt=%d tp=%d zh=%c\n", cnt, tp, zh[tp]);
    if(zh[tp] != s[lev]){
        zh[++tp] = s[lev];
        now[++tot] = s[lev];
        now[++tot] = 'Q';
        //printf("tp=%d zh=%c\n", tp, zh[tp]);
        dfs(lev + 1, stp + 1);
        tot -= 2; tp--;
    }
}
void work(){
    int tot = 0;
    for(int i = 1;i <= len; i++){
        if(!tp){
            zh[++tp] = s[i];
            tot++;
            tot++;
        }
        else{
            if(zh[tp] == s[i]){
                tot++;
                continue;
            }
            else{
                if(tp == 1){
                    zh[++tp] = s[i];
                    tot++;
                    tot++;
                }
                else{
                    tp--;
                    tot++;
                    tot++;
                }
            }
        }
    }
    printf("%d\n", tot + tp);
}
int main(){
    freopen("letter.in", "r", stdin);
    freopen("letter.out", "w", stdout);
    scanf("%s", s + 1);
    len = strlen(s + 1);
    bool flag = 1;
    for(int i = 1;i <= len; i++){
        if(s[i] == 'c')flag = 0;
    }
    if(flag){
        work(); 
        return 0;
    }
    dfs(1, 0);
    //printf("ans=%d\n", ans);
    //for(int i = 1;i <= ans; i++){
        //printf("%c", best[i]);
    //}
    cout<<ans<<endl;
    return 0;
}
