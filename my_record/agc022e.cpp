#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 3e5 + 11;
int f[N][3][3], n;
char s[N];
inline int A(int x, int y){
	return x + y - (x + y >= mod ? mod : 0);
}
inline int M(int x, int y){
	return 1LL * x * y % mod;
}
int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	f[0][0][0] = 1;
	for(int i = 0;i < n; i++){
		for(int x = 0;x <= 2; x++){
			for(int y = 0;y <= 2; y++){
				int F = f[i][x][y];
				if(s[i+1] != '0'){
					if(y == 0) f[i+1][x+(x!=2)][y] = A(f[i+1][x+(x!=2)][y], F);
					else f[i+1][x][y-1] = A(f[i+1][x][y-1], F);
				}
				if(s[i+1] != '1'){
					if(y == 2) f[i+1][x][y-1] = A(f[i+1][x][y-1], F);
					else f[i+1][x][y+1] = A(f[i+1][x][y+1], F);
				}
			}
		}
	}
	int ans = 0;
	for(int x = 0;x <= 2; x++){
		for(int y = x;y >= 0; y--)ans = A(ans, f[n][x][y]);
	}
	cout<<ans<<endl;
	return 0;
}
