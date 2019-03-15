typedef int T;

typedef struct node_t{
	T key;
	struct node_t * next;
}node_t;

typedef struct stack_t{
	node_t * data;
	int size;
}stack_t;

node_t * new_node(T value){
	node_t * p = (node_t *)malloc(sizeof(node_t));
	p->key = value;
	return p;
}

void push(stack_t * stack, T value){
	node_t * node_for_add = new_node(value);
	node_for_add->next = stack->data;
	stack->data = node_for_add; 
	stack->size++;
}

T pop(stack_t * stack){
	if (stack->size <= 0)
		exit(1);
	node_t * node_for_pop = stack->data;
	T pop_value = node_for_pop->key;
	stack->data = node_for_pop->next;
	free(node_for_pop);
	stack->size--;
	return pop_value; 
}

T top(stack_t * stack){
	if (stack->size <= 0)
		exit(1);
	return stack->data->key;
}

void print_stack(stack_t * stack){
	node_t * cur = stack->data;
	while (cur){
		printf("%d ", cur->key);
		cur = cur->next;
	}
	printf("\n");
}

void remove_stack(stack_t * stack){
	node_t * c;
	while (stack->data){
		c = stack->data;
		stack->data = stack->data->next;
		free(c);
	}
	stack->size = 0;
}

int is_empty(stack_t * stack){
	return !stack->size;
}

