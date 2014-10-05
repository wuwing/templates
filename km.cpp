int len[FFF][FFF]
int sx[FFF],sy[FFF];
int lx[FFF],ly[FFF];
int match[FFF];
//int match[j]//与j匹配的i
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