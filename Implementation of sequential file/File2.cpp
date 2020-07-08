/*============================================================================
                           SEQUENTIAL FILES
Assignment no. : 11
Roll no.       : 23333
Batch          : F11
============================================================================*/

#include<fstream>
#include<iostream>
#include<iomanip>
#include<string.h>
#define NAME 25
using namespace std;
void tabletail()
{
	for(int i=0;i<50;i++)
		cout<<"-";
	cout<<"\n";
}

void tablehead()
{
	tabletail();
	cout<<"|Student Name             |Age |Division |Marks  |\n";
	tabletail();
}

class Student
{
	private:
		char Name[NAME];
		int Division;
		int Marks;
		int Age;
	public:
		Student()
		{
			strcpy(Name,"NULL");
			Division=-1;
			Marks=-1;
			Age=-1;
		}
		Student(char Namecpy[],int Divisioncpy,int Markscpy,int Agecpy)
		{
			strcpy(Name,Namecpy);
			Division=Divisioncpy;
			Marks=Markscpy;
			Age=Agecpy;
			cout<<"Done\n\n";
		}
		void print()
		{
			cout<<std::left<<"|"<<setw(25)<<Name<<"|"<<setw(4)<<Age<<"|"<<setw(9)<<Division<<"|"<<setw(7)<<Marks<<"|\n";
		}
		char* getName()
		{
			return Name;
		}
		void setMarks()
		{
			do
			{
				cout<<"\nEnter marks:\t";
				cin>>Marks;
				if(Marks<0||Marks>100)
					cout<<"\n\tInvalid!!!\n";
			}while(Marks<0||Marks>100);
		}
		void setAge()
		{
			do
			{
				cout<<"\nEnter Age:\t";
				cin>>Age;
				if(Age<0)
					cout<<"\n\tInvalid!!!\n";
			}while(Age<0);
		}
		void setDiv()
		{
			do
			{
				cout<<"\nEnter Division:\t";
				cin>>Division;
				if(Division<0||Division>30)
					cout<<"\n\tInvalid!!!\n";
			}while(Division<0||Division>30);
		}
};

class Fileop
{
	private:
		fstream file;
		Student s;
	public:
		Fileop()
		{
			file.open("abc",ios::app);
			file.close();
		}
		~Fileop()
		{
			file.close();
		}
		void addData();
		void  displayData();
		int search(char[]);
		int modify(char[]);
		int delRec(char[]);
};

void Fileop::addData()
{
	file.open("abc",ios::app|ios::binary);
	char Name[NAME];
	int Age,Divison,Marks;
	cout<<"Enter Student name:\t";
	cin.ignore();
	scanf("%[^\n]s",Name);
	cout<<"Enter Age:\t";
	cin>>Age;
	cout<<"Enter Marks:\t";
	cin>>Marks;
	cout<<"Enter Division:\t";
	cin>>Divison;
	s=Student(Name,Divison,Marks,Age);
	file.write((char *)&s,sizeof(s));
	file.close();
}

void Fileop::displayData()
{
	file.open("abc",ios::in);
	file.read((char *)&s,sizeof(s));
	while(!file.eof())
	{
		s.print();
		file.read((char *)&s,sizeof(s));
	}
	file.close();
}

int Fileop::search(char n[])
{
	file.open("abc",ios::in);
	file.read((char *)&s,sizeof(s));
	while(!file.eof())
	{
		if(strcmp(s.getName(),n)==0)
		{
			cout<<"\nRecord Found!\n\n";
			tablehead();
			s.print();
			tabletail();
			file.close();
			return 1;
		}
		file.read((char *)&s,sizeof(s));
	}
	file.close();
	return 0;
}

int Fileop::modify(char n[])
{
	int flag=0;
	fstream temp;
	temp.open("t",ios::out|ios::binary);
	file.open("abc",ios::in|ios::out|ios::binary);
	file.read((char *)&s,sizeof(s));
	while(!file.eof())
	{
		if(strcmp(s.getName(),n)==0)
		{
			flag=1;
			cout<<"\nRecord Found!\n\n";
			tablehead();
			s.print();
			tabletail();
			s.setMarks();
			s.setAge();
			s.setDiv();
			//file.seekg(-sizeof(s),ios::cur);
			//cout<<"\n\tSuccessfully Modified!\n";
			//file.close();
			//return 1;
		}
		temp.write((char *)&s,sizeof(s));
		file.read((char *)&s,sizeof(s));
	}
	temp.close();
	file.close();
	remove("abc");
	rename("t","abc");
	if(flag==1)
		cout<<"\n\tSuccessfully Modified!\n";
	return flag;
}

/*int Fileop::delRec(char n[])
{
	file.open("abc",ios::in|ios::out|ios::binary);
	file.read((char *)&s,sizeof(Student));
	int flag=0;
	while(!file.eof())
	{
		if(strcmp(s.getName(),n)==0)
		{
			flag=1;
			file.read((char *)&s,sizeof(Student));
			continue;
		}
		else if(flag==1)
		{

			if(!file.eof())
			{
				file.seekg(-2*sizeof(s),ios::cur);
				file.write((char *)&s,sizeof(Student));
				file.seekg(sizeof(s),ios::cur);
			}
			file.read((char *)&s,sizeof(Student));
		}
		else
		{
			file.read((char *)&s,sizeof(Student));
		}
	}
	if(flag==1)
	{
		file.seekg(-sizeof(s),ios::cur);
		file<<-1;
	}
	file.close();
	return flag;
}*/
int Fileop::delRec(char n[])
{
	int flag=0;
	fstream temp;
	temp.open("t",ios::out|ios::binary);
	file.open("abc",ios::in|ios::out|ios::binary);
	file.read((char *)&s,sizeof(s));
	while(!file.eof())
	{
		if(strcmp(s.getName(),n)==0)
		{
			flag=1;
		}
		else
		{
			temp.write((char *)&s,sizeof(s));
		}
		file.read((char *)&s,sizeof(s));
	}
	if(flag==1)
	{
		cout<<"\n\tRecord deleted successfully\n";
	}
	file.close();
	temp.close();
	remove("abc");
	rename("t","abc");
	return flag;
}


int main()
{
	int choice,t,res,mod,del;
	Fileop f;
	char query[NAME];
	do
	{
		cout<<"\nStudent Data Base\n";
		cout<<"Press 1 to Add Data\n";
		cout<<"Press 2 to Display all records\n";
		cout<<"Press 3 to search for a record\n";
		cout<<"Press 4 to Modify a record\n";
		cout<<"Press 5 to delete a record\n";
		cout<<"Press 6 to Exit\n\n";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Enter number of Records you want to add:";
				cin>>t;
				while(t--)
					f.addData();
				break;

			case 2:
				tablehead();
				f.displayData();
				tabletail();
				break;
			case 3:
				cout<<"Enter Name to be searched:\t";
				cin.ignore();
				scanf("%[^\n]s",query);
				res=f.search(query);
				if(res==0)
					cout<<"Record not found!\n";

				break;
			case 4:
				cout<<"Enter Name to be modified:\t";
				cin.ignore();
				scanf("%[^\n]s",query);
				mod=f.modify(query);
				if(mod==0)
					cout<<"Record not Found!\n";
				break;
			case 5:
				cout<<"Enter Name to be deleted:\t";
				cin.ignore();
				scanf("%[^\n]s",query);
				del=f.delRec(query);
				if(del==0)
					cout<<"Record not Found!\n";

				break;
			case 6:

				break;
		}
	}
	while(choice!=6);
}
