/*============================================================================
                              HASHING
Assignment no. : 9
Roll no.       : 23333
Batch          : F11
============================================================================*/

#include <iostream>
using namespace std;
struct hash
{
	int id;
	char name[20];
	long phn;
	int chain;
};


int hash_function(long ph)
{
	int a=ph%10;
	return a;
}


int menu()
{
	int ch;
	cout<<"\n\nMENU :\n1.Create hash table\n2.Insert\n3.Search\n4.Display table\n5.Exit\nEnter your choice : ";
	cin>>ch;
	return ch;
}

void display(hash h[])
{
	cout<<"Index\tID\tName\tPhone No.\t\tChain\n";
	for(int i=0 ; i<10; i++)
	{
		if(h[i].phn!=0)
		   cout<<i<<"\t"<<h[i].id<<"\t"<<h[i].name<<"\t"<<h[i].phn<<"\t"<<h[i].chain<<"\n";
		else
		   cout<<i<<"\t--\t--\t\t--\t--\t\n";
	}
}

hash input()
{
	hash temp;
	cout<<"\n\nEnter id : "; cin>>temp.id;
	cout<<"Enter name : "; cin>>temp.name;
	cout<<"Enter phone number : "; cin>>temp.phn;
	temp.chain=-1;
	return temp;
}

void search(hash h[])
{
	long ph1;
	int c=0;
	cout<<"\nEnter the phone number to be searched : ";
	cin>>ph1;
	int a=hash_function(ph1);
	while(1)
	{
		if(h[a].phn==ph1)
		{
			cout<<"\n\nRecord found";
			cout<<"\t"<<h[a].id<<"\t"<<h[a].name<<"\t"<<h[a].phn<<"\n";
			c++;
			break;
		}
		else if(h[a].chain!=-1)
		{
			a=h[a].chain;
		}
		else
			break;

	}
	if(c==0)
		cout<<"\nRecord not found!!";
}

class without_replacement
{
	hash h[10];
    public:
	without_replacement()
	{
		for(int i=0; i<10; i++)
		{
			h[i].id=0;
			h[i].phn=0;
			h[i].chain=-1;
		}
	}

	void call(int ch)
	{
		switch(ch)
		{
		case 1:
			create();
			break;
		case 2:
			insert();
			break;
		case 3:
			search(h);
			break;
		case 4:
			display(h);
			break;
		}
	}

	void insert()
	{
		hash temp=input();
		add(temp);
		cout<<"\nInserted Successfully!!";
	}

	void create()
	{
		int n;
		cout<<"How many records do you want to add : "; cin>>n;
		for(int i=1; i<=n; i++)
		{
			hash temp=input();
			add(temp);
		}
	}
	void add(hash temp)
	{
		int index=hash_function(temp.phn);
		if(h[index].phn==0)
			h[index]=temp;
		else
		{
			int i=index;
			while(h[i].phn!=0)
			{
				i++;
				if(i>9)
					i=0;
			}
			h[i]=temp;
			if(hash_function(h[index].phn)==index)
			{
				while(h[index].chain!=-1)
				{
					index=h[index].chain;
				}
				//if(hash_function(h[index].phn)==index)
				  h[index].chain=i;
			}
			else
			{
				int j=index+1;
				while(h[j].chain!=-1)
				{
					j=h[j].chain;
				}
				if(h[j].phn!=temp.phn)
					h[j].chain=i;
			}			 
		}
	}

};


class with_replacement
{
	hash h1[10];
    public:
    	with_replacement()
	{
		for(int i=0; i<10; i++)
		{
			h1[i].id=0;
			h1[i].phn=0;
			h1[i].chain=-1;
		}
	}
	void call(int ch)
	{
		switch(ch)
		{
		case 1:
			create();
			break;
		case 2:
			insert();
			break;
		case 3:
			search(h1);
			break;
		case 4:
			display(h1);
			break;
		}
	}

	void create()
	{
		int n;
		cout<<"How many records do you want to add : "; cin>>n;
		for(int i=1; i<=n; i++)
		{
			hash temp=input();
			add(temp);
		}
	}

	void add(hash temp)
	{
		int j,k;
		int index=hash_function(temp.phn);
		if(h1[index].phn==0)
			h1[index]=temp;
		else
		{
			hash new1;
			new1=h1[index];
			if(hash_function(new1.phn)!=index)
			{
				h1[index]=temp;
				int i=index;
				while(h1[i].phn!=0)
				{
					i++;
					if(i>9)
						i=0;
				}
				h1[i]=new1;
				//h1[index].chain=i;
				int j=hash_function(new1.phn);
				while(h1[j].chain!=index)
				{
					j=h1[j].chain;
				}
				h1[j].chain=i;
			}
			else if(hash_function(new1.phn)==index)
			{
				int i=index;
				while(h1[i].chain!=-1)
				{
					//i++;
					//if(i>9)
						//i=0;
					i=h1[i].chain;
				}
				j=i;
				while(h1[i].phn!=0)
				{
					i++;
					if(i>9)
						i=0;
				}
				h1[i]=temp;
				h1[j].chain=i;
			}
		}
	}

	void insert()
	{
		hash temp=input();
		add(temp);
		cout<<"\nInserted Successfully!!";
	}
	
};



int main()
{
	int choice;
	do
	{
		cout<<"\n\nMENU:\n1.Without replacement\n2.With replacement\n3.Exit\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
		case 1:
		{
			without_replacement w;
			do
			{
				choice=menu();
				w.call(choice);
			}while(choice!=5);
		}
		break;
		case 2:
		{
			with_replacement w1;
			do
			{
				choice=menu();
				w1.call(choice);
			}while(choice!=5);
		}
		break;
		case 3:
			cout<<"\n\nTHANK YOU!!";
			break;
		default:
			cout<<"\nPlease enter a valid option!!";
		}
	}while(choice!=3);
}
