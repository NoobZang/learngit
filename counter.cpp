#include <iostream> 
#include <string>
using namespace std;

template <typename E> class AStack
{
private:
	int maxSize;
	int top;
  	E *listArray;

public:
  	AStack(int size = 30)
    {	maxSize = size;
		top = 0;
		listArray = new E[size];
	}

  	~AStack() { delete [] listArray; }
  
  	void clear() { top = 0; }

  	void push(const E& it) 
	{
    	if(top != maxSize)
    		listArray[top++] = it;
  		else
	  		cout << "Stack is full..." << endl;
	}

  	E pop() 
	{ 
    	if(top != 0)
    		return listArray[--top];
  		else
	  		cout << "Stack is empty..." << endl;
	}

  	const E& topValue() const {
    if(top != 0)
    	return listArray[top-1];
    else
    	cout << "Stack is empty..." << endl;
  	}

  	int length() const { return top; }
};


bool IsOperator(const char& token) 
{
	if((token == '+') || (token == '-')|| (token == '*') || (token == '/'))
		return true;
	return false;
}


bool IsHigher(const char& curr,const char& prev)
{	if(prev=='(')
		return true;
	else if((curr=='*' || curr=='/' ) && (prev=='+' || prev=='-'))
		return true;
	else
		return false;
}


string convertInfixToPRN(string& exp)
{	AStack<char> l;
	string ans="";
	for(int i=0;i<exp.length();i++)
	{	if(IsOperator(exp[i]))
		{	while(1)
			{	if(l.length()==0 ||(l.length()!=0 && IsHigher(exp[i],l.topValue()) ))
				{	l.push(exp[i]);
					break;
				}
				else
					ans = ans + l.pop() + ' ';	
			}
		}

		else if(exp[i]=='(')
			l.push('(');
		
		else if(exp[i]==')')
		{	while(l.topValue()!='(')
				ans = ans + l.pop() + ' ';
			l.pop();
		}
		
		else                //数字可能不止一位 
		{	string num="";
			int j;
			for(j=i;j<exp.length();j++)
			{	if(exp[j]!='(' && exp[j]!=')' && !IsOperator(exp[j]))
					num = num + exp[j];
				else
					break;
			}
			i=j-1;         //读完数字以后更新i，之后再加上1刚好到位置 
			ans = ans + num + ' ';
		}
	}
	while(l.length()!=0)
		ans=ans + l.pop() + ' ';
	ans.erase(ans.length()-1);
	return ans;
}


int comput(string& exp)
{	int a,b;
	AStack<int> l;
	for(int i=0;i<exp.length();i++)
	{	if(IsOperator(exp[i]))
		{	b = l.pop();
			a = l.pop();
			if(exp[i]=='+')
				l.push(a+b);
			else if(exp[i]=='-')
				l.push(a-b);
			else if(exp[i]=='*')
				l.push(a*b);
			else if(exp[i]=='/')
				l.push(a/b);
		}

		else if(exp[i] == ' ')
			continue;
		
		else
		{	string num="";
			int j;
			for(j=i;j<exp.length();j++)
			{	if(!IsOperator(exp[j]) && exp[j]!=' ')
					num = num + exp[j];
				else
					break;
			}
			i=j-1;              //读完数字以后更新i，之后再加上1刚好到位置  
			int intnum=atoi(num.c_str());   //string类转为int类 
			l.push(intnum);
		}
	}
	return l.pop();
}


 
int main()
{	string s;
	cin >> s;
	cout << s << endl;

	string exp = convertInfixToPRN(s);
	cout << exp << endl;
	
	int ans = comput(exp);
	cout << ans << endl;
}
