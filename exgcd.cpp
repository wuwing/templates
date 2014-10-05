/* exgcd
 *a,b,gcd(a,b)为非负整数，必存在整数对使得gcd(a,b)=ax+by

 * 求解ax+by=c的整数解的方法：
 ** 求ax+by=gcd(a,b)的整数解x0,y0
 *** x1=x0*(c/gcd(a,b)) 
 *** y1=y0*(c/gcd(a,b))
 **** x=x1+b/gcd(a,b)*t
 **** y=y1-a/gcd(a,b)*t

 */
//递归版
int exgcd(int a,int b,int &x,int &y) {
	if(b==0) {
		x=1;y=0;return a;
	}
	int r=exgec(b,a%b,x,y);
	int t=x;
	x=y;
	y=t-a/b*y;
	return r;
}

//非递归版
int exgcd(int a,int b,int &x,int &y) {
	int x1,y1,x0,y0;
	x0=1;y0=0;
	x1=0;y1=1;
	x=0;y=1;
	int r=a%b;
	int q=(a-r)/b;
	while(r) {
		x=x0-q*x1;
		y=y0-q*y1;
		x0=x1;
		y0=y1;
		x1=x;
		y1=y;
		a=b;
		b=r;
		b=a%b;
		q=(a-r)/b;
	}
	return b;
}

//ax+by=c
bool liner_equation(int a,int b,int c,int &x,int &y) {
	int d=exgcd(a,b,x,y);
	if(c%d)
		return false;
	int k=c/d;
	x*=k;y*=k;//求得x1,y1 x=x1+b/gcd(a,b)*t y=y1-a/gcd(a,b)*t
	return true;
}
