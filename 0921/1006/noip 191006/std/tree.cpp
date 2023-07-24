#include<bits/stdc++.h>
using namespace std;
const int MAX_N=5+1e5,MOD=998244353;
struct Graph{
	struct Edge{ int to,nxt; }edge[MAX_N*2];
	int head[MAX_N],top;
	Graph(){memset(head,-1,sizeof(head)),top=-1;}
	inline void add(int x,int y){
		edge[++top]=(Edge){y,head[x]};
		head[x]=top;
	}
}G;
inline int fpow(int x,int n,int ret=1){
	for(;n;n>>=1,x=1ll*x*x%MOD)
		n&1?ret=1ll*ret*x%MOD:0;
	return ret;
}
inline int mo(int x){ return x>=MOD?x-MOD:x; }
inline int mo2(int x){ return x<0?x+MOD:x; }
struct Key{ 
	int x[4];
	inline Key operator*(int t){
		return (Key){{int(1ll*x[0]*t%MOD),int(1ll*x[1]*t%MOD)
			,int(1ll*x[2]*t%MOD),int(1ll*x[3]*t%MOD)}};
	}
	inline Key operator+(Key b){
		return (Key){{mo(x[0]+b.x[0]),mo(x[1]+b.x[1])
			,mo(x[2]+b.x[2]),mo(x[3]+b.x[3])}};
	}
	inline Key operator-(Key b){
		return (Key){{mo2(x[0]-b.x[0]),mo2(x[1]-b.x[1])
			,mo2(x[2]-b.x[2]),mo2(x[3]-b.x[3])}};
	}
};
Key f[MAX_N];
int cnt[MAX_N],fa[MAX_N];
bool vis[MAX_N];
void dfs1(int x,int pre){
	cnt[x]=0,fa[x]=pre;
	for(int j=G.head[x];~j;j=G.edge[j].nxt){
		int y=G.edge[j].to;
		if(y!=pre){
			dfs1(y,x);
			++cnt[x];
		}
	}
}
void dfs2(int x,int pre){
	Key p=(Key){0,0,0,0};
	f[x].x[3]=1;
	int scnt=cnt[x]+1;
	if(fa[x]!=0) scnt+=cnt[fa[x]];
	if(fa[fa[x]]!=0) scnt+=1;
	for(int j=G.head[x];~j;j=G.edge[j].nxt){
		int y=G.edge[j].to;
		if(y!=pre){
			dfs2(y,x);
			p=p+f[y];
			scnt+=cnt[y];
		}
	}
//	printf("|%d %d|",x,scnt);
	int t=(1+MOD-p.x[2])%MOD; p.x[2]=0;
	p=p*fpow(t,MOD-2);
	for(int j=G.head[x];~j;j=G.edge[j].nxt){
		int y=G.edge[j].to;
		if(y!=pre){
			f[y].x[0]=(f[y].x[0]+1ll*f[y].x[2]*p.x[0])%MOD;
			f[y].x[1]=(f[y].x[1]+1ll*f[y].x[2]*p.x[1])%MOD;
			f[y].x[3]=(f[y].x[3]+1ll*f[y].x[2]*p.x[3])%MOD;
			f[y].x[2]=0;
		}
	} 
	scnt=fpow(scnt,MOD-2);
	f[x].x[2]=scnt;
	int dcnt=0;
	for(int j=G.head[x];~j;j=G.edge[j].nxt){
		int y=G.edge[j].to;
		if(y!=pre){
			f[x].x[1]=(f[x].x[1]+1ll*scnt*f[y].x[0])%MOD;
			dcnt=(dcnt+1ll*scnt*f[y].x[1]%MOD)%MOD;
			f[x].x[3]=(f[x].x[3]+1ll*scnt*f[y].x[3])%MOD;
			for(int j=G.head[y];~j;j=G.edge[j].nxt){
				int z=G.edge[j].to;
				if(z!=x){
					dcnt=(dcnt+1ll*scnt*f[z].x[0]+1ll*scnt
						*f[z].x[1]%MOD*f[y].x[1])%MOD;
					f[x].x[1]=(f[x].x[1]+1ll*scnt*f[z].x[1]%MOD
						*f[y].x[0])%MOD;
					f[x].x[3]=(f[x].x[3]+1ll*scnt*f[z].x[1]%MOD
						*f[y].x[3]+1ll*scnt*f[z].x[3])%MOD;
				}
			}
		}
	}
	if(fa[x]!=0) f[x].x[1]=(f[x].x[1]+scnt)%MOD;
	if(fa[fa[x]]!=0) f[x].x[0]=(f[x].x[0]+scnt)%MOD;
	dcnt=(1+MOD-dcnt)%MOD;
	for(int i=0;i<4;++i) 
		f[x].x[i]=1ll*f[x].x[i]*fpow(dcnt,MOD-2)%MOD;
	if(vis[x]) f[x].x[0]=f[x].x[1]=f[x].x[2]=f[x].x[3]=0;
	//printf("(%d %d %d %d %d)\n",x,f[x].x[0],f[x].x[1],f[x].x[2],f[x].x[3]);
}
int g[MAX_N];
void dfs3(int x,int pre){
	g[x]=(1ll*f[x].x[0]*g[fa[fa[x]]]+1ll*f[x].x[1]*g[fa[x]]+f[x].x[3])%MOD
		*fpow((1+MOD-f[x].x[2])%MOD,MOD-2)%MOD;
	for(int j=G.head[x];~j;j=G.edge[j].nxt){
		int y=G.edge[j].to;
		if(y!=pre) dfs3(y,x);
	}
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n,m; scanf("%d%d",&n,&m);
	for(int i=1;i<n;++i){
		int x,y;  scanf("%d%d",&x,&y);
		G.add(x,y); G.add(y,x);
	}
	for(int i=1;i<=n;++i) fa[i]=0;
	for(int i=1;i<=m;++i){
		int x; scanf("%d",&x); vis[x]=1;
	}
	dfs1(1,0);
	dfs2(1,0);
//	cerr<<"G"<<n<<endl;;
	dfs3(1,0);
//	cerr<<"T"<<n<<endl;
//	for(int i=1;i<=n;++i) 
//		printf("<%d %d %d %d>",f[i].x[0],f[i].x[1],f[i].x[2],f[i].x[3]);
	for(int i=1;i<=n;++i) printf("%d\n",g[i]);
	return 0;
}
