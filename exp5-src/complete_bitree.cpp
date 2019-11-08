#include <iostream>
#include <list>

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
		bool check_complete_tree()
		{
			std::list<binary_tree*> bfs;
			int cnt=0;
			std::list<bool> node_state;
			bfs.push_back(this);
			node_state.push_back(true);
			++cnt;
			while(!bfs.empty())
			{
				if(bfs.front()->left_child || bfs.front()->right_child)
				{
					if(bfs.front()->left_child)
					{
						bfs.push_back(bfs.front()->left_child);
						node_state.push_back(true);
					}
					else
						node_state.push_back(false);
					if(bfs.front()->right_child)
					{
						bfs.push_back(bfs.front()->right_child);
						node_state.push_back(true);
					}
					else
						node_state.push_back(false);
					cnt+=2;
				}
				bfs.pop_front();
			}
			std::list<bool>::iterator iter=node_state.begin();
			for(int i=0;i<cnt-1;++i,++iter)
				if(!(*iter))
					return false;
			return true;
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
	if(root.check_complete_tree())
		std::cout<<"yes";
	else
		std::cout<<"no";
	return 0;
}
