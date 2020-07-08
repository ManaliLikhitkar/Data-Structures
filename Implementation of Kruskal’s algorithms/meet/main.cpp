//============================================================
// Name        : Assignment07.cpp
// Author      : Meet Mandhane
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================

#include <queue>
#include <string.h>
#include <iostream>
using namespace std;

struct node;

typedef struct frnd
{
	node *link;
	frnd *nextfriend;
	int weight;
	bool intree;
    bool visited;
}frnd;

typedef struct node
{
	char name[15];
	node *next;
	frnd *friendnode;
	bool intree;
	bool bfsvisited;
}node;

class graph
{
	node *first;
public:
	graph();
	int create();
	void display();
	void insert();
	void cfriend();
	bool connect(node*,node*,int);
	node* searchnode(char[]);
	void MST(int);
	bool cycle(node*,frnd*);
	bool BFS(node*,frnd*);
};

graph::graph()
{
	first=new node();
	first->next=NULL;
}

int graph::create()
{
	int n;
	cout<<"Enter the no. of users:";
	cin>>n;
	node *t=first;
	cout<<"Enter your name.:";
	cin>>t->name;
	t->friendnode=NULL;
	for(int i=1;i<n;i++)
	{
		node *temp=new node();
		cout<<"\nEnter your name.:";
		cin>>temp->name;
		temp->friendnode=NULL;
		t->next=temp;
		t=temp;
		temp=temp->next;
	}
	return n;
}

void graph::display()
{
	node *temp=first;
	while(temp!=NULL)
	{
		frnd *t=temp->friendnode;
		while(t!=NULL)
		{
			cout<<t->link->name<<"\n";
			t=t->nextfriend;
		}
		temp=temp->next;
	}
}

void graph::insert()
{
	node *temp=new node();
	cout<<"Enter your name.:";
	cin>>temp->name;
	temp->next=NULL;
	node *t=first;
	while(t->next!=NULL)
		t=t->next;
	t->next=temp;
}

node* graph::searchnode(char t[])
{
	node *temp=first;
	while(temp!=NULL)
	{
		if(strcmp(t,temp->name)==0)
			return temp;
		temp=temp->next;
	}
	return temp;
}

bool graph::connect(node *temp1,node *temp2,int w)
{
	if(temp1->friendnode==NULL)
	{
		temp1->friendnode=new frnd();
		temp1->friendnode->link=temp2;
		temp1->friendnode->weight=w;
		temp1->friendnode->nextfriend=NULL;
	}
	else
	{
		frnd* t=temp1->friendnode;
		if(strcmp(t->link->name,temp2->name)==0)
			return 0;
		while(t->nextfriend!=NULL)
		{
			if(strcmp(t->link->name,temp2->name)==0)
				return 0;
			t=t->nextfriend;
		}
		t->nextfriend=new frnd();
		t=t->nextfriend;
		t->link=temp2;
		t->weight=w;
		t->nextfriend=NULL;
	}
	return 1;
}

void graph::cfriend()
{
	int n;
	char firstname[15],secondname[15];
	node *temp1,*temp2;
	cout<<"Enter the no. of friendship pairs you want to add:";
	cin>>n;
	for(int i=0;i<n;i++)
	{
	    do
        {
            cout<<"Enter the first name:";
            cin>>firstname;
            temp1=searchnode(firstname);
            if(temp1!=NULL)
                break;
            cout<<"User not found";
        }while(1);
        do
        {
            cout<<"Enter the second name:";
            cin>>secondname;
            temp2=searchnode(secondname);
             if(temp2!=NULL)
                break;
            cout<<"User not found";
        }while(1);
        int w;
        cout<<"Enter the weight of the edge.:";
        cin>>w;
        if(!connect(temp1,temp2,w))
          cout<<"They are already friends.\n";
        connect(temp2,temp1,w);
	}
}

bool graph::BFS(node *temp,frnd *minw)
{
    queue <node*>q;
    node *t=temp;
	while(t)
	{
		t->bfsvisited=false;
		t=t->next;
	}
	q.push(temp);
	while(!q.empty())
	{
		t=q.front();
		q.pop();
		if(!t->bfsvisited)
		{
			if(t==minw->link)
				return true;
			t->bfsvisited=1;
			frnd *f=t->friendnode;
			while(f)
			{
			    if(f->intree)
                    q.push(f->link);
				f=f->nextfriend;
			}
		}
	}
	return false;
}

bool graph::cycle(node *temp,frnd *f)
{
    if(!(temp->intree && f->link->intree))
        return false;
    else if(BFS(temp,f))
        return true;
    else
        return false;
}

void graph::MST(int n)
{
	node *temp=first;
	frnd *f;
	while(temp)
	{
		temp->intree=false;
		f=temp->friendnode;
		while(f)
		{
			f->intree=false;
			f->visited=false;
			f=f->nextfriend;
		}
		temp=temp->next;
	}
	int i=0;
	while(i<n-1)
	{
	    node *minv;
		frnd *minw;
		temp=first;
		int min=9999;
		while(temp)
		{
			f=temp->friendnode;
			while(f)
			{
				if(!f->intree && min>=f->weight && !cycle(temp,minw))
				{
					min=f->weight;
					minv=temp;
					minw=f;
				}
				f=f->nextfriend;
			}
			temp=temp->next;
		}
		minw->intree=true;
		minw->link->intree=true;
        minv->intree=true;
        minw->visited=true;
        temp=minw->link;
        f=temp->friendnode;
        while(f)
        {
            if(f->link==minv)
            {
                f->visited=false;
                f->intree=true;
            }
            f=f->nextfriend;
        }
		i++;
	}
	temp=first;
	i=0;
	while(temp)
	{
		f=temp->friendnode;
		while(f)
		{
			if(f->intree && f->visited)
                cout<<temp->name<<"<--->"<<f->link->name<<"\t"<<f->weight<<"\n";
			f=f->nextfriend;
		}
		temp=temp->next;
	}
}

int main()
{
	graph G;
	int n;
	n=G.create();
	int ch;
	do
	{
		cout<<"\n\t\tMENU:\n\t\t1.Insert user\n\t\t2.Add friends\n\t\t3.Display users\n\t\t4.Minimum spanning tree\n\t\t5.Exit\nEnter the correct choice.:";
	    cin>>ch;
	    switch(ch)
	    {
	     case 1:
	    	 G.insert();
	    	 n++;
	         break;
	     case 2:
	    	 G.cfriend();
	         break;
	     case 3:
	         G.display();
	         break;
	     case 4:
	    	 G.MST(n);
	    	 break;
	     case 5:
	         cout<<"Thank you";
	         break;
	     default:
	         cout<<"Wrong choice";
	     }
	  }while(ch!=5);
	return 0;
}
