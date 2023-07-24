#include<cstdio>
#include<cstring>

const int N=5005;
int n,dp[2][6*N];
char s[N];

void upd(int &x,int y){x=x<y?x:y;}

int push(int sta,int len,int x)
{
	if(!len)return x*(n+1)+1;
	if(len==1)return (sta*2+(x==0||(sta==0&&x==1)?0:1))*(n+1)+2;
	if(len==2)return sta*(n+1)+3;
	const int tr[6]={3,5,1,4,0,2};
	return tr[sta]*(n+1)+len+1;
}
int pop(int st)
{
	int sta=st/(n+1),len=st-sta*(n+1);
	if(len==1)return 0;
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
	scanf("%s",s),n=strlen(s);
	memset(dp[0],0x3f,sizeof dp[0]);
	dp[0][0]=0;
	for(int i=0;i<n;++i)
	{
		memset(dp[i+1&1],0x3f,sizeof dp[i+1&1]);
		for(int sta=0;sta<6;++sta)
			for(int len=(sta>=3?2:sta>=1);len<=i;++len)
			{
				int st=sta*(n+1)+len;
				// if(dp[i&1][st]>i)continue;
				if(st&&top(st)==s[i]-'A'){upd(dp[i+1&1][st],dp[i&1][st]);continue;}
				if(len>=2&&top(pop(st))==s[i]-'A'){upd(dp[i+1&1][pop(st)],dp[i&1][st]);continue;}
				if(len>=3)upd(dp[i+1&1][pop(pop(st))],dp[i&1][st]);
				upd(dp[i+1&1][push(sta,len,s[i]-'A')],dp[i&1][st]+1);
			}
	}
	int ans=n;
	for(int st=0;st<6*(n+1);++st)
		upd(ans,dp[n&1][st]);
	printf("%d\n",2*ans+n);
	return 0;
}
