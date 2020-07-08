/*============================================================================
                        KRUSKAL'S ALGORITHM
Assignment no. : 7
Roll no.       : 23333
Batch          : F11
============================================================================*/

#include <iostream>
#include <string.h>
#include<stack>
using namespace std;

typedef struct node
{
	char name[20];
	int visited;
	int intree;
	struct node* dlink;
	struct edge* next;
}node;

typedef struct edge
{
	struct node* flink;
	struct edge* nextlink;
	int weight;
	int intree;
	int selected;
}edge;

node* getNode()
{
	node* temp=new node();
	cout<<"\nEnter name : ";
	cin>>temp->name;
	temp->dlink=NULL;
	temp->next=NULL;
	return temp;
}

class Graph
{
	node* startVertex;
	int totalVertices;
	int totalEdges;

public:
	Graph()
{
		startVertex=NULL;
		totalVertices=0;
		totalEdges=0;

		startVertex=NULL;
		totalVertices=0;
		totalEdges=0;
}

	void unvisit()
	{
		node* p=startVertex;
		while(p!=NULL)
		{
			p->visited=0;
			p=p->dlink;
		}
	}

	node* insertVertex(node* vertex,node* temp)
	{

		if(vertex==NULL)
		{
			totalVertices++;
			return temp;
		}
		else if(strcmp(temp->name,vertex->name)==0)
		{
			cout<<"\n\tInvalid!! Duplication not allowed!";
			return vertex;
		}
		else
		{
			vertex->dlink = insertVertex(vertex->dlink,temp);
			return vertex;
		}
	}

	void createGraph()
	{
		int tot;
		node* temp;
		cout<<"\nEnter total vertices in the graph : ";
		cin>>tot;
		for(int i=0;i<tot;i++)
		{
			temp=getNode();
			startVertex=insertVertex(startVertex,temp);
		}
	}

	void insertSVertex()
	{
		node* temp=getNode();
		startVertex=insertVertex(startVertex,temp);
	}

	void displayAdjList()
	{
		node* temp=startVertex;
		edge* tlink;
		while(temp!=NULL)
		{
			tlink=temp->next;
			cout<<temp->name;
			while(tlink!=NULL)
			{
				cout<<" -- "<<tlink->weight<<" > "<<tlink->flink->name;
				tlink=tlink->nextlink;
			}
			temp=temp->dlink;
			if(temp!=NULL)
				cout<<"\n|\n";
		};

	}

	node* searchVertex(char key[])
	{
		node* temp=startVertex;
		while(temp!=NULL)
		{
			if(strcmp(key,temp->name)==0)
			{
				return temp;
			}
			temp=temp->dlink;
		}
		return NULL;
	}

	void insertEdge()
	{
		char f1[30],f2[30];
		int w;
		edge* tlink1=new edge();
		edge* tlink2=new edge();
		edge* t;

		cout<<"\nEnter name of first Vertex:\t";
		cin>>f1;
		cout<<"\nEnter name of second Vertex:\t";
		cin>>f2;
		cout<<"\nEnter weight of edge:\t";
		cin>>w;
		node* fr1=searchVertex(f1);
		node* fr2=searchVertex(f2);

		if(fr1!=NULL && fr2!=NULL)
		{
			tlink1->flink=fr2;
			tlink1->nextlink=NULL;
			tlink1->weight=w;

			t=fr1->next;
			if(t==NULL)
			{
				fr1->next=tlink1;
			}
			else
			{
				while(t->nextlink!=NULL)
					t=t->nextlink;
				t->nextlink=tlink1;
			}

			tlink2->flink=fr1;
			tlink2->nextlink=NULL;
			tlink2->weight=w;

			t=fr2->next;
			if(t==NULL)
			{
				fr2->next=tlink2;
			}
			else
			{
				while(t->nextlink!=NULL)
					t=t->nextlink;
				t->nextlink=tlink2;
			}
			totalEdges++;
		}
		else
		{
			cout<<"\nInvalid Vertices!\n";
		}
	}

	int checkLoops(node* start,node* end)
	{
		int loop=1;
		edge* temp=start->next;
		start->visited=1;
		while(temp!=NULL)
		{
			if(temp->flink->visited!=1)
			{
				if(temp->selected==1)
				{
					start=temp->flink;
					if(start!=end)
					{
						loop=checkLoops(start,end);
						if(loop)
							break;
					}
					else
					{
						start->visited=1;
						loop=1;
						break;
					}
				}
				else
				{
					loop=0;
				}
			}
			temp=temp->nextlink;
		}
		return loop;
	}

	void insertTreeEdge(node* v1,node* v2)
	{
		v1->intree=1;
		v2->intree=1;

		edge* t=v1->next;
		while(t!=NULL)
		{
			if(t->flink==v2)
			{
				t->intree=1;
				t->selected=1;
				break;
			}
			t=t->nextlink;
		}

		t=v2->next;
		while(t!=NULL)
		{
			if(t->flink==v1)
			{
				t->selected=1;
				break;
			}
			t=t->nextlink;
		}
	}

	void MinSpanningTree()
	{
		node* tvertex;
		edge* tedge;

		for(int i=0;i<totalEdges;i++)
		{
			tvertex=startVertex;
			edge* minedge=new edge();
			minedge->weight=9999;
			node* minedgestart=startVertex;

			while(tvertex!=NULL)
			{
				tedge=tvertex->next;

				while(tedge!=NULL)
				{
					if(tedge->intree!=1 && tedge->selected!=1 && tedge->weight<=minedge->weight)
					{
						minedge=tedge;
						minedgestart=tvertex;
					}
					tedge=tedge->nextlink;
				}
				tvertex=tvertex->dlink;
			}

			node* minedgeend=minedge->flink;
			if(minedgestart->intree!=1 || minedgeend->intree!=1)
			{
				insertTreeEdge(minedgestart,minedgeend);
			}
			else
			{
				if(!checkLoops(minedgestart,minedgeend))
				{
					insertTreeEdge(minedgestart,minedgeend);
				}
			}
		}

		tvertex=startVertex;
		tedge=startVertex->next;
		cout<<"\n\tMinimum Spanning Tree:\n";

		while(tvertex!=NULL)
		{
			tedge=tvertex->next;

			while(tedge!=NULL)
			{
				if(tedge->intree==1)
				{
					cout<<"\n"<<tvertex->name<<"\t"<<tedge->flink->name<<"\t"<<tedge->weight;
				}
				tedge=tedge->nextlink;
			}
			tvertex=tvertex->dlink;
		}

		tvertex=startVertex;

		while(tvertex!=NULL)
		{
			if(tvertex->intree!=1)
				cout<<"\n"<<tvertex->name;
			tvertex=tvertex->dlink;
		}
		unvisit();
	}
};

int menu()
{
	int choice;
	cout<<"\n\nMenu:";
	cout<<"\n1.Insert Vertex\n2.Insert Edge\n3.Display Adjacency List\n4.Minimum Spanning Tree\n5.Exit\nEnter your choice : ";
	cin>>choice;
	return choice;
}

int main()
{
	Graph g;
	g.createGraph();
	int cont,choice;
	do
	{
		choice=menu();
		switch(choice)
		{
		case 1:
			g.insertSVertex();
			break;
		case 2:
			g.insertEdge();
			break;
		case 3:
			g.displayAdjList();
			break;
		case 4:
			g.MinSpanningTree();
			break;
		case 5:
			cout<<"\n\nTHANK YOU!!";
			break;
		default:
			cout<<"\nInvalid Choice!\n";
		}
	}while(choice!=5);
	return 0;
}