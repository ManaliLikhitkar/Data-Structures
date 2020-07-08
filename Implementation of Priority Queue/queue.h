#ifndef QUEUE_H_
#define QUEUE_H_
struct patient
{
	int id;
	char name[20];
	char disease[20];
	char phone[13];
};
template <class T>
class queue
{
  public:
	struct node
	{
		T p;
		int priority;
		struct node *next;
	};
	struct node *front;
	struct node *rear;
	void enqueue(T t, int priority);
	T dequeue(int *flag);
	int isempty();
	int display(T a[]);
	queue();
	virtual ~queue();
};
#endif
