#include<bits/stdc++.h>
using namespace std;
const int N = 111;
int n, m, mod;
int fa[N*N], tot[2], num[N*N];
char s[N][N];
inline int A(int x, int y){
	return (x + y) % mod;
}
inline int M(int x, int y){
	return 1LL * x * y % mod;
}
int ksm(int base, int x){
	int ans = 1;
	while(x){
		if(x & 1)ans = M(ans, base);
		base = M(base, base);
		x >>= 1;
	}
	return ans;
}
struct mat{
	int a[N*5][N*5];
	void add(int x, int y){
		a[x][x]++;
		a[y][y]++;
		a[x][y] = A(a[x][y], mod - 1);
		a[y][x] = A(a[y][x], mod - 1);
	}
	int cal(int n){
		bool fl = 0;
		int ans = 1;
		for(int i = 1;i <= n; i++){
			if(a[i][i] == 0){
				int p = 0;
				for(int j = i + 1;j <= n; j++){
					if(a[j][i] != 0){
						p = j;
						break;
					}
				}
				if(!p)return 0;
				swap(a[i], a[p]);
				fl ^= 1;
			}
			ans = M(ans, a[i][i]);
			int inv = ksm(a[i][i], mod - 2);
			for(int j = i + 1;j <= n; j++){
				int tmp = a[j][i];
				for(int k = i;k <= n; k++)a[j][k] = A(a[j][k], mod - M(tmp, M(inv, a[i][k])));
			}
		}
		return fl ? mod - ans : ans;
	}
}G[2];
int id(int x, int y){
	return x * (m + 1) + y + 1;
}
int find(int x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y){
	int fx = find(x), fy = find(y);
	fa[fx] = fy;
}
int main(){
	cin>>n>>m>>mod;
	for(int i = 0;i <= n; i++){
		for(int j = 0;j <= m; j++)fa[id(i, j)] = id(i, j);
	}
	for(int i = 1;i <= n; i++){
		scanf("%s", s[i] + 1);
		for(int j = 1;j <= m; j++){
			if(s[i][j] == '/'){
				merge(id(i - 1, j), id(i, j - 1));
//				printf("i=%d j=%d\n", i, j);
			}
			if(s[i][j] == '\\'){
				merge(id(i - 1, j - 1), id(i, j));
//				puts("XBX");
			}
		}
	}
	for(int i = 0;i <= n; i++){
		for(int j = 0;j <= m; j++){
			if(fa[id(i, j)] == id(i, j)){
				tot[(i+j)&1]++;
				num[id(i, j)] = tot[(i+j)&1];
//				printf("case:%d i=%d j=%d\n", (i + j) & 1, i, j);
			}
//			printf("i=%d j=%d id=%d fa=%d\n", i, j, id(i, j), find(id(i, j)));
		}
	}
	for(int i = 1;i <= n; i++){
		for(int j = 1;j <= m; j++){
			if(s[i][j] == '*'){
				G[(i+j)&1].add(num[find(id(i - 1, j - 1))], num[find(id(i, j))]);
				G[(i+j-1)&1].add(num[find(id(i - 1, j))], num[find(id(i, j - 1))]);
			}
		}
	}
//	printf("tot0=%d tot1=%d\n", tot[0], tot[1]);
	printf("%d\n", A(G[0].cal(tot[0] - 1), G[1].cal(tot[1] - 1)));
	return 0;
}
