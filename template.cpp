#define FFF /*number of node*/
#define INF 233333333

//网络流
/*dinic*/
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
