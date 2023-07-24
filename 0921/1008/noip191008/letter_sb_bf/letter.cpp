#include<bits/stdc++.h>
using namespace std;

int n,ans,cnt;
char s[5005],st[5005];

void dfs(int i,int now,int top)
{
	if(now>=ans)return;
	if(i>n)
	{
		ans=now;
		return;
	}
	if(st[top]==s[i])
	{
		dfs(i+1,now,top);
		return;
	}
	if(top)dfs(i,now,top-1);
	char c=st[top+1];st[top+1]=s[i],dfs(i+1,now+1,top+1),st[top+1]=c;
}

int main()
{
	freopen("letter.in","r",stdin);
	freopen("letter.out","w",stdout);
	scanf("%s",s+1),n=strlen(s+1);
	ans=1<<30,cnt=0,dfs(1,0,0);
	printf("%d\n",2*ans+n);
	return 0;
}
