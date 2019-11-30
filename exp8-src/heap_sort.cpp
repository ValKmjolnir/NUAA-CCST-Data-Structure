#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define INF 0x7fffffff

int num[1025];

void init()
{
	std::srand(unsigned(std::time(NULL)));
	for(int i=1;i<1025;++i)
		num[i]=rand()%1025;
	return;
}

void heap_sort()
{
	for(int T=1;T<1025;++T)
	{
		for(int t=int(std::log(1024.0)/std::log(2.0));t>=1;--t)
		{
			for(int i=1<<t;i<=std::min(1024,(1<<(t+1))-1);++i)
				if(num[i>>1]>num[i])
				{
					int t=num[i>>1];
					num[i>>1]=num[i];
					num[i]=t;
				}
		}
		std::cout<<num[1]<<" ";
		num[1]=INF;
	}
	return;
}

int main()
{
	init();
	heap_sort();
	return 0;
}
