/*============================================================================
                           EXPERESSION TREE
Assignment no. : 4
Roll no.       : 23333
Batch          : F11
============================================================================*/

#include <iostream>
#include "stack.h"
#include "stack.cpp"
using namespace std;

class binary_tree
{
	struct node
	{
		char data;
		node *left,*right;
	};
	node *root;
	stack<node*> s;
	char exp[50];
public:
	void input()
	{
		cout<<"Enter the expression in postfix form : ";
		cin>>exp;
	}

	void create()
	{
		int i=0;
		node *temp=NULL;
		while(exp[i]!='\0')
		{
			temp=new node();
			temp->data=exp[i];
			if(isalpha(exp[i]) || isdigit(exp[i]))
			{
				s.push(temp);
			}
			else
			{
				temp->right=s.pop();
				temp->left=s.pop();
				s.push(temp);
			}
			i++;
		}
		root=temp;
	}

	void call(int i)
	{
		switch(i)
		{
		case 1:
			rec_inorder(root);
			break;
		case 2:
			rec_preorder(root);
			break;
		case 3:
			rec_postorder(root);
			break;
		case 4:
			inorder(root);
			break;
		case 5:
			preorder(root);
			break;
		case 6:
			postorder(root);
			break;
		}
	}

	void rec_inorder(node *t)
	{
		if(t!=NULL)
		{
			rec_inorder(t->left);
			cout<<t->data;
			rec_inorder(t->right);
		}
	}

	void rec_preorder(node *t)
	{
		if(t!=NULL)
		{
			cout<<t->data;
			rec_preorder(t->left);
			rec_preorder(t->right);
		}
	}

	void rec_postorder(node *t)
	{
		if(t!=NULL)
		{
			rec_postorder(t->left);
			rec_postorder(t->right);
			cout<<t->data;
		}
	}

	void inorder(node *t)
	{
		stack<node*> s;
		while(1)
		{
			while(t!=NULL)
			{
				s.push(t);
				t=t->left;
			}
			if(s.isempty())
			{
				break;
			}
			t=s.pop();
			cout<<t->data;
			t=t->right;
		}
	}

	void preorder(node *t)
	{
		stack<node*> s;
		while(1)
		{
			while(t!=NULL)
			{
				cout<<t->data;
				s.push(t);
				t=t->left;
			}
			if(s.isempty())
			{
				break;
			}
			t=s.pop();
			t=t->right;
		}
	}

	void postorder(node *t)
	{
		stack<node*> s1;
		stack<node*> s2;
		s1.push(t);
		while(!s1.isempty())
		{
			node *temp=s1.pop();
			s2.push(temp);
			if(temp->left!=NULL)
				s1.push(temp->left);
			if(temp->right!=NULL)
				s1.push(temp->right);
		}
		while(!s2.isempty())
		{
			node *t1=s2.pop();
			cout<<t1->data;
		}
	}


};

int main()
{
	int choice=0,ch=0;
	binary_tree b;
	do
	{
		cout<<"\n\nMENU:\n1.Create tree\n2.Recursive traversal\n3.Non-recursive traversal\n4.Exit\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				b.input();
				b.create();
				break;
			case 2:
				do
				{
					cout<<"\n\n1.Inorder\n2.Preorder\n3.Postorder\n4.Main menu\nEnter your choice : ";
					cin>>ch;
					switch(ch)
					{
					case 1:
						b.call(1);
						break;
					case 2:
						b.call(2);
						break;
					case 3:
						b.call(3);
						break;
					case 4:
						cout<<"\n\nReturning to main menu!!";
						break;
					default:
						cout<<"\nPlease enter a valid choice!";
					}
				}while(ch!=4);
				break;
			case 3:
				do
				{
					cout<<"\n\n1.Inorder\n2.Preorder\n3.Postorder\n4.Main menu\nEnter your choice : ";
					cin>>ch;
					switch(ch)
					{
					case 1:
						b.call(4);
						break;
					case 2:
						b.call(5);
						break;
					case 3:
						b.call(6);
						break;
					case 4:
						cout<<"\n\nReturning to main menu!!";
						break;
					default:
						cout<<"\nPlease enter a valid choice!";
					}
				}while(ch!=4);
				break;
			case 4:
				cout<<"\nTHANK YOU!!";
				break;
			default:
				cout<<"\nPlease enter a valid choice!";
		}
	}while(choice!=4);
}
