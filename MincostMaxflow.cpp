/*MinCostMaxFlow*/
#define FFF /*number of node*/
#define INF 233333333
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
	queue<int> p;
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
		vis[now] = false;//处理负环时有问题需要修正
	}
	if(dist[t] < INF) return true;
	else return false;
}

int MincostMaxflow(int s,int t)  {
	int mincost = 0;
	while(spfa(s,t))  {
		int flow = INF;
		for(int i = pre[t]; i != -1; i = pre[edge[i].u])
			flow = min(flow,edge[i].f);
		for(int i = pre[t]; i != -1; i = pre[edge[i].u])  {
			edge[i].f -= flow;
			edge[i^1].f += flow;
		}
		mincost += dist[t] * flow;
	}
	return mincost;
}
