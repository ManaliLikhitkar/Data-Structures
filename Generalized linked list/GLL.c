/*
============================================================================
 Name        : GLL.c
 Author      : Atharva Kulkarni,23329,F11
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 20


typedef struct Node
{
	union
	{
		char data[MAX];
		struct Node* dlink;
	}u;
	int flag;
	struct Node* next;
}Node;

Node* getnode()
{
	Node* new1=(Node*)malloc(sizeof(Node));
	new1->next=NULL;
	new1->u.dlink=NULL;
	return new1;
}

Node* createGLL(Node* head,char str[])
{
	int open=0;
	int close=0;
	int i,j;
	Node* temp=head;
	for(i=0;str[i]!='\0';)
	{
		if(str[i]=='(' && i==0)
		{
			head=getnode();
			temp=head;
		}
		else
		{
			temp->next=getnode();
			temp=temp->next;
		}
		i++;
		j=0;
		while(str[i]!=',' && str[i]!='(' && str[i]!=')')
		{
			temp->u.data[j]=str[i];
			i++;
			j++;
		}
		temp->u.data[j]='\0';
		temp->flag=0;

		if(str[i]=='(')
		{
			open++;
			temp->next=getnode();
			temp=temp->next;
			temp->flag=1;
			temp->u.dlink=createGLL(NULL,&str[i]);
			while(open!=close)
			{
				i++;
				if(str[i]=='(')
					open++;
				else if(str[i]==')')
					close++;
			}
			i++;
		}
		if(str[i]==')')
		{
			return head;
		}
	}
	return head;
}

void display(Node* temp)
{
	static int depth;
	depth++;
	int i;
	if(temp==NULL)
	{
		if(depth==1)
		{
			printf("List is Empty!\n");
		}
		else
		{
			printf("Sublist is Empty!\n");
		}
	}
	else
	{
		while(temp!=NULL)
		{
			if(temp->flag==0)
			{
				printf("\n");
				for(i=1;i<=depth;i++)
					printf("\t");
				printf("%s",temp->u.data);
			}
			else
				display(temp->u.dlink);
			temp=temp->next;
		}
		depth--;
	}
}

int main(void)
{

	char str[51],repeat='n';
	do
	{
		Node *head=NULL;
		printf("Enter Book Index String:\n");
		scanf("\n");
		gets(str);
		printf("The Book index is:\n");
		head=createGLL(head,str);
		display(head);
		printf("\nDo you want to continue?(y/n)\t");
		scanf("%c",&repeat);
	}while(repeat=='y');
	return EXIT_SUCCESS;
}
