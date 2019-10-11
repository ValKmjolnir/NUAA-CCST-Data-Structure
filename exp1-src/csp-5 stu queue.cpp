#include <iostream>
#include <cmath>
#include <list>
using namespace std;
void print(list<int> &l,const int n)
{
	list<int>::iterator i=l.begin();
	for(int j=0;j<n;++j,++i)
		cout<<*i<<(j==n-1? '\n':' ');
	return;
}
int main()
{
	int n,m,p,q;
	list<int> l;
	cin>>n;
	for(int i=0;i<n;++i)
		l.push_back(i+1);
	cin>>m;
	for(int i=0;i<m;++i)
	{
		cin>>p>>q;
		int cnt=0;
		for(list<int>::iterator j=l.begin();j!=l.end();++j,++cnt)
			if(*j==p)
				break;
		l.remove(p);
		list<int>::iterator j=l.begin();
		for(int k=0;k<cnt+q;++k)
			++j;
		l.insert(j,p);
	}
	print(l,n);
	return 0;
}
