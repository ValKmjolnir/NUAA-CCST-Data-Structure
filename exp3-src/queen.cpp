#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

bool row[9],le[16],ri[16];
int res[2][9];
void print(bool print_curve)
{
	for(int i=1;i<=8;++i)
		cout<<"("<<res[0][i]<<","<<res[1][i]<<") ";
	cout<<endl;
	if(!print_curve)
		return;
	for(int i=1;i<9;++i)
	{
		for(int j=1;j<9;++j)
		{
			bool a=false;
			for(int k=1;k<9;++k)
				if(res[0][k]==j && res[1][k]==i)
				{
					a=true;
					break;
				}
			cout<<(a? 1:0)<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	return;
}
void dfs(int depth)
{
	if(depth==9)
	{
		print(false);
		return;
	}
	for(int i=1;i<=8;++i)
	{
		if((!row[i]) && (!le[i-depth+8]) && (!ri[i+depth-2]))
		{
			row[i]=true;
			le[i-depth+8]=true;
			ri[i+depth-2]=true;
			res[0][depth]=i;
			res[1][depth]=depth;
			dfs(depth+1);
			row[i]=false;
			le[i-depth+8]=false;
			ri[i+depth-2]=false;
		}
	}
	return;
}
void queen_res()
{
	memset(row,0,sizeof(bool));
	memset(le,0,sizeof(bool));
	memset(ri,0,sizeof(bool));
	
	stack<int> que;
	stack<int> dep;
	
	int loop_begin=0;
	for(int depth=1;depth<=9;++depth)
	{
		if(depth==9)
		{
			print(true);
			loop_begin=que.top();
			depth=dep.top()-1;
			row[que.top()]=false;
			le[que.top()-dep.top()+8]=false;
			ri[que.top()+dep.top()-2]=false;
			que.pop();
			dep.pop();
			continue;
		}
		bool found=false;
		for(int i=loop_begin+1;i<9;++i)
		{
			if((!row[i]) && (!le[i-depth+8]) && (!ri[i+depth-2]))
			{
				que.push(i);
				dep.push(depth);
				row[i]=true;
				le[i-depth+8]=true;
				ri[i+depth-2]=true;
				res[0][depth]=i;
				res[1][depth]=depth;
				found=true;
				loop_begin=0;
				break;
			}
		}
		if(!found)
		{
			if(que.empty() || dep.empty())
				break;
			loop_begin=que.top();
			depth=dep.top()-1;
			row[que.top()]=false;
			le[que.top()-dep.top()+8]=false;
			ri[que.top()+dep.top()-2]=false;
			que.pop();
			dep.pop();
		}
	}
	return;
}
int main()
{
	memset(row,0,sizeof(bool));
	memset(le,0,sizeof(bool));
	memset(ri,0,sizeof(bool));
	dfs(1);     //stack in cpu
	queen_res();//std::stack
	return 0;
}
