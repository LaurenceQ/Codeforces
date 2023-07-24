#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	if(n == 1 || n == 2){
		puts("No");
		return 0;
	}
	if(n == 3){
		puts("Yes");
		puts("1 2");
		puts("2 3");
		puts("3 4");
		puts("4 5");
		puts("5 6");
		return 0;
	}
	int ma = 0;
	for(int i = 2;i <= n; i <<= 1){
		if(n >= i - 1)ma = i - 1;  
	}
	if(n - ma == 1){
		puts("No");
		return 0;
	}
	puts("Yes");
	for(int i = 1;i < ma; i++){
		printf("%d %d\n", i, i + 1);
		printf("%d %d\n", i + n, i + n + 1);
	}
	printf("%d %d\n", ma, n + 1);
	int now = ma + 1, sum = 0;
	for(int i = now;i <= n; i++)sum ^= i;
	if(sum == 0){
		for(int i = now;i < n; i++){
			printf("%d %d\n", i, i + 1);
			printf("%d %d\n", i + n, i + n + 1);
		}
		printf("%d %d\n", n, now + n);
		printf("%d %d\n", 1, n);
	}
	else if(sum == 1){
		for(int i = now;i < n; i++){
			printf("%d %d\n", i, i + 1);
			printf("%d %d\n", i + n, i + n + 1);
		}	
		printf("%d %d\n", n, 1);
		printf("%d %d\n", 1, n + now);	
	} 
	else {
		sum ^= n;
		int x = n ^ now;
		for(int i = now;i < n - 1; i++){
			printf("%d %d\n", i, i + 1);
			printf("%d %d\n", i + n, i + n + 1);
		}		
		if(sum == 0){
			printf("%d %d\n", n - 1, x + n - 1);
			printf("%d %d\n", x, now + n);
			printf("%d %d\n", n, now + n);
			printf("%d %d\n", x, n + n);
		}
		else {
			printf("%d %d\n", n - 1, x ^ 1);
			printf("%d %d\n", x, now + n);
			printf("%d %d\n", now + n, n);
			printf("%d %d\n", n + n, x);
		}
	}
	return 0;
}
