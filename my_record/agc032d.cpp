#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 11;
#define LL long long
LL f[N][N], A, B, a[N];
int n;
int main(){
	cin>>n>>A>>B;
	memset(f, 127, sizeof(f));
	f[0][0] = 0;
	for(int i = 1;i <= n; i++)cin>>a[i];
	for(int i = 0;i < n; i++){
		LL x = a[i+1];
		for(int j = 0;j <= n; j++){
			if(j <= x){
				f[i+1][j] = min(f[i+1][j], f[i][j] + A);
				f[i+1][x] = min(f[i+1][x], f[i][j]);
			}
			if(j > x){
				f[i+1][j] = min(f[i+1][j], f[i][j] + B);
			}
		}
	}
	LL ans = 1e18;
	for(int i = 0;i <= n; i++){
		ans = min(ans, f[n][i]);
	}
	cout<<ans<<endl;
	return 0;
}
