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
		bool BiTreeEmpty()
		{
			return !(left_child || right_child);
		}
		char Value()
		{
			return elem;
		}
		void LevelOrderTraverse(void (*func)(binary_tree*),int depth)
		{
			std::list<binary_tree*> que;
			std::list<int> level;
			que.push_back(this);
			level.push_back(1);
			while(!que.empty())
			{
				if(level.front()==depth)
					func(que.front());
				if(que.front()->left_child)
				{
					que.push_back(que.front()->left_child);
					level.push_back(level.front()+1);
				}
				if(que.front()->right_child)
				{
					que.push_back(que.front()->right_child);
					level.push_back(level.front()+1);
				}
				que.pop_front();
				level.pop_front();
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
	root.LevelOrderTraverse(visit,2);
	return 0;
}
