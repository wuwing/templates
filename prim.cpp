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
