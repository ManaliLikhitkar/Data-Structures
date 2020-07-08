#include<iostream>
#include "queue.h"

template<class T>
queue<T>::queue()
{
	front=NULL;
	rear=NULL;
}

template<class T>
int queue<T>::isempty()
{
	if(front==NULL)
		return 1;
	else
		return 0;
}

template<class T>
void queue<T>::enqueue(T a)
{
	node1 *temp;
	temp=new node1;
	temp->data=a;
	temp->next=NULL;
	if(isempty())
	{
	    front=temp;
	    rear=temp;
	}
	else
        {
            rear->next=temp;
            rear=temp;
	}
}

template<class T>
T queue<T>::dequeue()
{
	T a;
	node1 *temp=front;
	front=front->next;
	a=temp->data;
	delete temp;
	return a;
}

template<class T>
int queue<T>::sizeq()
{
	node1 *temp=front;
	int n=0;
	while(temp!=rear)
	{
		n++;
	}
	return n++;
}

template<class T>
queue<T>::~queue()
{
}

