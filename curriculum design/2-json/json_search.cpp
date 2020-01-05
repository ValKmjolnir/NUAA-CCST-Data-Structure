#include <iostream>
#include <fstream>
#include <cstring>
#include <list>

enum token_type
{
	unknown_type=0,
	__left_brace,
	__right_brace,
	__tok_string,
	__comma,
	__colon
};

enum node_type
{
	__error_type=0,
	__root,
	__not_exist,
	__node_string,
	__node_obj,
};

std::list<std::string> str_search_list;// this list is set for search-function of node
struct node
{
	int type;
	std::string context;
	std::list<node> children;
	node& operator=(const node& p)
	{
		type=p.type;
		context=p.context;
		children=p.children;
		return *this;
	}
	void child_search(std::list<std::string>::iterator& iter)
	{
		for(std::list<node>::iterator i=this->children.begin();i!=this->children.end();++i)
			if(i->context==*iter)
			{
				switch(i->type)
				{
					case __node_string:std::cout<<"STRING "<<i->children.front().context<<std::endl;return;break;
					case __node_obj:
						++iter;
						if(iter==str_search_list.end())
							std::cout<<"OBJECT"<<std::endl;
						else
							i->child_search(iter);
						return;break;
				}
			}
		std::cout<<"NOTEXIST"<<std::endl;
		return;
	}
	void root_search()
	{
		std::list<std::string>::iterator iter=str_search_list.begin();
		for(std::list<node>::iterator i=this->children.begin();i!=this->children.end();++i)
			if(i->context==*iter)
			{
				switch(i->type)
				{
					case __node_string:std::cout<<"STRING "<<i->children.front().context<<std::endl;return;break;
					case __node_obj:
						++iter;
						if(iter==str_search_list.end())
							std::cout<<"OBJECT"<<std::endl;
						else
							i->child_search(iter);
						return;break;
				}
			}
		std::cout<<"NOTEXIST"<<std::endl;
		return;
	}
	void print(int space)
	{
		// put some space on the screen
		std::string str="";
		for(int i=0;i<space;++i)str+=' ';
		std::cout<<str;
		
		switch(this->type)
		{
			case __root:std::cout<<"[root] "<<std::endl;break;
			// string type puts the first child and return
			case __node_string:std::cout<<"[string] "<<this->context<<" : "<<this->children.front().context<<std::endl;return;break;
			case __node_obj:std::cout<<"[object] "<<this->context<<" : "<<std::endl;break;
		}
		if(!this->children.empty())
			for(std::list<node>::iterator i=this->children.begin();i!=this->children.end();++i)
				i->print(space+4);
		return;
	}
};

struct token
{
	int type;
	std::string context;
};

std::list<char> resource;
std::list<token> token_list;
std::list<token>::iterator this_token;
std::string temp_string;
node root;

bool lexer()
{
	// scan the whole resource code and generate tokens
	std::string tmp;
	for(std::list<char>::iterator iter=resource.begin();iter!=resource.end();++iter)
	{
		token temp_token;
		if(*iter=='{')
		{
			temp_token.type=__left_brace;
			temp_token.context="{";
			token_list.push_back(temp_token);
		}
		else if(*iter=='}')
		{
			temp_token.type=__right_brace;
			temp_token.context="}";
			token_list.push_back(temp_token);
		}
		else if(*iter==',')
		{
			temp_token.type=__comma;
			temp_token.context=",";
			token_list.push_back(temp_token);
		}
		else if(*iter==':')
		{
			temp_token.type=__colon;
			temp_token.context=":";
			token_list.push_back(temp_token);
		}
		else if(*iter=='\"')
		{
			++iter;
			tmp="";
			while(*iter!='\"')
			{
				if(*iter=='\\')
				{
					++iter;
					if(iter!=resource.end() && (*iter=='\\' || *iter=='\"'))
						tmp+=*iter;
					else
					{
						// '\\' with no '\\' or '\"' after it
						std::cout<<">> [error] incorrect string: "<<tmp<<"\\"<<std::endl;
						return false;
					}
				}
				else
					tmp+=*iter;
				++iter;
				if(iter==resource.end() || *iter=='\n')
				{
					// string with an incorrect end
					std::cout<<">> [error] incorrect string: "<<tmp<<" . must end with a \'\"\' ."<<std::endl;
					return false;
				}
			}
			temp_token.type=__tok_string;
			temp_token.context=tmp;
			token_list.push_back(temp_token);
		}
	}
	return true;
}

node node_gen()
{
	node ret;
	ret.type=__error_type;
	++this_token;
	if(this_token->type==__tok_string)
	{
		ret.type=__node_string;
		ret.context=this_token->context;
	}
	else if(this_token->type==__left_brace)
	{
		ret.type=__node_obj;
		while(this_token!=token_list.end())
		{
			++this_token;
			if(this_token==token_list.end())
			{
				std::cout<<">> [error] expect a '}' at the end."<<std::endl;
				ret.type=__error_type;
				return ret;
			}
			// }
			if(this_token->type==__right_brace)
				break;
			if(this_token->type==__tok_string)
			{
				node tmp;
				tmp.context=this_token->context;
				++this_token;
				// :
				if(this_token==token_list.end() || this_token->type!=__colon)
				{
					std::cout<<">> [error] expect a \':\' this token: "<<tmp.context<<std::endl;
					ret.type=__error_type;
					return ret;
				}
				++this_token;
				if(this_token==token_list.end() || (this_token->type!=__tok_string && this_token->type!=__left_brace))
				{
					std::cout<<">> [error] expect a string or object after this token: "<<tmp.context<<std::endl;
					ret.type=__error_type;
					return ret;
				}
				switch(this_token->type)
				{
					// string must get a child typed string
					case __tok_string:tmp.type=__node_string;--this_token;tmp.children.push_back(node_gen());break;
					// object get a return type object so it's children list must set to the same as return object
					case __left_brace:tmp.type=__node_obj;--this_token;tmp.children=node_gen().children;break;
				}
				// if get error type ,parse failed
				if(tmp.children.back().type==__error_type)
				{
					ret.type=__error_type;
					return ret;
				}
				ret.children.push_back(tmp);
				++this_token;
				if(this_token->type==__right_brace)
					--this_token;
				else if(this_token->type!=__comma)
				{
					std::cout<<">> [error] expect a \',\' here."<<std::endl;
					ret.type=__error_type;
					return ret;
				}
			}
		}
	}
	else
		std::cout<<">> [error] unknown type."<<std::endl;
	return ret;
}

bool parse()
{
	root.type=__root;
	this_token=token_list.begin();
	// {
	if(this_token->type!=__left_brace)
	{
		std::cout<<">> [error] expect a '{' at the beginning."<<std::endl;
		return false;
	}
	while(this_token!=token_list.end())
	{
		++this_token;
		if(this_token==token_list.end())
		{
			std::cout<<">> [error] expect a '}' at the end."<<std::endl;
			return false;
		}
		// }
		if(this_token->type==__right_brace)
			break;
		if(this_token->type==__tok_string)
		{
			node tmp;
			tmp.context=this_token->context;
			++this_token;
			if(this_token==token_list.end() || this_token->type!=__colon)
			{
				std::cout<<">> [error] expect a \':\' this token: "<<tmp.context<<std::endl;
				return false;
			}
			++this_token;
			if(this_token==token_list.end() || (this_token->type!=__tok_string && this_token->type!=__left_brace))
			{
				std::cout<<">> [error] expect a string or object after this token: "<<tmp.context<<std::endl;
				return false;
			}
			switch(this_token->type)
			{
				// string must get a child typed string
				case __tok_string:tmp.type=__node_string;--this_token;tmp.children.push_back(node_gen());break;
				// object get a return type object so it's children list must set to the same as return object
				case __left_brace:tmp.type=__node_obj;--this_token;tmp.children=node_gen().children;break;
			}
			// if get error type ,parse failed
			if(tmp.children.back().type==__error_type)
				return false;
			root.children.push_back(tmp);
			++this_token;
			if(this_token->type==__right_brace)
				--this_token;
			else if(this_token->type!=__comma)
			{
				std::cout<<">> [error] expect a \',\' here."<<std::endl;
				return false;
			}
		}
	}
	return true;
}

int main()
{
	int n,m;
	resource.clear();
	token_list.clear();
	std::ifstream fin("test_json.txt");
	if(fin.fail())
	{
		std::cout<<">> cannot open file,stop."<<std::endl;
		return 0;
	}
	fin>>n>>m;
	std::getline(fin,temp_string);// avoid enter
	for(int i=0;i<n;++i)
	{
		std::getline(fin,temp_string);
		for(int j=0;j<temp_string.length();++j)
			resource.push_back(temp_string[j]);
	}
	if(!lexer())
	{
		std::cout<<">> [lexer] error occurred,stop."<<std::endl;
		return 0;
	}
	if(!parse())
	{
		std::cout<<">> [parse] error occurred,stop."<<std::endl;
		return 0;
	}
	root.print(0);
	for(int i=0;i<m;++i)
	{
		std::getline(fin,temp_string);
		str_search_list.clear();
		std::string t="";
		for(int j=0;j<temp_string.length();++j)
		{
			if(temp_string[j]!='.')
				t+=temp_string[j];
			else
			{
				str_search_list.push_back(t);
				t="";
			}
		}
		str_search_list.push_back(t);
		std::cout<<">> result of \'"<<temp_string<<"\' : ";
		root.root_search();
	}
	return 0;
}
