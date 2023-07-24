#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e5 + 11;
struct ddd{
	int pos, op, id;
	LL v, w;
}Q1[N], Q2[N], Q3[N], Q[N];
int n, m, K;
int cnt1, cnt2, cnt3, cnt;
LL a[N];
bool cmp1(ddd a, ddd b){
	return a.id == b.id ? a.v > b.v : a.id < b.id;
}
bool cmp3(ddd a, ddd b){
	return 1.0 * a.v * b.w - 1.0 * a.w * b.v > 1e-18;
}
bool cmp4(ddd a, ddd b){
	return a.op < b.op;
}
int main(){
	cin>>K>>n>>m;
	for(int i = 1;i <= K; i++)scanf("%lld\n", &a[i]);
	int op, id, b;
	for(int i = 1;i <= n; i++){
		scanf("%d%d%d", &op, &id, &b);
		if(op == 1 && b > a[id]) Q1[++cnt1] = (ddd){i, op, id, b, 1};
		if(op == 2)Q2[++cnt2] = (ddd){i, op, id, b, 1};
		if(op == 3)Q3[++cnt3] = (ddd){i, op, id, b, 1};
	}
	sort(Q1 + 1, Q1 + 1 + cnt1, cmp1);
	int tot = 0;
	for(int i = 1;i <= cnt1; i++){
		if(Q1[i].id == Q1[i-1].id)continue;
		Q1[++tot] = Q1[i];
	}
	for(int i = 1;i <= tot; i++){
		Q2[++cnt2] = Q1[i];
		Q2[cnt2].v = Q2[cnt2].v - a[Q2[cnt2].id];
	}
	sort(Q2 + 1, Q2 + 1 + cnt2, cmp1);
	LL sum = 0;
	for(int i = 1;i <= cnt2; i++){
		if(Q2[i].id != Q2[i-1].id) sum = a[Q2[i].id];
		Q2[i].w = sum; 
		sum += Q2[i].v;
	}
	for(int i = 1;i <= cnt3; i++)Q3[i].v--;
	for(int i = 1;i <= cnt2; i++)Q3[++cnt3] = Q2[i];
	sort(Q3 + 1, Q3 + 1 + cnt3, cmp3);
	cnt = min(cnt3, m);
	for(int i = 1;i <= cnt;  i++){
		Q[i] = Q3[i];
	}
	sort(Q + 1, Q + 1 + cnt, cmp4);
	cout<<cnt<<endl;
	for(int i = 1;i <= cnt; i++){
		printf("%d ", Q[i].pos);
	}
	puts("");
	return 0;
}
