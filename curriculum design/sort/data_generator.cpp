#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
int a[50000];
bool cmp(int a,int b)
{
	return a>b;
}
int main()
{
	std::string filename="data";
	std::string suffix=".txt";
	std::srand(unsigned(std::time(NULL)));
	
	for(char i='0';i<='9';++i)
	{
		std::ofstream fout(filename+i+suffix);
		for(int j=0;j<50000;++j)
			a[j]=std::rand()%10000;
		if(i=='0')
			std::sort(a,a+50000);
		if(i=='1')
			std::sort(a,a+50000,cmp);
		for(int j=0;j<50000;++j)
			fout<<a[j]<<" ";
		fout.close();
	}
	return 0;
}
