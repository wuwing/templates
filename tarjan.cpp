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
