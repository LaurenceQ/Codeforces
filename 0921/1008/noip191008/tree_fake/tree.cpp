#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll lim=(ll)1e18;

vector<int> e;
ll K,fac[20];
unordered_map<ll,vector<int>> all;
vector<pair<int,int>> ans;

void dfs(int i,ll K)
{
	if(i==20)
	{
		if(!all.count(K))all[K]=e;
		return;
	}
	for(e[i]=0;;++e[i])
	{
		dfs(i+1,K);
		if(K>lim/fac[i])break;
		K*=fac[i];
	}
}

int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	for(int i=fac[0]=1;i<20;++i)fac[i]=fac[i-1]*i;
	e.resize(20),dfs(2,1);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld",&K);
		if(K==1){puts("1");continue;}
		if(!all.count(K)){puts("-1");continue;}
		e=all[K];
		vector<int> fa{-1,0};
		int mx=0,rt=1,cnt=0;
		for(int i=2;i<=19;++i)
		{
			for(int a=0;a<e[i];++a)
			{
			//	if(a==0||a==e[i]/2+1)
			//	{
			//		mx=max(mx,cnt),cnt=0;
			//		rt=1;
			//	}
				fa.push_back(rt);
				rt=(int)fa.size()-1;
				for(int b=0;b<i;++b)fa.push_back(rt);
				cnt+=i+1;
			}
			mx=max(mx,cnt);
		}
		rt=1;
		for(int i=(int)fa.size();i<=min(200,2*mx+1);++i)fa.push_back(rt),rt=(int)fa.size()-1;
		printf("%d\n",(int)fa.size()-1);
		for(int i=2;i<=(int)fa.size()-1;++i)printf("%d %d\n",fa[i],i);
	}
}
