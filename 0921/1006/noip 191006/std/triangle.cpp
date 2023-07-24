#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long

int n, k;
ll a[N], b[N], c[N], d[N], e[N];

bool check1(int x) {
	if (a[x]+a[x+1]>a[x+2] && a[x+3]+a[x+4]>a[x+5]) return true;
	if (a[x]+a[x+1]>a[x+3] && a[x+2]+a[x+4]>a[x+5]) return true;
	if (a[x]+a[x+1]>a[x+4] && a[x+2]+a[x+3]>a[x+5]) return true;
	if (a[x]+a[x+1]>a[x+5] && a[x+2]+a[x+3]>a[x+4]) return true;
	if (a[x]+a[x+2]>a[x+3] && a[x+1]+a[x+4]>a[x+5]) return true;
	if (a[x]+a[x+2]>a[x+4] && a[x+1]+a[x+3]>a[x+5]) return true;
	if (a[x]+a[x+2]>a[x+5] && a[x+1]+a[x+3]>a[x+4]) return true;
	if (a[x]+a[x+3]>a[x+4] && a[x+1]+a[x+2]>a[x+5]) return true;
	if (a[x]+a[x+3]>a[x+5] && a[x+1]+a[x+2]>a[x+4]) return true;
	if (a[x]+a[x+4]>a[x+5] && a[x+1]+a[x+2]>a[x+3]) return true;
	return false;
}

bool dfs(int now, int t1, int t2, int t3, ll s1, ll s2, ll s3) {
	if ((t1 & t2 & t3) == 3) return true;
	if (t1 < 2 && dfs(now+1, t1+1, t2, t3, s1+a[now], s2, s3)) return true;
	if (t2 < 2 && dfs(now+1, t1, t2+1, t3, s1, s2+a[now], s3)) return true;
	if (t3 < 2 && t2 > 0 && dfs(now+1, t1, t2, t3+1, s1, s2, s3+a[now])) return true;
	if (t1 == 2 && a[now]<s1 && dfs(now+1, 3, t2, t3, s1, s2, s3)) return true;
	if (t2 == 2 && a[now]<s2 && dfs(now+1, t1, 3, t3, s1, s2, s3)) return true;
	if (t3 == 2 && a[now]<s3 && dfs(now+1, t1, t2, 3, s1, s2, s3)) return true;
	return false;
}

bool check2(int x) {
	return dfs(x+1, 1, 0, 0, a[x], 0, 0);
}

ll calc1() {
	for (int i = n-1; i > 1; --i)
		if (a[i-2]+a[i-1]>a[i])
			return a[i-2]+a[i-1]+a[i];
	return -1;
}

ll calc2() {
	for(int i = n-1; i > 1; --i) {
		b[i] = a[i-2]+a[i-1]>a[i] ? a[i-2]+a[i-1]+a[i] : 0;
		c[i] = max(b[i], c[i+1]);
	}
	ll ans = -1;
	for(int i = n-4; i > 1; --i)
		if (b[i] && c[i])
			ans = max(ans, b[i]+c[i+3]);
	for (int i = n-1; i > 4; --i)
		if (check1(i-5)) {
			ans = max(ans, a[i]+a[i-1]+a[i-2]+a[i-3]+a[i-4]+a[i-5]);
			break;
		}
	return ans;
}

ll calc3() {
	for(int i = n-1; i > 1; --i) {
		b[i] = a[i-2]+a[i-1]>a[i] ? a[i-2]+a[i-1]+a[i] : 0;
		c[i] = max(b[i], c[i+1]);
	}
	for(int i = n-4; i > 1; --i) {
		e[i] = e[i+1];
		if (b[i] && c[i+3])
			e[i] = max(e[i], b[i]+c[i+3]);
	}
	for (int i = n-1; i > 4; --i) {
		d[i] = check1(i-5) ? a[i]+a[i-1]+a[i-2]+a[i-3]+a[i-4]+a[i-5] : 0;
		e[i-3] = max(e[i-3], d[i]);
	}
	ll ans = -1;	
	for(int i = n-4; i > 2; --i) {
		if (d[i] && c[i+3]) ans = max(ans, d[i]+c[i+3]);
		if (b[i] && e[i+3]) ans = max(ans, b[i]+e[i+3]);
	}
	for(int i = n-1; i > 7; --i)
		if (check2(i-8)){
			ans = max(ans, a[i]+a[i-1]+a[i-2]+a[i-3]+a[i-4]+a[i-5]+a[i-6]+a[i-7]+a[i-8]);
			break;
		}
	return ans;
}

int main() {
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
	
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; ++i) scanf("%lld", a + i);
	sort(a, a + n);
	ll ans = 0;
	switch(k) {
		case 1: ans = calc1(); break;
		case 2: ans = calc2(); break;
		case 3: ans = calc3(); 
	}
	cout << ans << endl;
	return 0;
}
