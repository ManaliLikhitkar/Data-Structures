/*============================================================================
                        Direct Access Files
Assignment no. : 2
Roll no.       : 23333
Batch          : F11
============================================================================*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#define MAX 15
#define TABLE_SIZE 10

using namespace std;

class student {
	private :
		int loc;
		char std_name[15];
		int std_roll;
		int std_class;
		float per;
		int marks1;
		int marks2;
		int marks3;
		int flag;
		int chain;
		static int record_count;
	public :
		student ();
		void initialise ();
		int hashing_function (int);
		void getdata ();
		void displaydata ();
		int getroll (int);
		int insert ();
		int search (int);
		void modify_record (int);
		void print (int);
		void save () ;
};

int student :: record_count = 0;

student :: student () {
	std_roll = -1;
	std_class = -1;
	marks1 = -1;
	marks2 = -1;
	marks3 = -1;
	per = 0.0;
	flag = -1;
	chain = -1;
}

void student :: initialise () {
	fstream file;
	student s;
	file.open ("student.txt", ios::out | ios::binary);
	strcpy (s.std_name, "NULL");
	for (int i = 0 ; i < TABLE_SIZE ; i++) {
		s.loc = i;
		file.write ( (char*) &s, sizeof (s));
	}
	file.close ();
}

int student :: hashing_function (int key) {
	return (key%TABLE_SIZE);
}

void student :: getdata() {
	cout<<"\nEnter Name : ";
	cin>>std_name;
	cout<<"\nEnter Roll No : ";
	cin>>std_roll;
	cout<<"\nEnter class : ";
	cin>>std_class;
	cout<<"\nEnter Marks (out of 100) ";
	cout<<"\nEnter Physics Marks : "; cin>>marks1;
	cout<<"Enter Maths Marks : "; cin>>marks2;
	cout<<"Enter Chemistry Marks : "; cin>>marks3;
	per = marks1 + marks2 + marks3;
	per = per/300;
	per = per * 100;
}

void student :: displaydata ()
{
	cout << left ;
	cout << setw (10) << loc;
	cout << setw(15) << std_name;
	cout << setw(8) << std_roll;
	cout << setw(6) << std_class;
	cout << setprecision(3) << setw(11) << per;
	cout << setw (8) << marks1;
	cout << setw (6) << marks2;
	cout << setw (10) << marks3;
	cout << setw (5) << flag;
	cout << setw (10) << chain <<endl;
}

int student :: getroll (int r)
{
	if (r==std_roll) return 1;
	else  return 0;
}

int student :: insert ()
{
	fstream file;
	student s, temp;
	if (record_count == TABLE_SIZE)
	{
		cout << "\nTABLE FULL, CAN'T INSERT ELEMENT " << endl;
		return record_count;;
	}
	cout << "\n :: RECORD " << record_count+1 << " ::\n";
	file.open("student.txt", ios::out | ios::in | ios::binary | ios::ate);
	s.getdata();
	int key = hashing_function (s.std_roll);
	file.seekg ( (key*sizeof(student)), ios::beg );
	file.read ( (char*) &temp, sizeof (student));
		//location empty
	if (temp.flag == -1)
	{
		file.seekg( (key*sizeof(student)), ios::beg);
		s.loc = key;
		s.flag = 1;
		file.write ( (char*) &s, sizeof (student) );
		record_count ++;
	}
		//search empty location
	//if element of same type

	else if ( hashing_function (temp.std_roll) == key )
	{
		int tempkey = key;
		while ( temp.chain != -1 ) {
			file.seekg (temp.chain*sizeof(student), ios::beg);
			file.read ( (char*) &temp, sizeof (student) );
			tempkey = temp.loc;
	}
	file.seekg (key*sizeof(student), ios::beg);
	file.read ( (char*) &temp, sizeof (student) );
	while ( temp.flag != -1 ) {
		file.seekg ( (key = hashing_function (key+1))*sizeof(student), ios::beg );
		file.read ( (char*) &temp, sizeof (student) );
		key = temp.loc;
	}
	file.seekg( (key*sizeof(student)), ios::beg);
	s.loc = key;
	s.flag = 1;
	file.write ( (char*) &s, sizeof (student) );
	record_count ++;
	file.seekg (tempkey*sizeof (student), ios::beg);
	file.read ( (char*) &temp, sizeof (student) );
	temp.chain = key;
	file.seekg (tempkey*sizeof (student), ios::beg);
	file.write ( (char*) &temp, sizeof (student) );
	}
	//element not of same type
	else
	{
		int tempkey = key;
		int signal = 0;
		for (int i=0 ; i<TABLE_SIZE ; i++)
		{

			file.seekg ( (tempkey = hashing_function (tempkey+1))*sizeof (student), ios::beg );
			file.read ( (char*) &temp, sizeof (student) );
			if (temp.std_roll != -1) {
				if (hashing_function (temp.std_roll) == key)
				{
					tempkey = temp.loc;
					signal = 1;
					break;
				}
			}
		}
		if (signal == 0)
		{
			file.seekg (key*sizeof(student), ios::beg);
			file.read ( (char*) &temp, sizeof (student) );
			while ( temp.flag != -1 )
			{
				file.seekg ( (key = hashing_function (key+1))*sizeof(student), ios::beg );
				file.read ( (char*) &temp, sizeof (student) );
				key = temp.loc;
			}
			file.seekg( (key*sizeof(student)), ios::beg);
			s.loc = key;
			s.flag = 1;
			file.write ( (char*) &s, sizeof (student) );
			record_count ++;
		}
		else
		{
			while ( temp.chain != -1 )
			{
				file.seekg (temp.chain*sizeof(student), ios::beg);
				file.read ( (char*) &temp, sizeof (student) );
				tempkey = temp.loc;
			}
			file.seekg (key*sizeof(student), ios::beg);
			file.read ( (char*) &temp, sizeof (student) );
			while ( temp.flag != -1 )
			{
				file.seekg ( (key = hashing_function (key+1))*sizeof(student), ios::beg );
				file.read ( (char*) &temp, sizeof (student) );
				key = temp.loc;
			}
			file.seekg( (key*sizeof(student)), ios::beg);
			s.loc = key;
			s.flag = 1;
			file.write ( (char*) &s, sizeof (student) );
			record_count ++;
			file.seekg (tempkey*sizeof (student), ios::beg);
			file.read ( (char*) &temp, sizeof (student) );
			temp.chain = key;
			file.seekg (tempkey*sizeof (student), ios::beg);
			file.write ( (char*) &temp, sizeof (student) );
		}
	}
	file.close ();
	return record_count;
}

int student :: search (int r)
{
		fstream file;
		student temp;
		int key = hashing_function (r);
		file.open("student.txt", ios::in | ios::binary);
		file.seekg (key*sizeof (student), ios::beg);
		file.read( (char *) &temp, sizeof(student));
			//if empty
		if (temp.std_roll == -1)
		{
			file.close();
			return -1;
		}
			//if element of same type
		if ( hashing_function (temp.std_roll) == key )
		{
			do
			{
				if (temp.std_roll == r)
				{
					file.close();
					return key;
				}
				if (temp.chain != -1)
				{
					file.seekg (temp.chain*sizeof(student), ios::beg);
					file.read ( (char*) &temp, sizeof (student) );
				}
				key = temp.chain;
			} while (key != -1);
			if (temp.std_roll == r)
			{
				file.close();
				return temp.loc;
			}
			return -1;
		}
			//if element not of same type
		else
		{
			int tempkey = key;
			int signal = 0;
			while ( (tempkey = hashing_function (tempkey+1)) != key )
			{
				file.seekg ( tempkey*sizeof (student), ios::beg );
				file.read ( (char*) &temp, sizeof (student) );
				if (temp.std_roll != -1)
				{
					if ( hashing_function (temp.std_roll) == key )
					{
						signal = 1;
						break;
					}
				}
			}
			if (signal == 1)
			{
				do {
					if (temp.std_roll == r)
					{

						file.close();
						return tempkey;
					}
					if (temp.chain != -1)
					{
						file.seekg (temp.chain*sizeof(student), ios::beg);
						file.read ( (char*) &temp, sizeof (student) );
					}
					tempkey = temp.chain;
				} while (tempkey != -1);
				if (temp.std_roll == r)
				{
					file.close();
					return temp.loc;
				}
			}
			file.close ();
			return -1;
		}
		file.close();
		return -1;
}

void student :: modify_record (int key)
{
		fstream file;
		student temp;
		int r;
		file.open("student.txt", ios::out | ios::in | ios::binary | ios::ate);
		file.seekg ( key*sizeof (student), ios::beg );
		file.read ( (char*) &temp, sizeof (student) );
		r = temp.std_roll;
		temp.getdata();
		temp.std_roll = r;
		file.seekg ( key*sizeof (student), ios::beg );
		file.write ( (char*) &temp, sizeof (student) );
		file.close ();
}

void student :: save ()
{
	fstream file, temp;
	student s;
	file.open ("student.txt", ios::in | ios::binary);
	temp.open ("student_text_file.txt", ios::out);
	temp << "\n\t                                        |        MARKS        |" ;
	temp << "\nLocation Name\t      "
			" Roll_No Class Percentage Physics Maths Chemistry Flag Next_Link\n" << endl;
	file.read( (char *) &s, sizeof(s));
		while (file)
		{
			temp << left ;
			temp << setw (10) << s.loc;
			temp << setw(15) << s.std_name;
			temp << setw(8) << s.std_roll;
			temp << setw(6) << s.std_class;
			temp << setprecision(3) << setw(11) << s.per;
			temp << setw (8) << s.marks1;
			temp << setw (6) << s.marks2;
			temp << setw (10) << s.marks3;
			temp << setw (5) << s.flag;
			temp << setw (10) << s.chain <<endl;
			file.read( (char *) &s, sizeof(s));
		}
	file.close();
	temp.close();
}

void student :: print (int key)
{
	fstream file;
	student s;
	file.open ("student.txt", ios::in | ios::binary);
	file.seekg (key*sizeof (student), ios::beg);
	file.read ( (char*) &s, sizeof (student) );
	cout << "Name: " << s.std_name << endl;
	cout << "Roll No: " << s.std_roll << endl;
	cout << "Class: " << s.std_class << endl;
	cout << "Percentage: " << s.per << endl;
	cout << "Physics = " << s.marks1 << endl;
	cout << "Maths = " << s.marks2 << endl;
	cout << "Chemistry = " << s.marks3 << endl;
	file.close ();
}

int main ()
{
	student s, s1;
	static int record_count;
	int choice,flag,r,i,n;
	fstream file,temp;
	s.initialise();
	do
	{
		cout << "\n\nEnter 0 to Exit ";
		cout << "\nEnter 1 to Add Data/Record ";
		cout << "\nEnter 2 to Display Data ";
		cout << "\nEnter 3 to Modify Data  ";
		cout << "\nEnter 4 to Search Record ";
		cout << "\nEnter 5 to Convert To Text File ";
		cout << "\nEnter Your Choice : ";
		cin >> choice ;
		switch (choice)
		{
		case 0 : s.save();
				 break;
		case 1 : record_count = s.insert ();
				 break;
		case 2 : if (record_count != 0)
		{
				 cout << "\n\t                                        |        MARKS        |" ;
				 cout << "\nLocation Name\t       "
						 "Roll_No Class Percentage Physics Maths Chemistry Flag Next_Link\n" << endl;
				 file.open("student.txt", ios::out | ios::in | ios::binary | ios::ate);
				 file.seekg(0);
				 while ( file.read( (char *) &s, sizeof(s)) )
				{
					s.displaydata();
					cout<<endl;
				}
				 file.close();
		}
				 else cout << "\nPLEASE ADD RECORD... DATABASE EMPTY ";
				 break;
		case 3 : if (record_count != 0)
		{
				 cout << "\n Enter Roll No Of Record To Be Modified : ";
				 cin >> r;
				 flag = s.search(r);
				 if ( flag == -1)
				 {
				 	cout << "\nRECORD NOT FOUND " << endl;
				 }
				 else
				 {
					cout << endl << "\t RECORD FOUND SUCCESSFULLY " << endl;
				 	s.modify_record (flag);
					cout << endl << endl << "NEW DETAILS :" << endl << endl;
					s.print (flag);
					cout << endl << "\t RECORD MODIFIED SUCCESSFULLY " << endl;
				 }
		}
				 else cout << "\nPLEASE ADD RECORD... DATABASE EMPTY ";
				 break;
		case 4 : if (record_count != 0)
		{
			     cout << "\n Enter Roll No Of Record To Be searched : ";
			     cin >> r;
				 flag = s.search(r);
				 if ( flag == -1)
				 {
				 	cout << "\nRECORD NOT FOUND " << endl;
				 }
				 else
				 {
					cout << endl << "\t RECORD FOUND SUCCESSFULLY " << endl;
				 	s.print (flag);
				 }
		}
				 else cout << "\nPLEASE ADD RECORD... DATABASE EMPTY ";
				 break;

		case 5 : if (record_count != 0)
		{
				 s.save();
				 cout << "\nTEXT FILE CREATED SUCCESSFULLY\n\n ";
		}
				 else cout << "\nDATABASE EMPTY ";
				 break;
		default : cout << "\nPlease Enter Valid Choice ";
				  break;
	}
}while (choice!=0);// end of menu driven program
	return 0;
}
