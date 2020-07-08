/*============================================================================
                           Prim's Algorithm
Assignment no. : 10
Roll no.       : 23333
Batch          : F11
============================================================================*/

#include <iostream>
#include<stdlib.h>
#include "graph.h"
using namespace std;

int main()
{
	graph g;

	do
		{
			int ch;
			cout<<"\tMENU\n";

			cout<<"\t\t1.Enter Adjecency list\n\t\t2.Display graph\n\t\t3.Prim\n\t\t"
					"4.Display minimum spanning tree"
					"\n\t\t5.Re_Enter\n\t\t6.Exit\n";
			cout<<"Enter Choice : ";
			cin>>ch;
			cout<<endl;

			switch(ch)
			{

				case 1:
							g.create();
							break;

				case 2:
							g.display();
							break;

				case 3:
							g.prim();
							break;

				case 4:
							g.display_mst();
							break;

				case 5:
							main();
							break;

				case 6:
							exit(0);
							break;

			}
		}
		while(1);
	return 0;

}
