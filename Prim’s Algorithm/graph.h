
#include<iostream>
#include<string>
using namespace std;


struct frnd
{
	string f_name;
	int dist;
	frnd * link;
	int visited;

	struct node * current_vertex;

};

struct node
{
	string Name;
	int id;
	node * down;
	frnd * next;
	int visited;
};

#ifndef ADJ_LIST_H_
#define ADJ_LIST_H_

class graph
{
	node * root;
	int n;
	int cost;

public:
		graph();
		void create();
		frnd * add_friend(node *);
		void display();

		node * search(string);
		node * min_edge(node *,node *);

		//node * prims();
		void prim();
		void display_mst();
};

#endif /* ADJ_LIST_H_ */
