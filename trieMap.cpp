struct node {
	bool flag;
	node *fa,*next[26];
	char ch;
};  
node *newnode() {
	node *p = (node*)malloc(sizeof(node));
	p -> flag = false;
	for(int i = 0;i < 26;i++)
		p -> next[i] = NULL;
	return p;
}

void insert(node *root) {
	for(int i = 0;s[i] != '\0';i++) {
		if(root -> next[s[i] - 'a'] == NULL) {
			node *p = newnode();
			p -> fa = root;
			p -> ch = s[i];
			root -> next[s[i] - 'a'] = p;
		}
		root = root -> next[s[i] - 'a'];
	}
	root -> flag = true;
	return;
}

queue<node*> q;
void solve(node *root) {
	//cout<<"root = "<<root<<endl;
	while(!q.empty()) q.pop();
	root -> fa = root;
	for(int i = 0;i < 26;i++) {
		if(root -> next[i] == NULL)
			root -> next[i] = root;
		else
			q.push(root->next[i]);
	}
	node *now,*pre;
	while(!q.empty()) {
		now = q.front(); q.pop();
		pre = now -> fa;
		//cout<<"now = "<<now<<" ch = "<<now -> ch<<endl;
		//cout<<" pre = "<<pre<<" pre = "<<pre -> ch<<endl;
		if(pre != root)
			pre = pre -> fa -> next[now -> ch - 'a'];
		//cout<<" pre = "<<pre<<" pre = "<<pre -> ch<<endl;
		for(int i = 0;i < 26;i++) {
			if(now -> next[i] == NULL) {
				now -> next[i] = pre -> next[i];
			}
			else
				q.push(now -> next[i]);
		}
	}
	return;
}

int main() {
	int n;
	scanf("%d",&n);
	node *root = newnode();
	for(int i = 0;i < n;i++) {
		scanf("%s",s);
		insert(root);
	}

	//cout<<"insert finished\n";
	solve(root);
	//cout<<"solve finished\n";

	scanf("%s",s);
	bool ok = false;
	for(int i = 0;s[i] != '\0' && !ok;i++) {
		root = root -> next[s[i] - 'a'];
		if(root -> flag)
			ok = true;
	}
	if(ok)
		cout<<"YES\n";
	else
		cout<<"NO\n";
	return 0;
}
