/*============================================================================
                               GRAPHS
Assignment no. : 6
Roll no.       : 23333
Batch          : F11
============================================================================*/
#include <iostream>
#include <string.h>
#include <stack>
#include <queue>

using namespace std;

struct vertex
{
	char name[30];
	int visited;
	int friends;
	int intree;
	struct edge *adj;
	struct vertex *next;
};

struct edge
{
	struct vertex *v;
	struct edge *adj;
	int weight;
	int intree;
	int selected;
};

class graph
{
public:
	vertex *first;
	int totver;

	graph()
	{
		first=NULL;
		totver=0;
	}

	void init()
	{
		vertex *temp=first;
		edge* e;
		while(temp!=NULL)
		{
			temp->visited=0;
			temp->intree=0;
			e=temp->adj;
			while(e)
			{
				e->intree=0;
				e->selected=0;
				e=e->adj;
			}
			temp=temp->next;
		}
	}

	vertex* getVertex()
	{
		vertex *temp=new vertex();
		cout<<"Name : ";
		cin>>temp->name;

		temp->adj=NULL;
		temp->next=NULL;
		return temp;
	}

	void create_network(vertex *v)
	{
		if(first==NULL)
		{
			first=new vertex();
			strcpy(first->name, v->name);
			first->next=NULL;
		}
		else
		{
			vertex *temp=first;
			while(temp->next!=NULL)
				temp=temp->next;
			temp->next=new vertex();
			temp=temp->next;
			strcpy(temp->name, v->name);
			temp->next=NULL;
		}
	}

	void create()
	{
		vertex *v;
		cout<<"Create Network :-\n";
		cout<<"Enter the total number of people : ";
		cin>>totver;
		for(int i=1 ; i<=totver; i++)
		{
			cout<<"\n\nRecord no. "<<i<<"\n";
			v=getVertex();
			create_network(v);
		}
	}

	vertex * searchVertex(char key[])
	{
		vertex *temp=first;
		while(temp!=NULL)
		{
			if(strcmp(key,temp->name)==0)
			{
				return temp;
			}
			temp=temp->next;
		}
		return NULL;
	}

	void insertFriend()
	{
		char f1[30],f2[30];
		int wt;
		edge *e1=new edge;
		edge *e2=new edge;
		edge *t;
		cout<<"Enter name of first friend:\t";
		cin>>f1;
		cout<<"Enter name of second friend:\t";
		cin>>f2;
		cout<<"Enter weight of edge:\t";
		cin>>wt;

		vertex *fr1=searchVertex(f1);
		vertex *fr2=searchVertex(f2);

		if(fr1!=NULL && fr2!=NULL)
		{
			e1->v=fr2;
			e1->adj=NULL;
			e1->weight=wt;

			t=fr1->adj;
			if(t==NULL)
			{
				fr1->adj=e1;
				fr1->friends++;
			}
			else
			{
				while(t->adj!=NULL)
					t=t->adj;
				t->adj=e1;
				fr1->friends++;
			}

			e2->v=fr1;
			e2->adj=NULL;
			e2->weight=wt;

			t=fr2->adj;
			if(t==NULL)
			{
				fr2->adj=e2;
				fr2->friends++;
			}
			else
			{
				while(t->adj!=NULL)
					t=t->adj;
				t->adj=e2;
				fr2->friends++;
			}
		}
		else
		{
			cout<<"\n\nInvalid vertices!!";
		}
	}

	void display()
	{
		vertex *temp=first;
		edge *e;
		do
		{
			e=temp->adj;
			cout<<temp->name;
			while(e!=NULL)
			{
				cout<<"-> ( "<<e->weight<<" ) "<<e->v->name;
				e=e->adj;
			}
			temp=temp->next;
			cout<<"\n";
		}while(temp!=NULL);
	}

	int bfs(vertex* curr,edge* temp)
	{

		queue<vertex*> q;
		q.push(curr);
		vertex* p,*t;
		edge* newed;
		t=first;
		while(t)
		{
			t->visited=0;
			t=t->next;
		}

		//curr->visited=1;
		while(!q.empty())
		{
			p=q.front();
			q.pop();
			if(!p->visited)
			{
				if(p==temp->v)
					return 1;
				newed=p->adj;
				while(newed)
				{
					if(newed->selected)
						q.push(newed->v);
					newed=newed->adj;
				}
			}
		}
		return 0;
	}

	int checkcycle(vertex* curr,edge*temp)
	{
		if(curr->intree!=1 || temp->v->intree!=1)
			return 0;
		else if(bfs(curr,temp))
			return 1;
		return 0;
	}

	void mst()
	{
		int min=9999,i=0;
		vertex* v,*t;
		edge* e;
		edge* minimume;
		vertex* minimumv;

		init();

		t=first;
		while(i<totver-1)
		{
			t=first;
			min=9999;
			while(t)
			{
				e=t->adj;
				while(e)
				{
					if(!e->selected && e->weight<=min && !checkcycle(t,e))
					{
						minimume=e;
						min=e->weight;
						minimumv=t;
					}
					e=e->adj;
				}
				t=t->next;
			}
				minimumv->intree=1;
				minimume->v->intree=1;
				minimume->intree=1;
				minimume->selected=1;

				cout<<minimumv->name<<"-> ( "<<minimume->weight<<" )"<<minimume->v->name<<"\n";

				v=minimume->v;
				e=v->adj;

				while(e)
				{
					if(e->v==minimumv)
					{
						e->intree=0;
						e->selected=1;
					}
					e=e->adj;
				}
			i++;
		}
	}

};

int main()
{
	graph g;
	g.create();
	int choice=0;
	do
	{
		cout<<"\n\nMENU\n1.Insert Friends\n2.Display network\n3.Display MST\n4.Exit\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
		case 1:
			g.insertFriend();
			break;
		case 2:
			g.display();
			break;
		case 3:
			g.mst();
			break;
		case 4:
			cout<<"\n\nTHANK YOU!!";
			break;
		default:
			cout<<"\n\nPlease enter a valid choice!!";
		}
	}while(choice!=4);
	return 0;
}
