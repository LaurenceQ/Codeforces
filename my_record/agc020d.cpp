#include<bits/stdc++.h>
using namespace std;
int T, k, n, a, b, c, d;
int main(){
	cin>>T;
	while(T--){
		cin>>a>>b>>c>>d;
		n = a + b;
		int l = 0, r = n, pos = n;
		k = (max(a, b) - 1) / (min(a, b) + 1) + 1;
		while(l <= r){
			int mid = l + r >> 1;
			int A = a - mid / (k + 1) * k - mid % (k + 1), B = b - mid / (k + 1);
			if(B <= 1LL * k * A)l = mid + 1;
			else r = mid - 1, pos = mid;
		}
//		printf("pos=%d\n", pos);
		int A = a - pos / (k + 1) * k - pos % (k + 1), B = b - pos / (k + 1), tmp = l + B - k * A + 1;
		for(int i = c;i <= min(d, pos); i++)putchar(i % (k + 1) ? 'A' : 'B');
		for(int i = max(pos + 1, c);i <= d; i++)putchar((i - tmp) % (k + 1) ? 'B' : 'A');
		puts("");
	}
	return 0;
}
