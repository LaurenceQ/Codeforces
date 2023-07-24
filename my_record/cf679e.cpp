#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 11;
#define LL long long 
#define ls (p << 1)
#define rs (p << 1 | 1)
int n;
LL mi[15], a[N];
struct node{
	LL val, tag, mn;
	bool same;
	node (){
		val = tag = mn = same = 0;
	}
	node(LL vall, LL tagg, LL mnn, bool samee){
		val = vall; tag = tagg; mn = mnn; same = samee;
	}
 	node operator + (node b){
 		node tmp;
 		tmp = node();
 		tmp.mn = min(b.mn, mn);
 		if(b.same && same && val == b.val && b.mn == mn){
 			tmp.same = 1; tmp.val = val;	
		}
		return tmp;
	} 
};
struct seg{
	node t[N<<2];
	bool flag;
	node get(LL v){
		LL mn = 0;
		for(int i = 0;i <= 11; i++){
			if(mi[i] >= v){
				mn = mi[i] - v;
				break;
			}
		}
		return node(v, 0, mn, 1); 
	}
	void add_tag(int p, LL v){
		t[p].val += v;
		t[p].mn -= v;
		t[p].tag += v;
	}
	void push_down(int p){
		if(t[p].same){
			t[ls] = t[rs] = t[p];
			return ;
		}
		if(!t[p].tag)return ;
		add_tag(ls, t[p].tag);
		add_tag(rs, t[p].tag);
		t[p].tag = 0;
	}
	void build(int p, int l, int r){
		if(l == r){
			t[p] = get(a[l]);
			return ;
		}
		int mid = l + r >> 1;
		build(ls, l, mid); build(rs, mid + 1, r);
		t[p] = t[ls] + t[rs];
	}
	void modify(int p, int l, int r, int x, int y, LL v){
		if(l > y || r < x)return ;
		if(l >= x && r <= y){
			t[p] = get(v);
			return ;
		}
		push_down(p);
		int mid = l + r >> 1;
		modify(ls, l, mid, x, y, v); modify(rs, mid + 1, r, x, y, v);
		t[p] = t[ls] + t[rs];
	}
	void add(int p, int l, int r, int x, int y, int v){
		if(l > y || r < x)return ;
		if(l >= x && r <= y && t[p].mn >= v){
			add_tag(p, v);
			if(t[p].mn == 0)flag = 1;
			return ;
		}
		if(l >= x && r <= y && t[p].same){
			t[p] = get(t[p].val + v);
			if(t[p].mn == 0)flag = 1;
			return ;
		}
		push_down(p);
		int mid = l + r >> 1;
		add(ls, l, mid, x, y, v); add(rs, mid + 1, r, x, y, v);
		t[p] = t[ls] + t[rs];
	}
	LL query(int p, int l, int r, int x){
		if(l == r && l == x){
			return t[p].val;
		}
		push_down(p);
		int mid = l + r >> 1;
		if(mid >= x)return query(ls, l, mid, x);
		else if(mid + 1 <= x)return query(rs, mid + 1, r, x);
	} 
}T;
int main(){
	int q;
	cin>>n>>q;
	mi[0] = 1;
	for(int i = 1;i <= 11; i++){
		mi[i] = mi[i-1] * 42;
	}
	for(int i = 1;i <= n; i++){
		scanf("%d", &a[i]);
	}
	T.build(1, 1, n);
	int fl, a, b, x;
	while(q--){
		scanf("%d", &fl);
		if(fl == 1){
			scanf("%d", &x);
			printf("%lld\n", T.query(1, 1, n, x));
		}
		else{
			scanf("%d%d%d", &a, &b, &x);
			if(fl == 2){
				T.modify(1, 1, n, a, b, x);
			}
			else{
				do{
					T.flag = 0;
					T.add(1, 1, n, a, b, x);
				}while(T.flag);
			}
		}
//		printf("a5=%lld\n", T.query(1, 1, n, 5));
	}
	
	return 0;
}
