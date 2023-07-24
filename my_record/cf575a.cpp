#include<bits/stdc++.h>
using namespace std;
const int N = 5e4 + 11;
#define LL long long
#define ls (p << 1)
#define rs (p << 1 | 1)
int m, q;
LL K, s[N], f[N], mod;
struct ddd{
	LL w, bl, pos;
	int fl;
	ddd (LL _w = 0, LL _bl = 0, LL _pos = 0, int _fl = 0){
		w = _w; bl = _bl; pos = _pos; fl = _fl;
	}
}Q[N<<1];
inline LL M(LL x, LL y){
    return x * y % mod;
}
inline LL A(LL x, LL y){
    return x + y - (x + y >= mod ? mod : 0);
}
struct mat{
    LL a[2][2];
    void clear(){
        memset(a, 0, sizeof(a));
    }
    void init(){
    	clear();
    	a[0][0] = a[1][1] = 1;
	}
    mat operator * (mat b){
        mat ans;
        ans.clear();
        for(int i = 0;i < 2; i++){
            for(int j = 0;j < 2; j++){
                for(int k = 0;k < 2; k++){
                    ans.a[i][j] = A(ans.a[i][j], M(a[i][k], b.a[k][j]));
                }
            }
        }
        return ans;
    }
    void print(){
    	printf("%d %d \n%d %d\n", a[0][0], a[0][1], a[1][0], a[1][1]);
	}
}base, One;
struct seg{
	mat t[N<<2];
	void build(int p, int l, int r){
		if(l == r){
			t[p].clear();
			t[p].a[0][0] = s[l];
			t[p].a[1][0] = s[(l-1+m)%m];
			t[p].a[0][1] = 1;
			return ;
		}
		int mid = l + r >> 1;
		build(ls, l, mid); build(rs, mid + 1, r);
		t[p] = t[ls] * t[rs];
	}
	void modify(int p, int l, int r, int x, int fl, LL v){
		if(l > x || r < x)return ;
		if(l == x && r == l){
			t[p].a[fl][0] = v;
			return ;
		}
		int mid = l + r >> 1;
		modify(ls, l, mid, x, fl, v);
		modify(rs, mid + 1, r, x, fl, v);
		t[p] = t[ls] * t[rs];
	}
	mat query(int p, int l, int r, int x, int y){
		if(l > y || r < x){
			return One;
		}
		if(l >= x && r <= y)return t[p];
		int mid = l + r >> 1;
		return query(ls, l, mid, x, y) * query(rs, mid + 1, r, x, y);
	}	
}T;
bool cmp(ddd x, ddd y){
	return x.bl == y.bl ? x.pos < y.pos : x.bl < y.bl;
}
mat ksm(mat base, LL x){
	mat ans = One;
	while(x){
		if(x & 1)ans = ans * base;
		base = base * base;
		x >>= 1;
	}
	return ans;
}
int main(){
//	freopen("a.in", "r", stdin);
    cin>>K>>mod>>m;
    if(mod == 1){
    	puts("0");
    	return 0;
	}
    for(int i = 0;i < m; i++){
    	scanf("%lld", &s[i]);
	}
	f[1] = 1;
	for(int i = 2;i <= m; i++)f[i] = A(M(f[i-1], s[i-1]), M(f[i-2], s[i-2]));
	if(K <= m){
		printf("%lld\n", f[K]);
		return 0;
	}
	T.build(1, 0, m - 1);
	One.init();
	int tot = 0;
	LL v, pos;
	cin>>q;
	for(int i = 1;i <= q; i++){
		scanf("%lld%lld", &pos, &v);
		if(pos >= K)continue;
		Q[++tot] = ddd(v, pos / m, pos % m, 0);
		if(pos + 1 < K)Q[++tot] = ddd(v, (pos + 1) / m, (pos + 1) % m, 1);
	}
	sort(Q + 1, Q + 1 + tot, cmp);
	if(Q[tot].pos + Q[tot].bl * m != K - 1)Q[++tot] = ddd(s[(K-1)%m], (K - 1) / m, (K - 1) % m, 0);
	mat now;
	base = T.t[1];
	now.init();
	for(int l = 1, r = 1;l <= tot && r <= tot; l = r + 1, r = l){
		now = now * ksm(base, Q[l].bl - 1 - Q[l-1].bl);
		T.modify(1, 0, m - 1, Q[l].pos, Q[l].fl, Q[l].w);
		while(Q[r+1].bl == Q[l].bl && r + 1 <= tot){
			r++;
			T.modify(1, 0, m - 1, Q[r].pos, Q[r].fl, Q[r].w);
		}
		mat tmp = T.query(1, 0, m - 1, 0, Q[r].pos + 1LL * Q[r].bl * m == K - 1 ? (K - 1) % m : m - 1);	
		now = now * tmp;
		for(int i = l;i <= r; i++){
			T.modify(1, 0, m - 1, Q[i].pos, Q[i].fl, s[(Q[i].pos-Q[i].fl+m)%m]);
		}
	}
	LL ans = A(M(f[m], now.a[0][0]), M(f[m-1], now.a[1][0]));
	cout<<ans<<endl;
    return 0;
}
