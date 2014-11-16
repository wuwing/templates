#define FFF /*number of node*/
#define INF 233333333

//字符串
/*kmp*/
void getnext(char *s) {
	int len = strlen(s),j = 0,k = -1;
	next[0] = -1;
	while(j < len) {
		if(k == -1 || s[j] == s[k]) {
			j++; k++; next[j] = k;
		}
		else
			k = next[k];
	}
}

bool kmpmatch(char *s,char *ss) {
	int i = 0,j = 0;
	while(s[i] != '\0') {
		if(j == -1 || ss[j] == s[i]) {
			i++;j++;
			if(ss[j] == '\0')
				return true;
		}
		else
			j = next[j];
	}
}

/*palindrome-最长回文子串*/
int solve() {
	int ml = 0, id, ans = 0;
	for(int i = 1;i < len;i++) {
		if(ml > i)
			cnt[i] = min(cnt[2*id-i],ml - i);
		else
			cnt[i] = 1;
		while(s[i+cnt[i]] != '\0' && i - cnt[i] >= 0 && s[i+cnt[i]] == s[i-cnt[i]])
			cnt[i]++;
		if(cnt[i] + i > ml) {
			ml = cnt[i] + i;
			id = i;
		}
		ans = max(ans,cnt[i] - 1);
	}
}

/*trie 样例为字典树*/
struct node {
	node *next[26];
};

node* newnode() {
	node *p = (node *)malloc(sizeof(node));
	for(int i = 0;i < 26;i++)
		p -> next[i] = NULL;
	return p;
}

void build(char *s,node *root) {
	node *p = root;
	for(int i = 0; s[i] != '\0';i++) {
		int t = s[i] - 'a';
		if(p -> next[t] == NULL) {
			node *q = newnode();
			p -> next[t] = q;
		}
		p = p -> next[t];
	}
	return;
}

bool solve(char *s,node *root) {
	node *p = root;
	for(int i = 0;s[i] != '\0';i++) {
		int t = s[i] - 'a';
		if(p -> next[t] == NULL)
			return false;
		else
			p = p -> next[t];
	}
	return true;
}

//网络流
/*dinic求最大流*/
int first[FFF],dis[FFF],e;
void init()  {
	memset(first,-1,sizeof(first));
	e = 0;
}
struct node  {
	int x,y,f;
}edge[FF];
void addedge(int x,int y,int f,int c)
{
	edge[e].x = x;edge[e].y = y;edge[e].f = f;edge[e].next = first[x];first[x] = e++;
	edge[e].y = x;edge[e].x = y;edge[e].f = 0;edge[e].next = first[y];first[y] = e++;
}

bool bfs(int s,int t)
{
	memset(dis,-1,sizeof(dis));
	dis[s] = 0;
	queue<int> p;
	p.push(s);
	while(!p.empty())  {
		int now = p.front(); p.pop();
		for(int k = first[now];k != -1;k = edge[k].next)  {
			if(edge[k].f && dis[edge[k].v] == -1)
			{
				dis[edge[k].v] = dis[now] + 1;
				if(edge[k].v == t)
					return true;
				p.push(edge[k].v);
			}
		}
	}
	return false;
}
int dfs(int now,int flow,int t)  {
	int f;
	if(now == t)  return flow;
	for(int k = first[now];k != -1;k = edge[k].next)  {
		if(edge[k].f && dis[edge[k].v] == dis[now] + 1 && (f = dfs(edge[k].v,min(flow,edge[k].f),t)))  {
			edge[k].f -= f;
			edge[k^1].f += f;
			return f;
		}
	}
	return 0;
}
int dinic(int s,int t)
{
	int flow,ret = 0;
	while(bfs(s,t))  {
		while(flow = dfs(s,23333333,t))
			ret += flow;
	}
	return ret;
}

/*MinCostMaxFlow*/
int first[FFF] , dist[FFF] , pre[FFF];
bool vis[FFF];
struct node  {
	int u,v,flow,next,cost;
}edge[FFF*4];

void init()  {
	memset(first,-1,sizeof(first));
	e=0;
}
void addedge(int u,int v,int flow,int cost)  {
	edge[e].u=u;edge[e].v=v;edge[e].flow=flow;edge[e].cost=cost;edge[e].next=first[u];first[u]=e++;
	edge[e].u=v;edge[e].v=u;edge[e].flow=0;edge[e].cost=-cost;edge[e].next=first[v];first[v]=e++;
}

bool spfa(int s,int t)  {
	if(s == t) return false;
	queue<int> q;
	memset(pre,-1,sizeof(pre));
	memset(vis,false,sizeof(vis));
	for(int i = s; i <= t; i++)
		dist[i] = INF;
	dist[s] = 0; vis[s] = true; q.push(s);
	while(!q.empty())  {
		int now = q.front(); q.pop();
		for(int i = first[now]; i != -1; i = edge[i].next)  {
			int v = edge[i].v;
			if(edge[i].f && dist[v] > dist[now] + edge[i].cost)  {
				dist[v] = dist[now] + edge[i].cost;
				pre[v] = i;
				if(!vis[v])  { q.push(v); vis[v]=true;}
			}
		}
		vis[now] = false;
	}
	if(dist[v] < INF) return true;
	else return false;
}

int MincostMaxflow(int s,int t)  {
	int mincost = 0;
	while(spfa(s,t))  {
		int flow = INF;
		for(int i = pre[t]; i != -1; i = pre[edge[i]].u)
			flow = min(flow,edge[i].f);
		for(int i = pre[t]; i != -1; i = pre[edge[i]].u)  {
			edge[i].f -= flow;
			edge[i^1].f += flow;
		}
		mincost += dist[t] * flow;
	}
	return mincost;
}

//图
/*prim 最小生成树*/
int len[FFF][FFF],dis[FFF];
bool vis[FFF];
int prim(int s)  {
	int ans = 0;
	memset(vis,false,sizeof(vis));
	vis[s] = true;
	for(int i = 0;i < n; i++)  {
		if(!vis[i])
			dis[i] = len[s][i];
	}
	for(int i = 1;i < n; i++)  {
		int l = MAX,k;
		for(int j = 0;j < n; j++)  {
			if(!vis[j]&&l > dis[j])  {
				l = dis[j]; k = j;
			}
		}
		vis[j] = true;
		ans += dis[k];
		for(int j = 0;j < n;j++)  {
			if(!vis[j] && len[k][j] < dis[j])  {
				dis[j] = len[k][j];
			}
		}
	}
	return ans;
}

/*tarjan*/
int first[FFF],dfn[FFF],low[FFF],e,set[FFF],cnt,top;
struct node  {
	int u,v,next;
}edge[FFF];
void addedge(int u,int v)  {edge[e].u = u;edge[e].v = v;edge[e].next = first[u];first[u] = e++;}
void init() {
	memset(first,-1,sizeof(first));
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	e = 0;  cnt = 1;  top = 1; snum = 1;
}
int que[FFF],snum;
bool vis[FFF];
void tarjan(int x)  {
	dfn[x] = low[x] = cnt++;
	que[top++] = x ;vis[x] = true;
	for(int k = first[x]; ~k ;k = edge[k].next)  {
		int v = edge[k].v;
		if(dfn[v] == -1)  {
			tarjan(v);
			low[x] = min(low[x],low[v]);
		}
		else if(vis[v])
			low[x] = min(low[x],dfn[v]);
	}
	if(dfn[x] == low[x])  {
		int y = que[--top];
		while(y != x)  {
			vis[y] = false;
			set[y] = snum;
			y = que[--top];
		}
		vis[y] = false;
		set[y] = snum;
	}
}
int main()  {
	/*****/
	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i);
}


/*km二分图最大权匹配&&最小权匹配*/
int len[FFF][FFF]
int sx[FFF],sy[FFF];
int lx[FFF],ly[FFF];
int match[FFF]; //int match[j]//与j匹配的i
#define MAX 999999999

int bfs(int i){
	int j;
	sx[i]=1;
	for(j=1;j<=m;j++) {
		if(!sy[j]&&lx[i]+ly[j]==len[i][j]){
			sy[j]=1;
			if(!match[j]||bfs(match[j])){
				match[j]=i;
				return 1;
			}
		}
	}
	return 0;
}

//最大权匹配
int km(){
	int i,j,d,x,sum;
	for(i=1;i<=n;i++){
		lx[i]=MIN;//lx=max(len[i][j])
		for(j=1;j<=m;j++)
			lx[i]=max(lx[i],len[i][j]);
	}
	memset(ly,0,sizeof(ly));
	memset(match,0,sizeof(match));
	for(x=1;x<=n;x++){
		while(1){
			memset(sx,0,sizeof(sx));
			memset(sy,0,sizeof(sy));
			if(bfs(x))break;
			d=MAX;
			for(i=1;i<=n;i++){
				if(sx[i])
				for(j=1;j<=m;j++){
					if(!sy[j])
						d=min(d,lx[i]+ly[j]-len[i][j]);
				}
			}
			for(i=1;i<=n;i++)
				if(sx[i]) lx[i]-=d;
			for(j=1;j<=m;j++)
				if(sy[j]) ly[j]+=d;
		}
	}
	sum=0;
	for(i=1;i<=n;i++)
		sum+=lx[i];
	for(j=1;j<=m;j++)
		sum+=ly[j];
	return sum;
}


// 最小权匹配
int km(){
	int i,j,d,x,sum;
	for(i=1;i<=n;i++){
		lx[i]=MAX;//lx=min(len[i][j])
		for(j=1;j<=m;j++)
			lx[i]=min(lx[i],len[i][j]);
	}
	memset(ly,0,sizeof(ly));
	memset(match,0,sizeof(match));
	for(x=1;x<=n;x++){
		while(1){
			memset(sx,0,sizeof(sx));
			memset(sy,0,sizeof(sy));
			if(bfs(x))break;
			d=MAX;
			for(i=1;i<=n;i++){
				if(sx[i])
				for(j=1;j<=m;j++){
					if(!sy[j])
						d=min(d,len[i][j]-lx[i]-ly[j]);
				}
			}
			for(i=1;i<=n;i++)
				if(sx[i]) lx[i]+=d;
			for(j=1;j<=m;j++)
				if(sy[j]) ly[j]-=d;
		}
	}
	sum=0;
	for(i=1;i<=n;i++)
		sum+=lx[i];
	for(j=1;j<=m;j++)
		sum+=ly[j];
	return sum;
}

//数学
/*
  exgcd 扩展欧几里得
 *a,b,gcd(a,b)为非负整数，必存在整数对使得gcd(a,b)=ax+by

 * 求解ax+by=c的整数解的方法：
 ** 求ax+by=gcd(a,b)的整数解x0,y0
 *** x1=x0*(c/gcd(a,b)) 
 *** y1=y0*(c/gcd(a,b))
 **** x=x1+b/gcd(a,b)*t
 **** y=y1-a/gcd(a,b)*t

 */
//递归版
int exgcd(int a,int b,int &x,int &y) {
	if(b==0) {
		x=1;y=0;return a;
	}
	int r=exgec(b,a%b,x,y);
	int t=x;
	x=y;
	y=t-a/b*y;
	return r;
}

//非递归版
int exgcd(int a,int b,int &x,int &y) {
	int x1,y1,x0,y0;
	x0=1;y0=0;
	x1=0;y1=1;
	x=0;y=1;
	int r=a%b;
	int q=(a-r)/b;
	while(r) {
		x=x0-q*x1;
		y=y0-q*y1;
		x0=x1;
		y0=y1;
		x1=x;
		y1=y;
		a=b;
		b=r;
		b=a%b;
		q=(a-r)/b;
	}
	return b;
}

//ax+by=c
bool liner_equation(int a,int b,int c,int &x,int &y) {
	int d=exgcd(a,b,x,y);
	if(c%d)
		return false;
	int k=c/d;
	x*=k;y*=k;//求得x1,y1 x=x1+b/gcd(a,b)*t y=y1-a/gcd(a,b)*t
	return true;
}
