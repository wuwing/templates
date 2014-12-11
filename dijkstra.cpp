//  dijkstra
int dist[FFF],len[FFF][FFF]
bool vis[FFF];

int dijkstra(int s) {
	memset(dist,-1,sizeof(dist));
	memset(vis,false,sizeof(vis));
	dist[s] = 0;
	for(int i = 1;i < n;i++) {
		int dis = INF,loc;
		for(int j = 1;j <= n;j++) {
			if(!vis[j] && dist[j] != -1 && dist[j] < dis) {
				dis = dist[j];
				loc = j;
			}	
		}
		vis[loc] = true;
		for(int j = 1;j <= n;j++) {
			if(vis[j]) continue;
			if(dist[j] == -1 || dist[j] > dist[loc] + len[loc][j])
				dist[j] = dist[loc] + len[loc][j];
		}
	}
	return dist[target];
}
