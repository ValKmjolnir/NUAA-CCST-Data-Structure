#include <iostream>
#include <list>
using namespace std;
struct point
{
	int x,y;
};
struct window
{
	point p1;
	point p2;
	int number;
	bool operator==(const window& p)
	{
		return 
			p1.x==p.p1.x 
			&& p1.y==p.p1.y 
			&& p2.x==p.p2.x 
			&& p2.y==p.p2.y 
			&& number==p.number;
	}
};
int main()
{
	list<window> win_list;
	int n,m;
	int x1,y1,x2,y2;
	cin>>n>>m;
	for(int i=0;i<n;++i)
	{
		cin>>x1>>y1>>x2>>y2;
		window t;
		t.p1.x=x1;t.p1.y=y1;
		t.p2.x=x2;t.p2.y=y2;
		t.number=i+1;
		win_list.push_front(t);
	}
	for(int i=0;i<m;++i)
	{
		cin>>x1>>y1;
		bool found=false;
		for(auto j=win_list.begin();j!=win_list.end();++j)
		{
			if(j->p1.x<=x1 && x1<=j->p2.x && j->p1.y<=y1 && y1<=j->p2.y)
			{
				window t=*j;
				win_list.remove(t);
				win_list.push_front(t);
				cout<<t.number<<endl;
				found=true;
				break;
			}
		}
		if(!found)
			cout<<"IGNORED"<<endl;
	}
	return 0;
}
