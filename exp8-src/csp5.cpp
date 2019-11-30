#include <iostream>
#include <algorithm>
using namespace std;

struct stru
{
	int number;
	int cnt;
}num[10001];

bool cmp(stru a,stru b)
{
	if(a.cnt>b.cnt)return true;
	if(a.cnt==b.cnt)return a.number<b.number;
	return false;
}

int main()
{
	for(int i=0;i<10001;++i)
		num[i].number=num[i].cnt=0;
	int n;
	cin>>n;
	for(int i=0;i<n;++i)
	{
		int number;
		cin>>number;
		for(int j=0;j<n;++j)
		{
			if(num[j].number==number)
			{
				++num[j].cnt;
				break;
			}
			if(!num[j].cnt)
			{
				num[j].number=number;
				++num[j].cnt;
				break;
			}
		}
	}
	sort(num,num+n,cmp);
	for(int i=0;i<10001;++i)
	{
		if(!num[i].cnt)
			break;
		std::cout<<num[i].number<<" "<<num[i].cnt<<std::endl;
	}
	return 0;
}
