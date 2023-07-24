#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 11;
#define LL long long
LL X[N], Y[N], len[111];
int n, tot;
int nex[5] = {-1, 1, 0, 0};
int ney[5] = {0, 0, -1, 1};
char mp[5] = {'L', 'R', 'D', 'U'};
int main(){
	cin>>n;
	int flag = -1;
	for(int i = 1;i <= n; i++){
		cin>>X[i]>>Y[i];
		if(flag == -1)flag = (abs(X[i]) + abs(Y[i])) % 2;
		else if(flag != (abs(X[i]) + abs(Y[i])) % 2){
			puts("-1");
			return 0;
		}
	}
	if(!flag)
		len[++tot] = 1;
	for(int i = 1;i <= 31; i++)len[++tot] = 1 << (i - 1);
	sort(len + 1, len + 1 + tot, greater<LL>());
	printf("%d\n", tot);
	for(int i = 1;i <= tot; i++){
		printf("%lld ", len[i]);
	}
	puts("");
	for(int i = 1;i <= n; i++){
		LL nx = 0, ny = 0;
		for(int j = 1;j <= tot; j++){
			int pos = 0;
			LL mi = 5e9;
			for(int k = 0;k < 4; k++){
				LL tox = nx + nex[k] * len[j];
				LL toy = ny + ney[k] * len[j];
				if(abs(X[i] - tox) + abs(Y[i] - toy) < mi){
					mi = abs(X[i] - tox) + abs(Y[i] - toy);
					pos = k;
				}
			}
			printf("%c", mp[pos]);
			nx = nx + nex[pos] * len[j]; ny = ny + ney[pos] * len[j];
		}
		puts("");
//		printf("nx=%lld ny=%lld\n", nx, ny);
	}
	return 0;
}
