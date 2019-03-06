typedef int T;

typedef struct node_t{
	T key;
	struct node_t * next;
}node_t;

typedef struct stack_t{
	node_t * data;
	int size;
}stack_t;

node_t * new_node(T value);
void push(stack_t * stack, T value);
T pop(stack_t * stack);
T top(stack_t * stack);
void print_stack(stack_t * stack);
int is_empty(stack_t * stack);
void remove_stack(stack_t * stack);