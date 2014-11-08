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

bool kmpmatch(char *s,char *ss)
{
	int i = 0,j = 0;
	while(s[i] != '\0')
	{
		if(j == -1 || ss[j] == s[i])
		{
			i++;j++;
			if(ss[j] == '\0')
				return true;
		}
		else
			j = next[j];
	}
}
