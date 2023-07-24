#include<bits/stdc++.h>
using namespace std;
const int N = 111;
#define P pair<int, int>
#define fs first
#define sc second
#define mk_p mk_pair
int f[N][N][2], n;
P seg[N];
int main(){
	cin>>n;
	int mi = 1e9;
	for(int i = 1;i <= n; i++){
		cin>>seg[i].fs>>seg[i].sc;
		mi = min(mi, seg[i].fs - seg[i].sc);
	}
	sort(seg + 1, seg + 1 + n);
	seg[0].fs = mi;
	memset(f, -127, sizeof f);
	f[0][0][0] = f[0][0][1] = 0;
	int ans = 0;
	for(int i = 0;i <= n; i++){
		for(int j = 0;j <= i; j++){
			for(int p = 0;p < 2; p++){
				ans = max(ans, f[i][j][p]);
				int l = seg[j].fs + seg[j].sc * p, pos = j, r = l, d = p;
				for(int k = i + 1;k <= n; k++){
					for(int q = 0;q < 2; q++){
						int now = seg[k].fs + seg[k].sc * q;
						if(r < now) r = now, d = q, pos = k;
						if(now <= l)continue;
						f[k][pos][d] = max(f[k][pos][d], min(now - l, seg[k].sc) + f[i][j][p] + r - now);
					}
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
