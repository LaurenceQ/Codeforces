#include<bits/stdc++.h>
using namespace std;

int T,n,ans;
string s;
unordered_map<string,int> mem[5005];

int dfs(int i,const string &st)
{
	if(i==n)return 0;
	if(mem[i].count(st))return mem[i][st];
	if(st.size()>=1&&st.back()==s[i])return mem[i][st]=dfs(i+1,st);
	if(st.size()>=2&&st[(int)st.size()-2]==s[i])
	{
		string tmp=st;
		tmp.pop_back();
		return mem[i][st]=dfs(i+1,tmp);
	}
	int ans=1<<30;
	if(st.size()>=3)
	{
		string tmp=st;
		while(tmp.back()!=s[i])tmp.pop_back();
		ans=dfs(i+1,tmp);
	}
	ans=min(ans,dfs(i+1,st+s[i])+1);
	return mem[i][st]=ans;
}

int main()
{
	freopen("letter.in","r",stdin);
	freopen("letter.out","w",stdout);
	cin>>s,n=s.size();
	for(int i=0;i<n;++i)mem[i].clear();
	cout<<2*dfs(0,"")+n<<endl;
	return 0;
}
