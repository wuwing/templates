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
