#include <iostream>

int chess[3][3];

bool check(int p)
{
	for(int i=0;i<3;++i)
	{
		if(chess[i][0]==p && chess[i][0]==chess[i][1] && chess[i][1]==chess[i][2])
			return true;
		if(chess[0][i]==p && chess[0][i]==chess[1][i] && chess[1][i]==chess[2][i])
			return true;
	}
	if(chess[1][1]==p && (chess[0][0]==chess[1][1] && chess[1][1]==chess[2][2]))
		return true;
	if(chess[1][1]==p && (chess[0][2]==chess[1][1] && chess[1][1]==chess[2][0]))
		return true;
	return false;
}

int dfs(int person)
{
	int cnt=0;
	for(int i=0;i<3;++i)
		for(int j=0;j<3;++j)
			if(!chess[i][j])
				++cnt;
	int mmax=-10;
	int mmin=10;
	if(person==1 && check(2))
		return -cnt-1;
	if(person==2 && check(1))
		return cnt+1;
	if(!cnt)
		return 0;
	for(int i=0;i<3;++i)
		for(int j=0;j<3;++j)
			if(!chess[i][j])
			{
				chess[i][j]=person;
				if(person==1)
					mmax=std::max(mmax,dfs(2));
				if(person==2)
					mmin=std::min(mmin,dfs(1));
				chess[i][j]=0;
			}
	if(person==1)
		return mmax;
	if(person==2)
		return mmin;
	return 0;
}

int main()
{
	int n;
	std::cin>>n;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<3;++j)
			for(int k=0;k<3;++k)
				std::cin>>chess[j][k];
		std::cout<<dfs(1)<<std::endl;
	}
	
	return 0;
}
