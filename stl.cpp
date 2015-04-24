/*multiset */
multiset <type> p;

p.begin(); //第一个元素的迭代器
p.rbegin(); //指向最后一个元素的反向迭代器

p.end(); //最后一个元素的迭代器

p.insert(x); //添加x元素
p.erase(); //删除某元素

p.lower_bound(); //返回指向大于等于某值的第一个元素的迭代器

struct type {
	int a,b,c;
};
struct compare {
	bool operator()(const type &a,const type &b)const {
		return a.s < b.x;
	}
}
multiset<type,compare> element;

multiset<int> :: iterator it;
for( it = p.begin();it != p.end();it++)
{
	cout<<*it<<" ";
}

/*vector*/
vector <type> p;
p.push_back(a);//添加一个数

lower_bound(p.start(),p.end(),x); //找第一个大于等于x的值 返回的是迭代器
lower_bound(p.start(),p.end(),x)-p.start(); //找第一个大于等于x的值 返回的是下标

/*priority_queue*/
priority_queue<type> p;
p.push();
p.top();

priority_queue<int,vector<int>,greater<int>> p;

struct node {
	int x,y;
	friend bool operator < (node a,node b) {
		return a.x < b.x;
	}
};
/*pir*/
