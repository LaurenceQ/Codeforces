#include<bits/stdc++.h>
using namespace std;
#define LL long long
int h, m, n, tp;
LL A[3030][3030], sum[3030][3030];
struct Data_Maker{
	long long Seed,a,b,c,MOD;
	long long Random() {
		c++;
		Seed=(Seed*a+b*c)%MOD;
		return Seed;
	}
	int Random_int() {
		int tmp=Random();
		if(Random()&1)tmp*=-1;
		return tmp;
	}
	void MAKE(){
		scanf("%lld%lld%lld%lld%lld",&Seed,&a,&b,&c,&MOD);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				A[i][j]=Random_int();
	}
}tmp;

int main(){
    freopen("rhombus.in", "r", stdin);
    freopen("rhombus.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &h, &tp);
    if(tp == 0){
        for(int i = 1;i <= n; i++){
            for(int j = 1;j <= m; j++)
                scanf("%lld", &A[i][j]);
        }
    }
    else tmp.MAKE();
    for(int i = 1;i <= n; i++){
        for(int j = 1;j <= m; j++){
            sum[i][j] = sum[i][j-1] + A[i][j];
        }
    }
    LL ans = -1e18;
    for(int i = 1;i <= n; i++){
        for(int j = 1;j <= m; j++){
            int u = i - h + 1, d = i + h - 1, l = j - h + 1, r = j + h - 1;
            if(u < 1 || d > n || l < 1 || r > m)continue;
            LL now = 0;
            for(int k = u;k <= d; k++){
                int nl = j - h + abs(k - i), nr = j + h - abs(k - i);
                now += sum[k][nr-1] - sum[k][nl];
            }
            ans = max(ans, now);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
