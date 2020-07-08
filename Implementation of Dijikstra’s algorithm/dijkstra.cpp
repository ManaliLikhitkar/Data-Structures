#include<iostream>
#include<stack>
#include<queue>
#include<string.h>

using namespace std;

typedef struct vertex
{
	struct vertex* dlink;
	struct edge* adj;
	char name[30];
	//int visited;
	int distance;
	struct vertex* prev;
}vertex;

typedef struct edge
{
	struct vertex* flink;
	struct edge* nextlink;
	int weight;
}edge;

vertex* getVertex()
{
	vertex* newVertex=new vertex();
	cout<<"\nEnter name:\t";
	cin>>newVertex->name;
	newVertex->distance=9999;
	newVertex->dlink=NULL;
	newVertex->adj=NULL;
	return newVertex;
}

class Graph
{
	vertex* startVertex;
	int totalVertices;
	
	public:
	
	Graph()
	{
		startVertex=NULL;
		totalVertices=0;
	}
	
	vertex* insertVertex(vertex* r,vertex* temp)
	{
		if(r!=NULL)
		{
			if(strcmp(r->name,temp->name)==0)
			{
				cout<<"\nDuplication not allowed!\n";
			}
			else
				r->dlink=insertVertex(r->dlink,temp);
		}
		else
		{
			r=temp;
			totalVertices++;
		}
		return r;
	}
	
	void createGraph()
	{
		int total;
		vertex* temp;
		cout<<"\nHow many vertices to add?\t";
		cin>>total;
		for(int i=0;i<total;i++)
		{
			temp=getVertex();
			startVertex=insertVertex(startVertex,temp);
		}	
	}
	
	void displayGraph()
	{
		vertex* v=startVertex;
		edge* e=NULL;
		while(v)
		{
			cout<<v->name<<" -> ";
			e=v->adj;
			while(e)
			{
				cout<<e->flink->name<<" -> ";
				e=e->nextlink;
			}
			cout<<"\n|\n";
			v=v->dlink;
		}
	}
	
	vertex* searchVertex(vertex* r,char key[])
	{
		vertex* t=r;
		while(t)
		{
			if(strcmp(t->name,key)==0)
			{
				return t;
			}
			t=t->dlink;
		}
		return NULL;
	}
	
	void searchVertex()
	{
		char key[30];
		vertex* t=NULL;
		cout<<"\nEnter name of vertex:\t";
		cin>>key;
		
		t=searchVertex(startVertex,key);
		if(t!=NULL)
			cout<<"\nVertex found\n";
		else
			cout<<"\nVertex not found\n";
	}
	
	void addEdge()
	{	
		char fr1[30],fr2[30];
		vertex* f1,*f2,*traverse;
		int wt;
		
		cout<<"\nEnter name of vertex 1:\t";
		cin>>fr1;
		
		cout<<"Enter name of vertex 2:\t";
		cin>>fr2; 
		
		cout<<"Enter weight of edge:\t";
		cin>>wt;
		
		f1=searchVertex(startVertex,fr1);
		f2=searchVertex(startVertex,fr2);
		
		if(f1 && f2)
		{
			edge* e1=new edge();
			edge* e2=new edge();
			edge* ed;
			
			e1->flink=f2;
			e1->nextlink=NULL;
			e1->weight=wt;
			
			ed=f1->adj;
			if(ed==NULL)
			{
				f1->adj=e1;
			}
			else
			{
				while(ed->nextlink)
				{
					if(ed->flink!=f2)
						ed=ed->nextlink;
					else
					{
						cout<<"\nEdge present\n";
						return;
					}
				}
				
				if(ed->flink!=f2)
					//ed=ed->nextlink;
					ed->nextlink=e1;
				else
				{
					cout<<"\nEdge present\n";
					return;
				}
			}
			
			e2->flink=f1;
			e2->nextlink=NULL;
			e2->weight=wt;
			
			ed=f2->adj;
			if(ed==NULL)
			{
				f2->adj=e2;
			}
			else
			{
				while(ed->nextlink)
				{
					if(ed->flink!=f1)
						ed=ed->nextlink;
					else
					{
						cout<<"\nEdge present\n";
						return;
					}
				}
				
				if(ed->flink!=f1)
					//ed=ed->nextlink;
					ed->nextlink=e2;
				else
				{
					cout<<"\nEdge present\n";
					return;
				}
			}
		}
		else
			cout<<"\nInvalid Vertices\n";
	}
	
	/*void unvisit()
	{
		vertex* t=startVertex;
		while(t)
		{
			t->visited=0;
			t=t->dlink;
		}
	}*/
	
	void dijkstra()
	{
		vertex* start=NULL,*t,*t1;
		edge* tedge;
		char key[30];
		int pre_dist;
		stack<vertex*> s;
		
		cout<<"\nEnter starting vertex:\t";
		cin>>key;
		start=searchVertex(startVertex,key);
		
		start->distance=0;
		
		t=start;
		do
		{
			pre_dist=t->distance;
			tedge=t->adj;
			while(tedge)
			{
				if((tedge->weight+pre_dist)<=tedge->flink->distance)
				{
					tedge->flink->distance=tedge->weight+pre_dist;
					tedge->flink->prev=t;
				}
				tedge=tedge->nextlink;
			}
			t=t->dlink;
			if(t==NULL)
				t=startVertex;
		}while(t!=start);
		
		cout<<"\nDistances from "<<start->name<<" are:\n";
		
		t=startVertex;
		while(t)
		{
			if(t!=start)
			{
				t1=t->prev;
				while(t1!=start)
				{
					s.push(t1);
					t1=t1->prev;
				}
				s.push(start);
				cout<<"\n";
				while(!s.empty())
				{
					t1=s.top();
					s.pop();
					cout<<t1->name<<"\t";
				}
				
				cout<<t->name<<"\t"<<t->distance;	
			}
			t=t->dlink;
		}
		cout<<"\n";
	}
};

int main()
{
	Graph g;
	int tedges;
	g.createGraph();
	
	cout<<"\nHow many edges?\t";
	cin>>tedges;
	for(int i=0;i<tedges;i++)
		g.addEdge();
		
	g.displayGraph();
	
	g.dijkstra();
}
