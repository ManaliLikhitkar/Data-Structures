#ifndef QUEUE_H_
#define QUEUE_H_

template<class T>
class queue
{
	struct node1
	{
		T data;
		node1 *next;
	};
	node1 *front,*rear;
public:
	queue();
	int isempty();
	void enqueue(T a);
	int sizeq();
	T dequeue();
	virtual ~queue();
};

#endif
