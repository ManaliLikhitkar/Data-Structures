#include <iostream>
#include "stack.h"
using namespace std;
template<class T>
stack<T>::stack()
{
     top=NULL;
}
template<class T>
void stack<T>::push(T x)
{
	struct node *temp;
	temp=new node();
	temp->data=x;
	temp->next=top;
	top=temp;
}
template<class T>
T stack<T>::pop()
{
	struct node *temp=top;
	T x=top->data;
	top=top->next;
	delete temp;
	return x;
}
template<class T>
int stack<T>::isempty()
{
	if(top==NULL)
		return 1;
	else
		return 0;
}
template<class T>
T stack<T>::get_top()
{
	if(isempty()==0)
      return top->data;
	else
	  return -1;
}
template<class T>
stack<T>::~stack()
{
	struct node* temp;
	while(top!=NULL)
	{
		temp=top;
		top=top->next;
		delete(temp);
	}
}
