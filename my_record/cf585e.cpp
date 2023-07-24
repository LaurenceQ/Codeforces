#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 1e7 + 11;
int pri[N], miu[N], tot;
int base[N], a[500100], tong[N];
bool is_not[N];
int ma, n;
void pre(){
	miu[1] = 1;
	for(int i = 2;i <= ma; i++){
		if(!is_not[i])pri[++tot] = i, miu[i] = -1;
		for(int j = 1;j <= tot && pri[j] * i <= ma; j++){
			is_not[i*pri[j]] = 1;
			miu[i*pri[j]] = -miu[i];
			if(i % pri[j] == 0){
				miu[i*pri[j]] = 0;
				break;
			}
		}
	}
}
int main(){
	cin>>n;
	base[0] = 1;
	for(int i = 1;i <= n; i++){
		scanf("%d", &a[i]);
		tong[a[i]]++;
		ma = max(ma, a[i]);
		base[i] = (base[i-1] << 1) % mod;
	}
	pre();
	long long ans = 0;
	for(int i = 2;i <= ma; i++){
		if(!miu[i])continue;
		int tot = 0;
		for(int j = i;j <= ma; j += i){
			tot += tong[j];
		}
		ans = (ans - 1LL * (base[tot] - 1) * (n - tot) * miu[i] % mod + mod) % mod;
	}
	cout<<ans<<endl;
	return 0;
}
