#include<iostream>
#include<algorithm>
using namespace std;
int arr[100000];
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;++i)
		cin>>arr[i];
	sort(arr,arr+n);
	int cnt_less=0,cnt_more=0;
	for(int i=0;i<n>>1;++i)
		if(arr[i]!=arr[n>>1])
			++cnt_less;
	for(int i=1+(n>>1);i<n;++i)
		if(arr[i]!=arr[n>>1])
			++cnt_more;
	if(cnt_less==cnt_more)
		cout<<arr[n>>1];
	else
		cout<<-1;
	return 0;
}
