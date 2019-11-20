#include <iostream>
using namespace std;

struct ball
{
	int delta;
	int place;
};
ball set[100];
int n,L,t;

void run()
{
	for(int i=0;i<n;++i)
	{
		if(set[i].place==L && set[i].delta==1)
			set[i].delta=-1;
		if(set[i].place==0 && set[i].delta==-1)
			set[i].delta=1;
		for(int j=i+1;j<n;++j)
			if(set[i].place==set[j].place)
			{
				set[i].delta*=-1;
				set[j].delta*=-1;
				break;
			}
	}
	return;
}

int main()
{	
	cin>>n>>L>>t;
	for(int i=0;i<n;++i)
	{
		set[i].delta=1;
		cin>>set[i].place;
	}
	for(int i=0;i<t;++i)
	{
		for(int j=0;j<n;++j)
			set[j].place+=set[j].delta;
		run();
	}
	for(int i=0;i<n;++i)
		cout<<set[i].place<<" ";
	return 0;
}
