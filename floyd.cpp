void floyd() {
	for(int k = 1;k <= n;k++) {
		for(int i = 1;i <= n;i++) {
			for(int j = 1;j <= n;j++) {
				if(len[i][j] > len[i][k] + len[k][j])
					len[i][j] = len[i][k] + len[k][j];
			}
		}
	}
}
