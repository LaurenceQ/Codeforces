#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 11;
#define LL long long
#define db double
int n;
db sum;
struct prob{
	LL p, t;
}a[N];
struct grade{
	LL p, tma, tmi;
}b[N];
bool cmp(prob a, prob b){
	return a.p * b.t > a.t * b.p; 
}
bool cmpp(grade a, grade b){
	return a.p > b.p;
}
bool check(db c){
	db lst = 1e9, now = 1e9;
	for(int i = 1;i <= n; i++){
		now = min(now, 1.0 * b[i].p * (1.0 - c * b[i].tma / sum));
		if(1.0 * b[i].p * (1.0 - c * b[i].tmi / sum) > lst){
			return 0;
		}
		if(b[i+1].p != b[i].p){
			lst = now;
		}
	}
	return 1;
}
int main(){
	cin>>n;
	for(int i = 1;i <= n; i++){
		scanf("%lld", &a[i].p);
	}
	for(int i = 1;i <= n; i++){
		scanf("%lld", &a[i].t);
		sum += a[i].t;
	}
	sort(a + 1, a + 1 + n, cmp);
	LL lst = 0, now = 0;
	int lstp = 1;
	for(int i = 1;i <= n; i++){
		now += a[i].t;
		b[i].p = a[i].p;
		b[i].tmi = lst + a[i].t;
		if(i == n || a[i].p * a[i+1].t != a[i].t * a[i+1].p){
			for(int j = i;j >= lstp; j--){
				b[j].tma = now;
			}
			lstp = i + 1; lst = now;
		}
	}
	sort(b + 1, b + 1 + n, cmpp);
	db l = 0, r = 1, ans = 0;
	while(r - l > 1e-12){
		db mid = (l + r) / 2.0;
		if(check(mid))l = mid, ans = mid;
		else r = mid;
	}
	printf("%.11lf\n", ans);
	return 0;
}
/*
4
15 7 10 20 
15 7 10 20 
*/
