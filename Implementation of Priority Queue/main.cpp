/*============================================================================
                           PRIORITY QUEUE
Assignment no. : 2
Roll no.       : 23333
Batch          : F11
============================================================================*/
#include <iostream>
#include<string.h>
#include "queue.h"
#include "queue.cpp"
using namespace std;
class A
{
	private:
	   int id=1,size;
	   int priority()
		{
			int p=0;
			if(strcmp(pt.disease,"heart")==0)
				p=3;
			else if(strcmp(pt.disease,"accident")==0)
				p=2;
			else if(strcmp(pt.disease,"general")==0)
				p=1;
			return p;
		}
	   int name()
	   {
		   for(int i=0 ;i<strlen(pt.name); i++)
		   {
			   if(!isalpha(pt.name[i]))
				   return 0;
		   }
		   return 1;
	   }
	   int valid_phone()
	   {
		   if(strlen(pt.phone)==10)
			   return 1;
		   return 0;
	   }
	public:
	    queue<patient>q;
	    patient pt,pt1,a[30];
	    void add()
	    {
	    	pt.id=id;
	    	do
	    	{
	    		cout<<"Enter name : "; cin>>pt.name;
	    		if(name()!=1)
	    			cout<<"\nPLease enter a valid name\n";
	    	}while(name()!=1);

	    	cout<<"Enter disease (heart/accident/general) : "; cin>>pt.disease;

	    	do
		{
    		cout<<"Enter phone number : "; cin>>pt.phone;
		if(valid_phone()!=1)
			cout<<"\nPlease enter a valid phone number\n";
	        }while(valid_phone()!=1);
	    	q.enqueue(pt,priority());
	    	id++;
	    }
	    void remove()
	    {
	    	int p;
	    	pt1=q.dequeue(&p);
	    	if(p==1)
	    	{
	    		cout<<"\n\nID\t\tNAME\t\tDISEASE\t\tPHONE NUMBER\n\n";
			cout<<pt1.id<<"\t\t"<<pt1.name<<"\t\t"<<pt1.disease<<"\t\t"<<pt1.phone<<endl;
			cout<<"\n\nPatient Served!!";
	    	}

	    }
	    void display()
	    {
	    	size=q.display(a);
	    	if(size!=0)
	    	{
		    	cout<<"\n\nID\t\tNAME\t\tDISEASE\t\tPHONE NUMBER\n\n";
		    	for(int i=0; i<size; i++)
		    	{
		    	   cout<<a[i].id<<"\t\t"<<a[i].name<<"\t\t"<<a[i].disease<<"\t\t"<<a[i].phone<<endl;
		    	}
		}
	    }
};
int main()
{
	A p;
	int choice=0;
	do
	{
		cout<<"\n\n1.Add records\n2.Serve patients\n3.Display\n4.Exit\nEnter your choice : ";
		cin>>choice;
		switch(choice)
			{
			case 1:
			{
				int n;
				do
				{
					cout<<"\nEnter the number of records to be added:";
					cin>>n;
					if(n<=0)
						cout<<"\nPlease enter number greater than zero!!";
				}while(n<=0);
			    for(int i=1; i<=n; i++)
			    {
			    	cout<<"\nRecord no. "<<i<<endl;
			    	p.add();
			    }
			    break;
			}
			case 2:
			{
				p.remove();
				break;
			}
			case 3:
			{
				p.display();
				break;
			}
			case 4:
			{
				cout<<"\n\nTHANK YOU!!\n\n";
				break;
			}
			default:
				cout<<"\n\nPLease enter valid option!!\n";
			}
	}while(choice!=4);
}