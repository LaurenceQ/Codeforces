#include<bits/stdc++.h>
using namespace std;

const int N=1005;
int n,cnt[N][N],A[N];
bool now[N];

bool dfs(int i)
{
	if(i==n)return true;
	int x=n-A[i];
	for(int j=1;j<i;++j)if(A[j]>A[i])--x;
	int y=i-1;
	bool flag=false;
	for(int j=1;j<=n;++j)
	{
		if(now[j])
		{
			if(j!=A[i])--y;
			continue;
		}
		if(cnt[i][A[i]]==x+(j-1==A[i]?i-y:0)&&cnt[i][A[i]-1]==n-i-x+(j+1==A[i]?y+1:0)&&cnt[i][j]==y+(j<A[i])+(j==A[i]-1?n-i-x:0)&&cnt[i][j-1]==i-1-y+(j>A[i])+(j-1==A[i]?x:0))
		{
			now[A[i+1]=j]=1;
			if(dfs(i+1))return true;
			now[j]=0;
		}
	}
	return false;
}

int main()
{
	freopen("puzzle.in","r",stdin);
	freopen("puzzle.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1,x;j<n;++j)
			scanf("%d",&x),++cnt[j][x];
	for(int i=1;i<=n;++i)
	{
		int cnt1=cnt[1][i],cnt2=cnt[1][i-1];
		if(cnt1>=n-i&&cnt2>=i-1){
			now[A[1]=i]=1;
			if(dfs(1))
			{
				for(int j=1;j<=n;++j)printf("%d ",A[j]);
				return 0;
			}
			now[A[1]=i]=0;
		}
	}
}
