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
