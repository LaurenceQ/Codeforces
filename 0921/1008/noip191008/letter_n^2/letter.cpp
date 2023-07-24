#include<bits/stdc++.h>
using namespace std;

const int N=5005,inf=0x3f3f3f3f;
int n,dp[2][6*N];
char s[N];

void upd(int &x,int y){x=x<y?x:y;}

int push(int st,int x)
{
	int sta=st/(n+1),len=st-sta*(n+1);
	if(!len)return x*(n+1)+1;
	if(len==1)return (sta*2+(x==0||(sta==0&&x==1)?0:1))*(n+1)+2;
	if(len==2)return sta*(n+1)+3;
	const int tr[6]={3,5,1,4,0,2};
	return tr[sta]*(n+1)+len+1;
}
int pop(int st)
{
	int sta=st/(n+1),len=st-sta*(n+1);
	if(len<=1)return 0;
	if(len==2)return (sta/2)*(n+1)+1;
	if(len==3)return sta*(n+1)+2;
	const int tr[6]={4,2,5,0,3,1};
	return tr[sta]*(n+1)+len-1;
}
int top(int st)
{
	int sta=st/(n+1),len=st-sta*(n+1);
	if(len==1)return sta;
	const int tr1[6]={1,2,0,2,0,1};
	if(len==2)return tr1[sta];
	const int tr2[6]={2,1,2,0,1,0};
	return tr2[sta];
}

int main()
{
	freopen("letter.in","r",stdin);
	freopen("letter.out","w",stdout);
	memset(dp,0x3f,sizeof dp);
	scanf("%s",s);
	n=strlen(s);
	vector<int> sta,nxt_sta;
	sta.push_back(0);
	dp[0][0]=0;
	for(int i=0;i<n;++i)
	{
		for(int st:sta)
		{
			int z=dp[i&1][st];dp[i&1][st]=inf;
			if(st&&top(st)==s[i]-'A')
			{
				if(dp[i+1&1][st]>i+1)nxt_sta.push_back(st);
				upd(dp[i+1&1][st],z);
				continue;
			}
			if(pop(st)&&top(pop(st))==s[i]-'A')
			{
				if(dp[i+1&1][pop(st)]>i+1)nxt_sta.push_back(pop(st));
				upd(dp[i+1&1][pop(st)],z);
				continue;
			}
			if(pop(pop(st)))
			{
				if(dp[i+1&1][pop(pop(st))]>i+1)nxt_sta.push_back(pop(pop(st)));
				upd(dp[i+1&1][pop(pop(st))],z);
			}
			if(dp[i+1&1][push(st,s[i]-'A')]>i+1)nxt_sta.push_back(push(st,s[i]-'A'));
			upd(dp[i+1&1][push(st,s[i]-'A')],z+1);
		}
		sta=nxt_sta,nxt_sta.clear();
	}
	int ans=n;
	for(int st:sta)upd(ans,dp[n&1][st]),dp[n&1][st]=inf;
	printf("%d\n",2*ans+n);
	return 0;
}
