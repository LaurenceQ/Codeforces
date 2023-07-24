#include<bits/stdc++.h>
using namespace std;
const int mod = 100 + 1;
#define P pair<int, int>
#define fs first
#define sc second
const int modd = 1e9;
bool mark[mod + 11]; 
map<P, int> mp;
int main(){
	freopen("a.in", "w", stdout);
	int n = 90000, q = 90993;
	srand(time(0));
	printf("%d %d\n", n, q);
	int x, y;
	for(int i = 1;i <= q; i++){
		do{
			x = rand() % n + 1;
			y = rand() % n + 1;
			if(x > y)swap(x, y);
		}while(mp[P(x, y)]);
		mp[P(x, y)] = 1;
		printf("%d %d\n", x, y);
	}

	return 0;
}
