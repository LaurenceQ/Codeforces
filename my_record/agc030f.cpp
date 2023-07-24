#include<bits/stdc++.h>
using namespace std;
const int N = 633;
const int mod = 1e9 + 7;
int f[N][N][N];
int a[N], n, cnt;
int typ[N], tmp[N];
int main(){
	cin>>n;
	n <<= 1;
	for(int i = 1;i <= n; i++)cin>>a[i];
	for(int i = 1;i <= n; i += 2){
		if(a[i] != -1 && a[i+1] != -1){
			typ[a[i]] = typ[a[i+1]] = 3;
		}
		else{
			if(a[i] != -1)typ[a[i]] = 2;
			else if(a[i+1] != -1)typ[a[i+1]] = 2;
			else cnt++;
		}
	}
	for(int i = 1;i <= n; i++)tmp[n-i+1] = typ[i];
	for(int i = 1;i <= n; i++)typ[i] = tmp[i];
	f[0][0][0] = 1;
	for(int i = 1;i <= n; i++){
//		printf("i=%d tp=%d\n", i, typ[i]);
		if(typ[i] == 3){
			memcpy(f[i], f[i-1], sizeof f[i]);
			continue;
		}
		for(int j = 0;j <= n; j++){
			for(int k = 0;k <= n; k++){
				if(typ[i] == 0){
					f[i][j][k] = (f[i-1][j+1][k] + 1LL * f[i-1][j][k+1] * (k + 1) % mod) % mod;
					if(j > 0)f[i][j][k] = (f[i][j][k] + f[i-1][j-1][k]) % mod;
				}
				else{
					f[i][j][k] = f[i-1][j+1][k];
					if(k > 0)f[i][j][k] = (f[i][j][k] + f[i-1][j][k-1]) % mod;
				}
			}
		}
	}
	int ans = f[n][0][0];
	for(int i = 1;i <= cnt; i++){
		ans = 1LL * ans * i % mod;
	}
	cout<<ans<<endl;
	return 0;
}
