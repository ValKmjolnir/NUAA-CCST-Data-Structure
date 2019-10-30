#include <iostream>
#include <algorithm>
using namespace std;
int a[10001];
int b[10001];
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;++i)
		cin>>a[i];
	sort(a,a+n);
	for(int i=0;i<n;++i)
		b[i]=-1;
	int j=0;
	for(int i=0;i<n;++i)
	{
		if(b[j]<0)
			b[j]=a[i];
		else if(a[i]!=b[j])
		{
			++j;
			b[j]=a[i];
		}
	}
	int cnt=0;
	for(int i=0;i<j;++i)
	{
		if(b[i]+1==b[i+1])
			++cnt;
	}
	cout<<cnt;
	return 0;
}
