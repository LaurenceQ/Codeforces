#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define P pair<LL, int>
#define fs first
#define sc second
#define mk_p make_pair
const int N = 1e5 + 11;
int n;
LL a[N], b[N], sum[N];
P c[N+N];
bool mark[N];
int main(){
	cin>>n;
	for(int i = 1;i <= n; i++){
		scanf("%lld%lld", &a[i], &b[i]);
		c[i] = mk_p(a[i], i);
		c[i+n] = mk_p(b[i], i + n);
	}
	sort(c + 1, c + 1 + n + n);
	bool flag = 0, flag2 = 1, flag3 = 1;
	for(int i = 1;i <= n; i++){
		LL v = c[i].fs;
		int pos = c[i].sc;
		if(pos > n)pos -= n, flag2 = 0;
		else flag3 = 0;
		if(mark[pos])flag = 1;
		mark[pos] = 1;
		sum[i] = sum[i-1] + v;
	}
	if(flag || flag2 || flag3){
		cout<<sum[n]<<endl;
		return 0;
	}
	LL ans = 1e18;
	for(int i = 1;i <= n; i++){
		P now1 = mk_p(a[i], i);
		P now2 = mk_p(b[i], i + n);
		int pos1 = lower_bound(c + 1, c + 1 + n, now1) - c;
		int pos2 = lower_bound(c + 1, c + 1 + n, now2) - c;
		if(pos1 >= n && pos2 >= n)ans = min(ans, a[i] + b[i] + sum[n-2]);//, printf("a+b+sum=%lld\n", a[i] + b[i] + sum[n-2]);
		else if(pos1 < n)ans = min(ans, sum[n-1] + b[i]);//, printf("b+sum=%lld\n", sum[n-1] + b[i]);
		else ans = min(ans, sum[n-1] + a[i]);//, printf("a+sum=%lld\n", sum[n-1] + a[i]);
	}
	cout<<ans<<endl;
	return 0;
}
