#include <iostream>
#include <list>
#include <stack>
class binary_tree
{
	private:
		char elem;
		binary_tree* left_child;
		binary_tree* right_child;
	public:
		binary_tree()
		{
			left_child=NULL;
			right_child=NULL;
			return;
		}
		~binary_tree()
		{
			if(left_child)
				delete left_child;
			if(right_child)
				delete right_child;
		}
		void CreateBiTree()
		{
			std::cin>>elem;
			if(elem=='#')
				return;
			if(!left_child)
			{
				left_child=new binary_tree;
				left_child->CreateBiTree();
				if(left_child->elem=='#')
				{
					delete left_child;
					left_child=NULL;
				}
			}
			if(!right_child)
			{
				right_child=new binary_tree;
				right_child->CreateBiTree();
				if(right_child->elem=='#')
				{
					delete right_child;
					right_child=NULL;
				}
			}
			return;
		}
		void ClearBiTree()
		{
			if(left_child)
				delete left_child;
			if(right_child)
				delete right_child;
			return;
		}
		char Value()
		{
			return elem;
		}
		void PreOrderTraverse(void (*func)(binary_tree*))
		{
			func(this);
			if(left_child)
				left_child->PreOrderTraverse(func);
			if(right_child)
				right_child->PreOrderTraverse(func);
			return;
		}
		void PreOrderTraverse_stack(void (*func)(binary_tree*))
		{
			std::stack<binary_tree*> stk;
			std::stack<int> check;
			stk.push(this);
			func(stk.top());
			check.push(0);
			while(!stk.empty())
			{
				if(check.top()==0)
				{
					if(stk.top()->left_child)
					{
						stk.push(stk.top()->left_child);
						func(stk.top());
						check.pop();check.push(1);check.push(0);
					}
					else
					{
						check.pop();
						check.push(1);
					}
				}
				else if(check.top()==1)
				{
					if(stk.top()->right_child)
					{
						stk.push(stk.top()->right_child);
						func(stk.top());
						check.pop();check.push(2);check.push(0);
					}
					else
					{
						check.pop();
						check.push(2);
					}
				}
				else if(check.top()==2)
				{
					check.pop();
					stk.pop();
				}
			}
		}
		void InOrderTraverse(void (*func)(binary_tree*))
		{
			if(left_child)
				left_child->InOrderTraverse(func);
			func(this);
			if(right_child)
				right_child->InOrderTraverse(func);
			return;
		}
		void InOrderTraverse_stack(void (*func)(binary_tree*))
		{
			std::stack<binary_tree*> stk;
			std::stack<int> check;
			stk.push(this);
			check.push(0);
			while(!stk.empty())
			{
				if(check.top()==0)
				{
					if(stk.top()->left_child)
					{
						stk.push(stk.top()->left_child);
						check.pop();check.push(1);check.push(0);
					}
					else
					{
						check.pop();
						check.push(1);
					}
				}
				else if(check.top()==1)
				{
					func(stk.top());
					if(stk.top()->right_child)
					{
						stk.push(stk.top()->right_child);
						check.pop();check.push(2);check.push(0);
					}
					else
					{
						check.pop();
						check.push(2);
					}
				}
				else if(check.top()==2)
				{
					check.pop();
					stk.pop();
				}
			}
			return;
		}
		void PostOrderTraverse(void (*func)(binary_tree*))
		{
			if(left_child)
				left_child->PostOrderTraverse(func);
			if(right_child)
				right_child->PostOrderTraverse(func);
			func(this);
			return;
		}
		void PostOrderTraverse_stack(void (*func)(binary_tree*))
		{
			std::stack<binary_tree*> stk;
			std::stack<int> check;
			stk.push(this);
			check.push(0);
			while(!stk.empty())
			{
				if(check.top()==0)
				{
					if(stk.top()->left_child)
					{
						stk.push(stk.top()->left_child);
						check.pop();check.push(1);check.push(0);
					}
					else
					{
						check.pop();
						check.push(1);
					}
				}
				else if(check.top()==1)
				{
					if(stk.top()->right_child)
					{
						stk.push(stk.top()->right_child);
						check.pop();check.push(2);check.push(0);
					}
					else
					{
						check.pop();
						check.push(2);
					}
				}
				else if(check.top()==2)
				{
					func(stk.top());
					check.pop();
					stk.pop();
				}
			}
			return;
		}
		void LeverOrderTraverse(void (*func)(binary_tree*))
		{
			std::list<binary_tree*> que;
			que.push_back(this);
			while(!que.empty())
			{
				func(que.front());
				if(que.front()->left_child)que.push_back(que.front()->left_child);
				if(que.front()->right_child)que.push_back(que.front()->right_child);
				que.pop_front();
			}
			return;
		}
};
void visit(binary_tree* p)
{
	std::cout<<p->Value();
	return;
}
int main()
{
	binary_tree root;
	root.CreateBiTree();
	root.PreOrderTraverse(visit);
	std::cout<<std::endl;
	root.PreOrderTraverse_stack(visit);
	std::cout<<std::endl;
	root.InOrderTraverse(visit);
	std::cout<<std::endl;
	root.InOrderTraverse_stack(visit);
	std::cout<<std::endl;
	root.PostOrderTraverse(visit);
	std::cout<<std::endl;
	root.PostOrderTraverse_stack(visit);
	std::cout<<std::endl;
	root.LeverOrderTraverse(visit);
	return 0;
}
