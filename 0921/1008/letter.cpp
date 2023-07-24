#include<bits/stdc++.h>
using namespace std;
char s[5050], zh[5050];
int tp, len, ans;
int main(){
    freopen("letter.in", "r", stdin);
    freopen("letter.out", "w", stdout);
    scanf("%s", s + 1);
    len = strlen(s + 1);
    for(int i = 1;i <= len; i++){
        if(!tp){
            zh[++tp] = s[i];
            continue;
        }
        if(zh[tp] == s[i]){
            //printf("i=%d\n", i);
            ans++;
            continue;
        }
        if(zh[tp] != s[i]){
            if(zh[tp-1] == s[i]){
                tp--;
                ans += 4;
            }
            else{
                zh[++tp] = s[i];
            }
        }
    }
    ans += tp + 2;
    char c = zh[1];
    /*printf("ans=%d\n", ans);
    for(int i = 1;i <= tp; i++){
        printf("%c", zh[i]);
    }
    puts("");
    */
    for(int i = 2;i <= tp; i++){
        
        ans += c == zh[i] ? 0 : 2;
    }
    cout<<ans<<endl;
    return 0;
}
