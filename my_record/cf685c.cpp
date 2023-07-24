#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 11;
#define LL long long
int n;
LL mi[11], ma[11];
struct node{
	LL x, y, z;
	node (LL _x = 0, LL _y = 0, LL _z = 0){
		x = _x; y = _y; z = _z;
	}
}nd[N], ans;
bool get(LL K, LL r){
	memset(mi, -127, sizeof(mi));
	memset(ma, 127, sizeof ma);
	for(int i = 1;i <= n; i++){
		LL x = nd[i].x, y = nd[i].y, z = nd[i].z;
		mi[1] = max(mi[1], (x + y + z - K - 3 * r + 1) >> 1); ma[1] = min(ma[1], (x + y + z + K - 3 * r) >> 1);
		mi[2] = max(mi[2], (z + y - x - K - r + 1) >> 1); ma[2] = min(ma[2], (K - x + y + z - r) >> 1);
		mi[3] = max(mi[3], (x + z - K - y - r + 1) >> 1); ma[3] = min(ma[3], (K + x + z - y - r) >> 1);
		mi[4] = max(mi[4], (x + y - z - K - r + 1) >> 1); ma[4] = min(ma[4], (K + x + y - z - r) >> 1);
	}
	for(int i = 1;i <= 4; i++){
		if(mi[i] > ma[i])return 0;
	}
	LL a = mi[2], b = mi[3], c = mi[4];
	if(a + b + c > ma[1])return 0;
	LL res = mi[1] - (a + b + c);
	if(res > 0){
		LL add = min(res, ma[2] - a);
		res -= add; a += add;
	}
	if(res > 0){
		LL add = min(res, ma[3] - b);
		res -= add; b += add;
	}
	if(res > 0){
		LL add = min(res, ma[4] - c);
		res -= add; c += add;
	}
	if(res > 0)return 0;
	ans = node(b + c + r, a + c + r, a + b + r);
	return 1;
}

void work(){
	scanf("%d", &n);
	LL x, y, z;
	for(int i = 1;i <= n; i++){
		scanf("%lld%lld%lld", &x, &y, &z);
		nd[i] = node(x, y, z);
	}
	LL l = 0, r = 6e18;
	while(l <= r){
		LL mid = l + r >> 1;	
		if(get(mid, 1) || get(mid, 0))r = mid - 1;
		else l = mid + 1;
	
	}
	printf("%lld %lld %lld\n", ans.x, ans.y, ans.z);
}
int main(){
	int T;
	cin>>T;
	while(T--) work();
	return 0;
}
