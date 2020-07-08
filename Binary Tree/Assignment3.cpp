/*============================================================================
                           BINARY TREES
Assignment no. : 3
Roll no.       : 23333
Batch          : F11
============================================================================*/

#include <iostream>
#include "queue.h"
#include "queue.cpp"
#define COUNT 10
using namespace std;
class binary_tree
{
	struct node
	{
		struct node *left,*right;
		char data;
	};
	node *root,*new_tree;
	int htl,rtl;
public:
	binary_tree()
	{
		root=new node;
		root->left=NULL;
		root->right=NULL;
		htl=rtl=0;
	}

	node * create()
	{
		struct node *p;
		char x;
		cout<<"Enter data (# for no data) : ";
		cin>>x;
		if(x=='#')
			return NULL;
		p=new node;
		p->data=x;
		cout<<"Enter left child of "<<x<<endl;
		p->left=create();
		cout<<"Enter right child of "<<x<<endl;
		p->right=create();
		return p;
	}

	void create_tree()
	{
		root=create();
	}

	void insert()
	{
		node *t;
		int x; char ch;
		if(root==NULL)
		{
			t=new node;
			cout<<"Enter data : "; cin>>t->data;
			t->left=NULL;
			t->right=NULL;
			root=t;
		}
		else
		{
			t=root;
			while(t!=NULL)
			{
				ch=t->data;
				cout<<"Enter 1 to insert at left of "<<ch<<", 2 to insert at right of "<<ch<<" :";
				cin>>x;
				if(x==1)
				{
					if(t->left==NULL)
					{
						cout<<"Enter data : "; cin>>ch;
						t->left=new node;
						t=t->left;
						t->data=ch;
						t->left=NULL;
						t->right=NULL;
						cout<<"\nInserted successfully!\n";
						break;
					}
					else
						t=t->left;
				}
				if(x==2)
				{
					if(t->right==NULL)
					{
						cout<<"Enter data : "; cin>>ch;
						t->right=new node;
						t=t->right;
						t->data=ch;
						t->left=NULL;
						t->right=NULL;
						cout<<"\nInserted successfully!\n";
						break;
					}
					else
						t=t->right;
				}
			}
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
	
	void display_tree()
    {
    	print(root,0);
		//display(root);
    }

	/*void display(node *root1)
	{
		if(root1!=NULL)
		{
			queue<node*>q;
			node *t=root1;
			while(t!=NULL)
			{
				  cout<<"\t"<<t->data;
				if(t->left!=NULL)
				  q.enqueue(t->left);
				if(t->right!=NULL)
				  q.enqueue(t->right);
				if(q.isempty())
					t=NULL;
				else
					t=q.dequeue();
				cout<<endl;
			}
		}
		else
			cout<<"\n\nTree empty!!";
	}*/

    void display_leaves()
    {
	displayLeaves(root);
    }
    void displayLeaves(node *temp)
    {
        if(temp!=NULL)
        {
            if(temp->left==NULL && temp->right==NULL)
            {
                cout<<temp->data<<"\t";
            }
            displayLeaves(temp->left);
            displayLeaves(temp->right);
        }
    }

    void count_height()
    {
        int n=height(root);
        cout<<"\n\nDepth of the tree is : "<<n;
    }

    int height(node *temp)
    {
        if(temp==NULL)
            return 0;
        else
        {
            htl=height(temp->left)+1;
            rtl=height(temp->right)+1;
        }
        if(htl>rtl)
            return htl;
        else
            return rtl;
    }
    
    void copy()
    {
	   new_tree=copyTree(root);
	   cout<<"Tree copied!!\nNew tree:\n";
	   display(new_tree);
    }
    
    node* copyTree(node *root)
    {
		node* newtree=NULL;
		if(root!=NULL)
		{
			newtree=new node();
			newtree->data=root->data;
			newtree->left=copyTree(root->left);
			newtree->right=copyTree(root->right);
		}
		return newtree;
    }
	
};


int main()
{
	int choice;
	binary_tree b;
	b.create_tree();
	do
	{
		cout<<"\n\nMENU:\n1.Insert\n2.Display\n3.Depth of a tree\n4.Display leaf-nodes\n5.Create a copy of tree\n6.Exit\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
		case 1:
			b.insert();
			break;
		case 2:
		    b.display_tree();
			break;
		case 3:
		    b.count_height();
			break;
		case 4:
		    b.display_leaves();
			break;
		case 5:
		    b.copy();
			break;
		case 6:
			cout<<"\n\nTHANK YOU!!";
			break;
		default:
			cout<<"\n\nPlease enter a valid choice!!";
		}
	}while(choice!=6);
}
