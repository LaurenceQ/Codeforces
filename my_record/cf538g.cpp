#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 11;
char S[6] = {'D', 'L', 'R', 'U'};
int nex[6] = {0, 0, 1, 1};
int ney[6] = {0, 1, 0, 1};
int cnt[6];
#define LL long long
int n;
LL loop, lx = -4e18, rx = 4e18, ly = -4e18, ry = 4e18;
string ans, tmp;
struct Pos{
	LL x, y, t, k, w;
}a[N], now[N];
bool cmp(Pos X, Pos Y){
	return X.w < Y.w;
}
void fail(){
	puts("NO");
	exit(0);
}
LL floor(LL x, LL y){
	if(!x)return 0;
	int flx = x < 0 ? -1 : 1;
	int fly = y < 0 ? -1 : 1;
	x = abs(x), y = abs(y);
	if(flx * fly > 0)return x / y;
	else return -((x - 1) / y + 1);
}
LL ceil(LL x, LL y){
	if(!x)return 0;
	int flx = x < 0 ? -1 : 1;
	int fly = y < 0 ? -1 : 1;
	x = abs(x), y = abs(y);
	if(flx * fly > 0)return (x - 1) / y + 1;
	return -(x / y);
}
void update(LL &l, LL &r, LL k, LL w, LL x1, LL x2){
	LL L = -w - x1 + x2, R = -x1 + x2;
//	printf("L=%lld R=%lld k=%lld\n", L, R, k);
	if(!k) {if(L > 0 || R < 0)fail();}
	else{
		if(k > 0){
//			printf("case1: L=%lld R=%lld\n", (LL)ceil(1.0 * L / k), (LL)floor(1.0 * R / k));
			l = max(l, ceil(L, k));
			r = min(r, floor(R, k));
		}
		else{
//			printf("case2: L=%lld R=%lld\n", (LL)ceil(1.0 * R / k), (LL)floor(1.0 * L / k));
			l = max(l, ceil(R, k));
			r = min(r, floor(L, k));
		}
	}
}
void work(LL rx, LL ry){
	for(int i = 1;i <= n; i++){			
//	 printf("i=%d x=%lld y=%lld k=%lld w=%lld\n", i, a[i].x, a[i].y, a[i].k, a[i].w);
	
		a[i].x = a[i].x - a[i].k * rx;
		a[i].y = a[i].y - a[i].k * ry;	 	
	}
//	printf("rx=%lld ry=%lld\n", rx, ry);
	a[n+1].x = rx; a[n+1].y = ry;
	tmp.clear();
	for(int i = 0;i <= n; i++){
		LL t = a[i+1].w - a[i].w;
		LL nx = a[i].x, ny = a[i].y;
		LL x = a[i+1].x, y = a[i+1].y;
//		printf("i=%d nx=%lld ny=%lld x=%lld y=%lld wi+1=%lld wi=%lld\n", i, nx, ny, x, y, a[i+1].w, a[i].w);
		memset(cnt, 0, sizeof(cnt));
		while(t--){
			if(nx < x){
				if(ny < y)cnt[3]++, nx++, ny++;
				else cnt[2]++, nx++;
			}
			else{
				if(ny < y)cnt[1]++, ny++;
				else cnt[0]++;
			}
		}
		for(int j = 0;j <= 3; j++)
			for(int k = 1;k <= cnt[j]; k++)tmp += S[j];
	}
	if(ans.empty() || ans > tmp)ans = tmp;
}
int main(){
//	freopen("robot.in", "r", stdin);
//	freopen("robot.out", "w", stdout);
	cin>>n>>loop;
	LL x, y, t;
	for(int i = 1;i <= n; i++){
		scanf("%lld%lld%lld", &t, &x, &y);
		if((x ^ y ^ t) & 1)fail();
		a[i].t = t; 
		a[i].x = (x + y + t) >> 1;
		a[i].y = (y - x + t) >> 1;
		a[i].k = t / loop;
		a[i].w = t % loop;
//		printf("i=%d x=%lld y=%lld\n", i, a[i].x, a[i].y);
	}
	sort(a + 1, a + 1 + n, cmp);
	a[n+1].k = -1; a[n+1].w = loop;
	for(int i = 0; i <= n; i++){
		LL k = a[i+1].k - a[i].k;
		LL w = a[i+1].w - a[i].w;
		update(lx, rx, k, w, a[i].x, a[i+1].x);
		update(ly, ry, k, w, a[i].y, a[i+1].y);		
//		printf("i=%d k=%lld w=%lld lx=%lld rx=%lld ly=%lld ry=%lld\n", i, k, w, lx, rx, ly, ry);

	}
//	puts("xbx");
	if(lx > rx || ly > ry)fail();
	memcpy(now, a, sizeof(now));
	work(lx, ly); 
	memcpy(a, now, sizeof(now));
	work(rx, ry);
//	printf("lx=%lld rx=%lld ly=%lld ry=%lld\n", lx, rx, ly, ry);
	cout<<ans<<endl;
	return 0;
}
/*
3 10
3 0 -3
5 -1 -2
17 -4 1
*/
