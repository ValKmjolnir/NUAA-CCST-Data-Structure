#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include <cstring>

#define __number 1
#define __operator 2

struct token
{
	int type;
	char oprt;
	double num;
};

std::string sequence;
std::list<token> token_list;
std::stack<token> opt;
std::list<token> rpn;

void print_stack(std::stack<token> p)
{
	std::stack<token> tmp;
	while(!p.empty())
	{
		tmp.push(p.top());
		p.pop();
	}
	std::cout<<"calc stack: ";
	while(!tmp.empty())
	{
		std::cout<<tmp.top().num<<" ";
		tmp.pop();
	}
	std::cout<<std::endl;
	return;
}

double str2num(std::string str)
{
	// transfer string to float number
	double number;
	int dot_place=-1;
	for(int i=0;i<(int)str.length();++i)
		if(str[i]=='.')
		{
			dot_place=i;
			break;
		}
	if(dot_place==-1)
	{
		number=0;
		double pw=1;
		for(int i=(int)str.length()-1;i>=0;--i)
		{
			number+=(str[i]-'0')*pw;
			pw*=10;
		}
	}
	else
	{
		number=0;
		double pw=0.1;
		for(int i=dot_place+1;i<(int)str.length();++i)
		{
			number+=(str[i]-'0')*pw;
			pw/=10;
		}
		pw=1;
		for(int i=dot_place-1;i>=0;--i)
		{
			number+=(str[i]-'0')*pw;
			pw*=10;
		}
	}
	return number;
}

bool lexer()
{
	// scan input sequence and split it into tokens
	token_list.clear();
	if((sequence.length()>1 && (sequence[0]!='#' || sequence[sequence.length()-1]!='#')) || sequence.length()<=1)
	{
		std::cout<<">>[Error] input string must begin with \'#\' and end with \'#\'"<<std::endl;
		return false;
	}
	for(int i=1;i<sequence.length()-1;++i)
	{
		if(sequence[i]=='+' || sequence[i]=='-' || sequence[i]=='*' || sequence[i]=='/' || sequence[i]=='(' || sequence[i]==')')
		{
			token tmp;
			tmp.type=__operator;
			tmp.oprt=sequence[i];
			token_list.push_back(tmp);
		}
		else if('0'<=sequence[i] && sequence[i]<='9')
		{
			token tmp;
			tmp.type=__number;
			std::string str="";
			int dotcnt=0;
			int j=i;
			while('0'<=sequence[j] && sequence[j]<='9' || sequence[j]=='.')
			{
				str+=sequence[j];
				if(sequence[j]=='.')
					++dotcnt;
				++j;
			}
			i=j-1;
			if(dotcnt>1)
			{
				std::cout<<">>[Error] number must use no more than one dot but \'"<<str<<"\' uses "<<dotcnt<<" dots."<<std::endl;
				return false;
			}
			if(!dotcnt && str[0]=='0')
			{
				std::cout<<">>[Error] \'"<<str<<"\' uses 0 as the beginning."<<std::endl;
				return false;
			}
			tmp.num=str2num(str);
			token_list.push_back(tmp);
		}
		else
		{
			std::cout<<">>[Error] \'"<<sequence[i]<<"\' should not appear here."<<std::endl;
			return false;
		}
	}
	return true;
}

void parser()
{
	while(!opt.empty())opt.pop();
	rpn.clear();
	// rpn is used to store postfix expressions
	// opt is used to store operators and pop operators
	for(std::list<token>::iterator i=token_list.begin();i!=token_list.end();++i)
	{
		if(i->type==__number)
			rpn.push_back(*i);
		else if(i->type==__operator && opt.empty())
			opt.push(*i);
		else if(i->type==__operator && !opt.empty())
		{
			// if this operator's priority is better than the one at the top of stack
			// push this operator into rpn,
			// if not push top of stack into rpn until the top's priority is better than
			// this operator.
			if((i->oprt=='+' || i->oprt=='-'))
			{
				while(!opt.empty() && opt.top().oprt!='(')
				{
					rpn.push_back(opt.top());
					opt.pop();
				}
				opt.push(*i);
			}
			if(i->oprt==')')
				while(!opt.empty())
				{
					if(opt.top().oprt=='(')
					{
						opt.pop();
						break;
					}
					rpn.push_back(opt.top());
					opt.pop();
				}
			if(i->oprt=='/' || i->oprt=='*')
			{
				while(!opt.empty())
				{
					if(opt.top().oprt=='/' || opt.top().oprt=='*')
					{
						rpn.push_back(opt.top());
						opt.pop();
					}
					else
						break;
				}
				opt.push(*i);
			}
			if(i->oprt=='(')
				opt.push(*i);
		}
	}
	while(!opt.empty())
	{
		rpn.push_back(opt.top());
		opt.pop();
	}
	return;
}

void calc()
{
	if(!lexer())
		return;
	parser();
	// begin calculation
	
	std::stack<token> calculator;
	for(std::list<token>::iterator i=rpn.begin();i!=rpn.end();++i)
	{
		std::cout<<"input sequence: ";
		for(std::list<token>::iterator j=i;j!=rpn.end();++j)
		{
			if(j->type==__number)
				std::cout<<j->num<<" ";
			else
				std::cout<<j->oprt<<" ";
		}
		std::cout<<std::endl;
		print_stack(calculator);
		if(i->type==__number)
			calculator.push(*i);
		if(i->type==__operator)
		{
			token tmp1,tmp2;
			if(!calculator.empty())
				tmp1=calculator.top();
			else
			{
				std::cout<<">>[Error] lack number at the operator "<<i->oprt<<"."<<std::endl;
				return;
			}
			calculator.pop();
			if(!calculator.empty())
				tmp2=calculator.top();
			else
			{
				std::cout<<">>[Error] lack number at the operator "<<i->oprt<<"."<<std::endl;
				return;
			}
			calculator.pop();
			switch(i->oprt)
			{
				case '+':tmp2.num+=tmp1.num;break;
				case '-':tmp2.num-=tmp1.num;break;
				case '*':tmp2.num*=tmp1.num;break;
				case '/':tmp2.num/=tmp1.num;break;
			}
			calculator.push(tmp2);
		}
	}
	std::cout<<"input sequence:"<<std::endl;
	print_stack(calculator);
	return;
}

int main()
{
	while(1)
	{
		std::cout<<">>";
		std::cin>>sequence;
		if(sequence=="exit")
			break;
		// check if the input sequence begins and ends with '#'
		if(sequence[0]!='#' && sequence[sequence.length()-1]!='#')
		{
			std::string filename=sequence;
			sequence="##";
			std::ifstream fin(filename);
			if(fin.fail())
			{
				std::cout<<">>[Error] cannot open file \'"<<filename<<"\'."<<std::endl;
				continue;
			}
			else
			{
				char c;
				sequence="";
				while(!fin.eof())
				{
					c=fin.get();
					if(fin.eof())
						break;
					sequence+=c;
				}
			}
			fin.close();
		}
		calc();
	}
	return 0;
}
