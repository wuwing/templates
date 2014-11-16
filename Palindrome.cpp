/*palindrome-最长回文子串*/
int solve() {
	int ml = 0, id, ans = 0;
	for(int i = 1;i < len;i++) {
		if(ml > i)
			cnt[i] = min(cnt[2*id-i],ml - i);
		else
			cnt[i] = 1;
		while(s[i+cnt[i]] != '\0' && i - cnt[i] >= 0 && s[i+cnt[i]] == s[i-cnt[i]])
			cnt[i]++;
		if(cnt[i] + i > ml) {
			ml = cnt[i] + i;
			id = i;
		}
		ans = max(ans,cnt[i] - 1);
	}
}
