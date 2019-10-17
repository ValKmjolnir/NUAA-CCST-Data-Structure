#include <iostream>
#include <cstring>
using namespace std;
int t1[1000001];
int t2[1000001];
int main()
{
	memset(t1,0,sizeof(t1));
	memset(t2,0,sizeof(t2));
	int n,beg,end;
	int max_end=0;
	cin>>n;
	for(int i=0;i<n;++i)
	{
		cin>>beg>>end;
		max_end=max_end>=end? max_end:end;
		for(int j=beg;j<end;++j)
			t1[j]=1;
	}
	for(int i=0;i<n;++i)
	{
		cin>>beg>>end;
		max_end=max_end>=end? max_end:end;
		for(int j=beg;j<end;++j)
			t2[j]=1;
	}
	int cnt=0;
	for(int i=0;i<=max_end;++i)
		cnt+=(t1[i] && t2[i]);
	cout<<cnt;
	return 0;
}
