/*============================================================================
                           BINARY SEARCH TREE
Assignment no. : 5
Roll no.       : 23333
Batch          : F11
============================================================================*/

#include <iostream>
#include <string.h>
#define COUNT 10
using namespace std;
class BST
{
	struct node
	{
		char data;
		struct node *left, *right;
	};
	node *root=NULL,*root_mirror=NULL;
	char x;
public:
	node * create(node *t,char x)
	{
		node *t1=new node;
		if(t==NULL)
		{
			t1->data=x;
			t1->left=NULL;
			t1->right=NULL;
			t=t1;
			return t;
		}
		if(x<t->data)
			t->left=create(t->left,x);
		else if(x>t->data)
			t->right=create(t->right,x);
		else
			cout<<"Duplication not allowed!!\n";
		return t;
	}

	void call(int i)
	{
		switch(i)
		{
		case 0:
			do
			{
				cout<<"Enter data (# for no data) : ";
				cin>>x;
				if(x!='#')
				{
					root=create(root,x);
				}
			}while(x!='#');
			//display(root);
			break;
		case 1:
			cout<<"Enter data (# for no data) : ";
			cin>>x;
			if(x!='#')
				root=create(root,x);
			print(root,0);
			break;
		case 2:
			DeleteNode();
			break;
		case 3:
		{
			if(root!=NULL)
			{
				char key;
				cout<<"\n\nEnter the data to be searched : ";
				cin>>key;
				node *t=search(root,key);
				if(t!=NULL)
					cout<<"\nData found!!";
				else
					cout<<"\nData not found!!";
			}
			else
				cout<<"\n\nTree empty!!";
			break;
		}
		case 4:
			if(root!=NULL)
			{
				mirror(root);
				cout<<"\n\nMirror image of the tree:\n";
				display(root);
				mirror(root);
			}
			else
				cout<<"\n\nTree empty!!";
			break;
		case 5:
			if(root!=NULL)
				display(root);
			else
				cout<<"\n\nTree empty!!";
			break;
		case 6:
			if(root!=NULL)
				print(root,0);
			else
				cout<<"\n\nTree empty!!";
			break;
		}
	}

	node* findmin(node* r)
	{
		node* temp=NULL;
		if(r->left==NULL)
			temp=r;
		else
			temp=findmin(r->left);
		return temp;
	}

	node* deleteNode(node* r,char key)
	{
		node* temp=NULL;
		if(r!=NULL)
		{
			if(key<r->data)
			{
				r->left=deleteNode(r->left,key);
				temp=r;
			}
			else if(key>r->data)
			{
				r->right=deleteNode(r->right,key);
				temp=r;
			}
			else if(key==r->data)	//node found
			{
				if(r->left==NULL&&r->right==NULL)
				{
					delete(r);
					temp=NULL;
				}
				else if(r->left==NULL)
				{
					temp=r->right;
					delete(r);
				}
				else if(r->right==NULL)
				{
					temp=r->left;
					delete(r);
				}
				else
				{
					temp=findmin(r->right);
					r->data=temp->data;
					r->right=deleteNode(r->right,temp->data);
					temp=r;
				}
			}
		}
		else
		{
			cout<<"\nNode not found!\n";
			temp=r;
		}
		return temp;
	}

	void DeleteNode()
	{
		char key;
		cout<<"\nEnter data to delete:\t";
		cin>>key;
		root=deleteNode(root,key);
	}

	void display(node *t)
	{
		if(t!=NULL)
		{
			display(t->left);
			cout<<t->data<<"  ";
			display(t->right);
		}
	}

	void print(node* root,int space)
	{
		if(root==NULL)
			return;
		space+=COUNT;
		print(root->right,space);
		cout<<"\n";
		for(int i=COUNT;i<space;i++)
			cout<<" ";
		cout<<root->data;
		print(root->left,space);
	}

	node * search(node *t, char key)
	{
		if(t==NULL)
			return NULL;
		else
		{
			if(key==t->data)
				return t;
			else if(key<t->data)
				return search(t->left,key);
			return search(t->right,key);
		}
	}

	void mirror(node *t)
	{
		if(t!=NULL)
		{
			node *temp=t->left;
			t->left=t->right;
			t->right=temp;
			mirror(t->left);
			mirror(t->right);
		}
		//return t;
	}
};

int main()
{
	int choice=0;
	BST b;
	cout<<"CREATE BINARY SEARCH TREE:-\n";
	b.call(0);
	do
	{
		cout<<"\n\nMENU:\n1.Insert\n2.Delete\n3.Search\n4.Mirror image\n5.Display\n6.Display level wise\n7.Exit\nEnter your choice : ";
		cin>>choice;
		switch(choice)
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
			b.call(4);
			break;
		case 5:
			b.call(5);
			break;
		case 6:
			b.call(6);
			break;
		case 7:
			cout<<"\n\nTHANK YOU!!";
			break;
		default:
			cout<<"\nPlease enter a valid choice!";
		}
	}while(choice!=7);
}
