typedef int T;

typedef struct node_s{
	T key;
	struct node_s * next;
}node_s;

typedef struct stack_t{
	node_s * data;
	int size;
}stack_t;

node_s * new_node(T value);
void push(stack_t * stack, T value);
T pop(stack_t * stack);
T top(stack_t * stack);
void print_stack(stack_t * stack);
int is_empty(stack_t * stack);
void remove_stack(stack_t * stack);