typedef int T;

typedef struct node_s{
	T key;
	struct node_s * next;
}node_s;

typedef struct stack_t{
	node_s * data;
	int size;
}stack_t;

node_s * new_node(T value){
	node_s * p = (node_s *)malloc(sizeof(node_s));
	p->key = value;
	return p;
}

void push(stack_t * stack, T value){
	node_s * node_for_add = new_node(value);
	node_for_add->next = stack->data;
	stack->data = node_for_add; 
	stack->size++;
}

T pop(stack_t * stack){
	if (stack->size <= 0)
		exit(1);
	node_s * node_for_pop = stack->data;
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
	node_s * cur = stack->data;
	while (cur){
		printf("%d ", cur->key);
		cur = cur->next;
	}
	printf("\n");
}

void remove_stack(stack_t * stack){
	node_s * c;
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

