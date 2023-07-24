#include<bits/stdc++.h>
using namespace std;
#define Myxx Axyx
#define Myxy Axyy
const int N = 5e3 + 11;
const int M =  1e5 + 11;
int n, q;
struct ddd{
	int dir, x, y, len;
	ddd (int _dir = 0, int _x = 0, int _y = 0, int _len = 0){
		dir = _dir; x = _x; y = _y; len = _len;
	}
}qst[M];
struct bit1{
	int t[N<<1];
	void add(int fl, int l, int r, int v){
		l += fl * (n + 1); r += fl * (n + 1);
//		if(fl)printf("l=%d r=%d\n", l, r);	
		add(r + 1, -v); add(l, v);
	}
	void add(int x, int v){
		for(;x <= n + n + 2;x += -x & x){
			t[x] += v;
		}
	}
	int query(int fl, int x){
		int ans = 0;
		x += (n + 1) * fl;
//		if(fl)printf("x=%d\n", x);
		for(;x;x -= -x & x)ans += t[x];
		return ans;
	}
}Axy, Myx;
struct bit2{
	int t[N<<1][N];
	void clear(){
		memset(t, 0, sizeof(t));
	}
	void add(int fl, int x1, int y1, int x2, int y2, int val){
		x1 += fl * (n + 1); 
		x2 += fl * (n + 1);
//		if(fl)printf("x1=%d y1=%d x2=%d y2=%d\n", x1, y1, x2, y2);
		add(x2, y2, val);
		add(x1 - 1, y2, -val);
		add(x2, y1 - 1, -val);
		add(x1 - 1, y1 - 1, val);
	}
	void add(int x, int y, int v){
		for(int xx = x;xx;xx -= -xx & xx){
			for(int yy = y;yy;yy -= -yy & yy){
				t[xx][yy] += v;
			}
		}
	}
	int query(int fl, int x, int y){
		x += (n + 1) * fl;
//		if(fl)printf("x=%d y=%d\n", x, y);
		int ans = 0;
		for(int xx = x;xx <= n + n + 1; xx += -xx & xx){
			for(int yy = y;yy <= n + 1; yy += -yy & yy){
				ans += t[xx][yy];
			}
		}
		return ans;
	}
}Axyx, Axyy;
int main(){
	cin>>n>>q;
	int tp, dir, x, y, len;
	for(int i = 1;i <= q; i++){
		scanf("%d", &tp);
		if(tp == 1){
			scanf("%d%d%d%d", &dir, &x, &y, &len);
			qst[i] = ddd(dir, x, y, len);
		}
		else{
			scanf("%d%d", &x, &y);
//			int ans = Axy.query(0, x + y) + Myx.query(x + y) + Axyx.query(x + y, x) + Axyy.query(x + y, y) + Myxx.query(y - x, x) + Myxy.query(y - x, y);
			qst[i] = ddd(0, x, y, 0);
		}
	}
	for(int i = 1;i <= q; i++){
		dir = qst[i].dir, x = qst[i].x, y = qst[i].y; len = qst[i].len;
		if(dir == 1){
			Axy.add(0, x + y, x + y + len, 1);
			Axyx.add(0, x + y, 1, x + y + len, x - 1, -1);
			Axyy.add(0, x + y, 1, x + y + len, y - 1, -1);
		}			
		if(dir == 4){
			Axy.add(0, x + y - len, x + y, 1);
			Axyx.add(0, x + y - len, x + 1, x + y, n, -1);
			Axyy.add(0, x + y - len, y + 1, x + y, n, -1);
		}
		if(dir == 0){
			qst[i].len = Axy.query(0, x + y) + Axyx.query(0, x + y, x) + Axyy.query(0, x + y, y);
//			printf("i=%d ans=%d\n", i, qst[i].len);
		}
	}
	Axyx.clear(); Axyy.clear(); 
	for(int i = 1;i <= q; i++){
		dir = qst[i].dir, x = qst[i].x, y = qst[i].y; len = qst[i].len;
		if(dir == 2){
			Myx.add(1, y - x - len, y - x, 1);
			Myxx.add(1, y - x - len, 1, y - x, x - 1, -1);
			Myxy.add(1, y - x - len, y + 1, y - x, n, -1);
		}
		if(dir == 3){
			Myx.add(1, y - x, y - x + len, 1);
			Myxx.add(1, y - x, x + 1, y - x + len, n, -1);
			Myxy.add(1, y - x, 1, y - x + len, y - 1, -1);
		}
		if(dir == 0){
			qst[i].len += Myx.query(1, y - x) + Myxx.query(1, y - x, x) + Myxy.query(1, y - x, y);
//			printf("x=%d y=%d y-x=%d\n", x, y, y - x);
			printf("%d\n", qst[i].len);
		}			
//		printf("i=%d y-x-len=%d y-x=%d Myx=%d Myxx.q=%d Myxy.q=%d\n", i, y - x - len, y - x, Myx.query(1, -5), Myxx.query(1, -5, 9), Myxy.query(1, -5, 4));

	}
	return 0;
}


