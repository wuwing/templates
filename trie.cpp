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
