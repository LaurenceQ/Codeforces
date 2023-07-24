#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int read()
{
	int ans=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') ans=ans*10+ch-'0',ch=getchar();
	return ans; 
}
struct node{int u,v,c;};
int n,now[500010],u[500010],v[500010],c[500010],fa[500010],col[500010],flag[500010];
vector<node>tree[5010],Tree[5010],Vec,Vec1;
char ch[3];
int find(int x)
{
	if (fa[x]==x) return x;
	int oldfa=fa[x];
	fa[x]=find(fa[x]);
	col[x]^=col[oldfa];
	return fa[x];
}
bool cmp(node a,node b)
{
	return a.c<b.c;
}
void insert(int l,int r,int t,int x,int y,int u,int v,int c)
{
	if (l==x&&y==r) 
	{
		tree[t].push_back((node){u,v,c});
		return;
	}
	int mid=(l+r)>>1;
	if (y<=mid) insert(l,mid,t<<1,x,y,u,v,c);
	else if (x>mid) insert(mid+1,r,t<<1|1,x,y,u,v,c);
	else insert(l,mid,t<<1,x,mid,u,v,c),insert(mid+1,r,t<<1|1,mid+1,y,u,v,c);
}
void dfs(int t,int l,int r)
{
	sort(tree[t].begin(),tree[t].end(),cmp);
	for (int i=1;i<=n;i++) fa[i]=i,col[i]=0; 
	for (int i=tree[t].size()-1;i>=0;i--)
	{
		int u=tree[t][i].u,v=tree[t][i].v,c=tree[t][i].c;
		int x=find(u),y=find(v);
		if (x!=y)
		{
			col[x]=col[u]^col[v]^1,fa[x]=y;
			Tree[t].push_back((node){u,v,c});
		}
		else
		{
			if (col[u]==col[v]) 
			{
				Tree[t].push_back((node){u,v,c});
				break;
			}
		}
	}
	if (l==r) return;
	int mid=(l+r)>>1;
	dfs(t<<1,l,mid);
	dfs(t<<1|1,mid+1,r);
}
int query(int l,int r,int t,int pos,int ans)
{
	for (int i=1;i<=n;i++) fa[i]=i,col[i]=0;
	int ll=0,rr=0;
	int V1size=Vec.size(),V2size=Tree[t].size();
	Vec1.clear();
	while (ll<V1size&&rr<V2size)
	{
		if (Vec[ll].c>Tree[t][rr].c) Vec1.push_back((node){Vec[ll].u,Vec[ll].v,Vec[ll].c}),ll++;
		else Vec1.push_back((node){Tree[t][rr].u,Tree[t][rr].v,Tree[t][rr].c}),rr++;
	}
	while (ll<V1size) Vec1.push_back((node){Vec[ll].u,Vec[ll].v,Vec[ll].c}),ll++;
	while (rr<V2size) Vec1.push_back((node){Tree[t][rr].u,Tree[t][rr].v,Tree[t][rr].c}),rr++;
	Vec.clear();
	for (int i=0;i<(int)Vec1.size();i++)
	{
		int u=Vec1[i].u,v=Vec1[i].v,c=Vec1[i].c;
		int x=find(u),y=find(v);
		if (x!=y)
		{
			col[x]=col[u]^col[v]^1,fa[x]=y;
			Vec.push_back((node){u,v,c});
		}
		else
		{
			if (col[u]==col[v])
			{
				Vec.push_back((node){u,v,c});
				ans=c;
				break;
			}
		}
	}
	if (l==r) return ans;
	int mid=(l+r)>>1;
	if (pos<=mid) return query(l,mid,t<<1,pos,0);
	return query(mid+1,r,t<<1|1,pos,0);
}
int main()
{
	freopen("redgreen.in","r",stdin);
	freopen("redgreen.out","w",stdout);
	int m,q;
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<=m;i++)
	{
		u[i]=read(),v[i]=read(),c[i]=read(),now[i]=1;
	}
	int cnt=m,qcnt=0;
	for (int i=1;i<=q;i++)
	{
		scanf("%s",ch);
		if (ch[0]=='A') u[++cnt]=read(),v[cnt]=read(),c[cnt]=read(),now[cnt]=qcnt+1;
		if (ch[0]=='D')
		{
			int xx=read();
			if (qcnt>=now[xx])
				insert(0,1010,1,now[xx],qcnt,u[xx],v[xx],c[xx]);
			flag[xx]=1;
		}
		if (ch[0]=='Q') qcnt++;
	}
	for (int i=1;i<=cnt;i++)
		if (!flag[i]&&now[i]<=qcnt) 
			insert(0,1010,1,now[i],qcnt,u[i],v[i],c[i]);
	dfs(1,0,1010);
	for (int i=1;i<=qcnt;i++)
	{
		Vec.clear();
		printf("%d\n",query(0,1010,1,i,0));
	}
	return 0;
}
