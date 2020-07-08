#ifndef STACK_H_
#define STACK_H_
template<class T>
class stack
{
 public:
	stack();
	struct node
	{
		T data;
		struct node *next;
	};
	struct node *top;
	void push(T x);
	T get_top();
	T pop();
	int isempty();
	virtual ~stack();
};
#endif
