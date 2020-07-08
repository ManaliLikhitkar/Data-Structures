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
//#define max 30
using namespace std;
struct date
{
	int day;
	int month;
	int year;
};

struct vertex
{
	char name[30];
	int comments;
	int visited;
	int friends;
	struct date dob;
	struct edge *adj;
	struct vertex *next;
};

struct edge
{
	struct vertex *v;
	struct edge *adj;
};

class graph
{
public:
	vertex *first;

	graph()
	{
		first=NULL;
	}

	void init()
	{
		vertex *temp=first;
		while(temp!=NULL)
		{
			temp->visited=0;
			temp=temp->next;
		}
	}

	vertex* getVertex()
	{
		vertex *temp=new vertex();
		cout<<"Name : ";
		cin>>temp->name;

		cout<<"Date of Birth\n";
		cout<<"\tDay : ";
		cin>>temp->dob.day;
		cout<<"\tMonth : ";
		cin>>temp->dob.month;
		cout<<"\tYear : ";
		cin>>temp->dob.year;

		cout<<"Number of comments : ";
		cin>>temp->comments;
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
			first->dob=v->dob;
			first->comments=v->comments;
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
			temp->dob=v->dob;
			temp->comments=v->comments;
			temp->next=NULL;
		}
	}

	void create()
	{
		vertex *v;
		int total;
		cout<<"Create Network :-\n";
		cout<<"Enter the total number of people : ";
		cin>>total;
		for(int i=1 ; i<=total; i++)
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
		edge *e1=new edge;
		edge *e2=new edge;
		edge *t;
		cout<<"Enter name of first friend:\t";
		cin>>f1;
		cout<<"Enter name of second friend:\t";
		cin>>f2;

		vertex *fr1=searchVertex(f1);
		vertex *fr2=searchVertex(f2);

		if(fr1!=NULL && fr2!=NULL)
		{
			e1->v=fr2;
			e1->adj=NULL;
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
				cout<<"->"<<e->v->name;
				e=e->adj;
			}
			temp=temp->next;
			cout<<"\n";
		}while(temp!=NULL);
		temp=first;
		while(temp!=NULL)
        {
            cout<<temp->friends<<"\t";
            temp=temp->next;
        }
	}

	void dfs()
	{
		init();
		vertex *comm=first;
		vertex *u=first;
		while(u!=NULL)
		{
			if(u->visited==0)
                 comm=dfs(u,comm);
			u=u->next;
		}
		cout<<"\nMinimum no. of comments : "<<comm->name<<"( "<<comm->comments<<" comments)";
		init();
		u=first;
		comm=first;
		while(u!=NULL)
		{
			if(u->visited==0)
                 comm=dfs_max(u,comm);
			u=u->next;
		}
		cout<<"\nMaximum no. of comments : "<<comm->name<<"( "<<comm->comments<<" comments)";
	}

	vertex * dfs(vertex *f, vertex *min_comm)
	{
		stack <vertex*> s;
		vertex *u=f;

		s.push(u);
		while(!s.empty())
		{
			u=s.top();
			s.pop();
            if(u->comments<min_comm->comments)
            min_comm=u;

			if(u->visited==0)
			{
				u->visited=1;
				edge *w=u->adj;
				while(w!=NULL)
				{
					vertex *t=w->v;
					if(t->visited==0)
						s.push(t);
					w=w->adj;
				}
			}
		}
		return min_comm;
	}

	vertex * dfs_max(vertex *f, vertex *max_comm)
	{
		stack <vertex*> s;
		vertex *u=f;

		s.push(u);
		while(!s.empty())
		{
			u=s.top();
			s.pop();
                if(u->comments>max_comm->comments)
				max_comm=u;

			if(u->visited==0)
			{
				u->visited=1;
				edge *w=u->adj;
				while(w!=NULL)
				{
					vertex *t=w->v;
					if(t->visited==0)
						s.push(t);
					w=w->adj;
				}
			}
		}
		u=first;
		return max_comm;
	}

	vertex * bfs(vertex * current)
	{
		queue<vertex *>q;
		vertex *p,*max=current;
		edge *temp=NULL;
		q.push(current);
		current->visited=1;
		while(!q.empty())
		{
			p=q.front();
			q.pop();
			if(p->friends>max->friends)
				max=p;
			temp=p->adj;
			while(temp!=NULL)
			{
				if((temp->v)->visited!=1)
				{
					q.push(temp->v);
					(temp->v)->visited=1;
				}
				temp=temp->adj;
			}
		}
		p=first;
		while(p!=NULL)
		{
			if(p->visited==0)
			{
				p=bfs(p);
				if(p->friends>max->friends)
					max=p;
			}
			p=p->next;
		}
		return max;
	}


	void bfs()
	{
		vertex *max;
		max=bfs(first);
		cout<<"\n"<<max->name<<" has max friends, i.e. "<<max->friends<<"\n";
		init();
	}

	void birthday()
	{
	    int month,c=0;
	    vertex *temp=first;
	    cout<<"Enter the month : ";
	    cin>>month;
	    cout<<"Following people have birthday in current month : \n";
	    while(temp!=NULL)
        {
            if(temp->dob.month==month)
            {
                cout<<temp->name<<"\n";
                c++;
            }
            temp=temp->next;
        }
        if(c==0)
            cout<<"\nNo birthdays in current month!!";
	}

};

int main()
{
	graph g;
	g.create();
	int choice=0;
	do
	{
		cout<<"\n\nMENU\n1.Insert Friends\n2.Display network\n3.Maximum and minimum no. of comments\n4.Maximum no. of friends\n5.Birthday in current month\n6.Exit\nEnter your choice : ";
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
			g.dfs();
			break;
		case 4:
		     g.bfs();
			break;
		case 5:
		     g.birthday();
			break;
		case 6:
			cout<<"\n\nTHANK YOU!!";
			break;
		default:
			cout<<"\n\nPlease enter a valid choice!!";
		}
	}while(choice!=6);
	return 0;
}
