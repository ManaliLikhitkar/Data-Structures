/*============================================================================
                         EXPRESSION CONVERSION
 Assignment no. : 1
 Roll no.       : 23333
 Batch          : F11
============================================================================*/

#include <iostream>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "stack.cpp"
using namespace std;

class EXP
{
private:
	char str[20];
public:
	stack<char> S;
	stack<int> S1;
	void input()
	{
		cout<<"Enter expression: ";
		cin.ignore();
		cin.getline(str,20);
	}
	int priority(char c)
	{
		switch(c)
		{
		case '-':
			return 1;
		case '+':
			return 1;
		case '*':
			return 2;
		case '/':
			return 2;
		case '^':
			return 3;
		case '(':
			return 0;
		case ')':
			return 0;
		default:
			return -1;
		}
	}
	int calculate(int op1, int op2, char c)
	{
		int res;
		switch(c)
		{
		case '+':
			res= op1+op2;
			break;
		case '-':
			res= op1-op2;
			break;
		case '*':
			res= op1*op2;
			break;
		case '/':
			res= op1/op2;
			break;
		case '^':
			res=pow(op1,op2);
			break;
		}
		return res;
	}
	int associativity(char x)
	{
		if(x=='^')
			return 1;
		return 0;
	}

	void convert_postfix(char m[],char n[],int dec)
	{
		char c;
		int i=0,j=0;
		if(dec==1)
			cout<<"Postfix expression : ";
		else if(dec==0)
			strcpy(str,n);
		while(str[i]!='\0')
		{
			c=str[i];
			if(isalpha(c) || isdigit(c))
			{
				if(dec==1)
					cout<<c;
				else
				{
					m[j]=c;
					j++;
				}
			}
			else if(c=='(')
				S.push(c);
			else if(c==')')
			{
				char y=S.pop();
				while(y!='(')
				{
					if(dec==1)
						cout<<y;
					else
					{
						m[j]=y;
						j++;
					}
					y=S.pop();
				}
			}
			else
			{
				while(!S.isempty() && priority(S.get_top())>=priority(c))
				{
					if(c==S.get_top())
					{
						if(associativity(c))
						{
							break;
						}
						else
						{
							if(dec==1)
								cout<<S.pop();
							else
							{
								m[j]=S.pop();
								j++;
							}
						}
					}
					else
					{
						if(dec==1)
							cout<<S.pop();
						else
						{
							m[j]=S.pop();
							j++;
						}
					}

				}
				S.push(c);
			}
			i++;
		}
		while(!S.isempty())
		{
			char c=S.pop();
			if(dec==1)
				cout<<c;
			else
			{
				m[j]=c;
				j++;
			}
		}
		m[j]='\0';
	}

	void convert_prefix(char m[],char n[],int dec)
	{
		char str1[20];
		char c;
		int i=0,j=0;
		if(dec==1)
			cout<<"Prefix expression : ";
		else if(dec==0)
			strcpy(str,n);
		int l=strlen(str);
		for(i=0;i<l;i++)
		{
			if(str[l-i-1]=='(')
				str1[i]=')';
			else if(str[l-i-1]==')')
				str1[i]='(';
			else
				str1[i]=str[l-1-i];
		}
		str1[i]='\0';
		i=0;
		while(str1[i]!='\0')
		{
			c=str1[i];
			if(isalpha(c) || isdigit(c))
			{
				m[j]=c;
				j++;
			}
			else if(c=='(')
				S.push(c);
			else if(c==')')
			{
				char y=S.pop();
				while(y!='(')
				{
					m[j]=y;
					j++;
					y=S.pop();
				}
			}
			else
			{
				while(priority(S.get_top())>priority(c))
				{
					if(c==S.get_top())
					{
						if(associativity(c))
						{
							m[j]=S.pop();
							j++;

						}
						else
							break;
					}
					else
					{
						m[j]=S.pop();
						j++;
					}


				}
				S.push(c);
			}
			i++;
		}
		while(!S.isempty())
		{
			char c=S.pop();
			m[j]=c;
			j++;
		}
		m[j]='\0';
		l=strlen(m);
		for(i=0;i<l;i++)
		{
			str1[i]=m[l-i-1];
		}
		str1[i]='\0';
		if(dec==1)
			cout<<str1<<"\n";
		else
			strcpy(m,str1);
	}

	void pre_eval()
	{
		char m[20];
		convert_prefix(m,str,0);
		cout<<"\n\nPrefix expression : "<<m<<endl;
		int op1,op2,i=0;
		i=strlen(m)-1;
		while(m[i]!='\0')
		{
			int n;
			char c=m[i];
			if(isalpha(c))
			{
				cout<<"Enter the value of "<<c<<":";
				cin>>n;
				S1.push(n);
			}
			else if(isdigit(c))
			{
				n=c-'0';
				cout<<n;
				S.push(n);
			}
			else
			{
				op1=S1.pop();
				op2=S1.pop();
				n=calculate(op1,op2,c);
				S1.push(n);
			}
			i--;
		}
		cout<<"\nAnswer:"<<S1.pop()<<endl;
	}

	void post_eval()
	{
		char m[20];
		convert_postfix(m,str,0);
		cout<<"\n\nPostfix expression : "<<m<<endl;
		int op1,op2,i=0;
		while(m[i]!='\0')
		{
			int n;
			char c=m[i];
			if(isalpha(c))
			{
				cout<<"Enter the value of "<<c<<":";
				cin>>n;
				S1.push(n);
			}
			else if(isdigit(c))
			{
				n=c-'0';
				cout<<n;
				S.push(n);
			}
			else
			{
				op2=S1.pop();
				op1=S1.pop();
				n=calculate(op1,op2,c);
				S1.push(n);
			}
			i++;
		}
		cout<<"\nAnswer : "<<S1.pop()<<endl;
	}

	int validate()
	{
		int countop=0,countcl=0,l=strlen(str),i,j=0,oprtr=0,oprnd=0;
		char c;
		char temp[50];
		for(i=0;i<l;i++)
		{
			c=str[i];
			if(c=='(')
				countop++;
			else if(c==')')
			{
				countcl++;
				if(countcl>countop)
					return 0;
			}
			else
			{
				temp[j]=c;
				j++;
				if(isalpha(c)||isdigit(c))
					oprnd++;
				else
					oprtr++;
			}
		}
		temp[j]='\0';
		if(countop!=countcl || oprtr!=(oprnd-1))
			return 0;
		l=strlen(temp);
		for(i=0;i<l;i++)
		{
			c=temp[i];
			if(i%2==0)
				if(!isalpha(c)&&!isdigit(c))
					return 0;
			if(i%2==1)
				if(isalpha(c)||isdigit(c))
					return 0;
		}
		return 1;
	}

};

int main()
{
	char str[20]="";
	char t[20]="";
	EXP e;
	int choice=0;
	do
	{
		//setvbuf( stdout, NULL, _IONBF, 0 );
		cout<<"\n\nMENU\n1.Infix to postfix conversion\n2.Infix to prefix conversion\n3.Postfix evaluation\n4.Prefix evaluation\n5.Exit\nEnter your choice: ";
		cin>>choice;
		switch(choice)
		{
		case 1:
		{
			e.input();
			if(e.validate())
				e.convert_postfix(str,t,1);
			else
				cout<<"Enter valid expression!!\n";
			break;
		}
		case 2:
			e.input();
			if(e.validate())
				e.convert_prefix(str,t,1);
			else
				cout<<"Enter valid expression!!\n";
			break;
		case 3:
			e.input();
			if(e.validate())
				e.post_eval();
			else
				cout<<"Enter valid expression!!\n";
			break;
		case 4:
			e.input();
			if(e.validate())
				e.pre_eval();
			else
				cout<<"Enter valid expression!!\n";
			break;
		case 5:
			cout<<"THANK YOU!!\n";
			break;
		default:
			cout<<"Please enter a valid number!!\n";
		}
	}while(choice!=5);
}
