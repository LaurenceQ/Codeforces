#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("pair.in", "w", stdout);
    int T = rand() % 11;
    T++;
    printf("%d 1\n", T);
    srand(time(0));
    for(int t = 1; t <= T; t++){
        for(int i = 1;i <= 5e5; i++){
            printf("%d", rand() % 10);
        }
        puts("");
    }
}
