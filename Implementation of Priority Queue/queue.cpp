#include <iostream>
using namespace std;
#include "queue.h"
template <class T>
queue<T>::queue()
{
	front=NULL;
	rear=NULL;
}

template <class T>
int queue<T>::isempty()
{
	if(front==NULL)
		return 1;
	else
		return 0;
}

template <class T>
void queue<T>::enqueue(T t,int priority)
{
	node *temp=new node();
	temp->next=NULL;
	temp->p=t;
	temp->priority=priority;
	if(!isempty())
	{
		rear->next=temp;
		rear=temp;
	}
	else
	{
		front=temp;
		rear=temp;
	}
}

template <class T>
int queue<T>::display(T a[])
{
	node *temp=new node();
	temp=front;
	T b;
	int i=0;
	if(!isempty())
	{
		while(temp!=NULL)
		{
		   b=temp->p;
		   a[i]=b;
		   i++;
		   temp=temp->next;
		}
	}
	else
		cout<<"\n\nQueue empty!!\nPLease enter records!!\n";
	return i;
}

template <class T>
T queue<T>::dequeue(int *flag)
{
	T pt;
	if(!isempty())
	{
		*flag=1;
		int high=0;
		node *temp1=new node();
		node *prev=new node();
		node *temp=new node();
		temp=front;
		if(front==rear)
		{
			pt=front->p;
			front=NULL;
			rear=NULL;
		}
		else
		{
			while(temp!=NULL)
			{
				if(temp->priority>high)
				{
					high=temp->priority;
					temp1=temp;
				}
				temp=temp->next;
			}
			pt=temp1->p;
			prev=front;
			if(temp1==front)
			{
				front=front->next;
				delete temp1;
			}
			else
                {
                    while(prev->next!=temp1)
                    {
                        prev=prev->next;
                    }
                    if(temp1==rear)
			    {
			       rear=prev;
				  prev->next=NULL;
				  delete temp1;
			    }
			    else
			    {
				 temp=temp1->next;
				 delete temp1;
				 prev->next=temp;
			    }
			 }
		  }
	}
	else
	{
		cout<<"\n\nQueue empty!!\nPLease enter records!!\n";
		*flag=0;
	}
	return pt;
}

template <class T>
queue<T>::~queue()
{
	node *temp=new node();
	while(front!=NULL)
	{
		temp=front;
		front=front->next;
		delete(temp);
	}
}
