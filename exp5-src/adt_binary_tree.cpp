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
		int BiTreeDepth()
		{
			int mmax=0;
			if(left_child)
			{
				int l=left_child->BiTreeDepth();
				mmax=l>mmax? l:mmax;
			}
			if(right_child)
			{
				int r=right_child->BiTreeDepth();
				mmax=r>mmax? r:mmax;
			}
			return 1+mmax;
		}
		binary_tree* Root()
		{
			return this;
		}
		char Value()
		{
			return elem;
		}
		void Assign(char value)
		{
			elem=value;
			return;
		}
		binary_tree* Parent(char c)
		{
			binary_tree* temp;
			if(left_child)
			{
				if(left_child->elem==c)
					return left_child;
				temp=left_child->Parent(c);
				if(temp)
					return temp;
			}
			if(right_child)
			{
				if(right_child->elem==c)
					return right_child;
				temp=right_child->Parent(c);
				if(temp)
					return temp;
			}
			return NULL;
		}
		binary_tree* LeftChild()
		{
			return left_child;
		}
		binary_tree* RightChild()
		{
			return right_child;
		}
		binary_tree* LeftSibling(char c)
		{
			binary_tree* temp;
			if(left_child)
			{
				if(left_child->elem==c)
					return NULL;
				temp=left_child->LeftSibling(c);
				if(temp)
					return temp;
			}
			if(right_child)
			{
				if(right_child->elem==c)
					return left_child;
				temp=right_child->LeftSibling(c);
				if(temp)
					return temp;
			}
			return NULL;
		}
		binary_tree* RightSibling(char c)
		{
			binary_tree* temp;
			if(left_child)
			{
				if(left_child->elem==c)
					return right_child;
				temp=left_child->RightSibling(c);
				if(temp)
					return temp;
			}
			if(right_child)
			{
				if(right_child->elem==c)
					return NULL;
				temp=right_child->RightSibling(c);
				if(temp)
					return temp;
			}
			return NULL;
		}
		void InsertChild(int LR,binary_tree* c)
		{
			if(right_child)
				return;
			if(!LR)
			{
				if(left_child)
				{
					right_child=left_child;
					left_child=c;
				}
			}
			else if(LR==1)
				right_child=c;
			return;
		}
		void DeleteChild(int LR)
		{
			if(!LR)
				delete left_child;
			else if(LR==1)
				delete right_child;
			return;
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
		void InOrderTraverse(void (*func)(binary_tree*))
		{
			if(left_child)
				left_child->InOrderTraverse(func);
			func(this);
			if(right_child)
				right_child->InOrderTraverse(func);
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
	root.InOrderTraverse(visit);
	std::cout<<std::endl;
	root.PostOrderTraverse(visit);
	std::cout<<std::endl;
	root.LeverOrderTraverse(visit);
	return 0;
}
