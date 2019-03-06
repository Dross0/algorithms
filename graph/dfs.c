#include <stdio.h>
#include "list.h"

typedef struct stack_t{
	int data[1000];
	int size;
}stack_t;

void push(stack_t * s, int el){

	s->data[s->size++] = el;
}

int pop(stack_t * s){
	return s->data[--s->size];
}

int is_empty(stack_t *s){
	return !s->size;
}

void  dfs(node_t * array[], int node, unsigned char visited[]){
	visited[node] = 1;
	printf("node = %d\n", node);
	node_t * k = array[node];
	while (k){
		if (!visited[k->data]){
			dfs(array, k->data, visited);
		}
		k = get_next_node(k);
	}
}

void stack_dfs(node_t *array[], int node, int n){
	stack_t stack;
	stack.size = 0;
	unsigned char * visited = (unsigned char *)calloc(n, sizeof(unsigned char));
	push(&stack, node);
	int c = 0;
	node_t * k = 0;
	while (!is_empty(&stack)){
		c = pop(&stack);
		printf("node = %d\n", c);
		k = array[c];
		visited[c] = 1;
		while (k){
			if (!visited[k->data])
				push(&stack, k->data);
			k = get_next_node(k);
		}
	}
}

void no_duplicates_stack_dfs(node_t *array[], int node, int n){
	stack_t stack;
	stack.size = 0;
	unsigned char * visited = (unsigned char *)calloc(n, sizeof(unsigned char));
	unsigned char * in_stack = (unsigned char *)calloc(n, sizeof(unsigned char));
	push(&stack, node);
	in_stack[node] = 1;
	int c = 0;
	node_t * k = 0;
	while (!is_empty(&stack)){
		c = pop(&stack);
		in_stack[c] = 0;
		printf("node = %d\n", c);
		k = array[c];
		visited[c] = 1;
		while (k){
			if (!visited[k->data] && !in_stack[k->data]){
				push(&stack, k->data);
				in_stack[k->data] = 1;
			}
			k = get_next_node(k);
		}
	}
}



int main(){
	int n = 0;
	printf("Количество вершин: ");
	scanf("%d", &n);
	unsigned char * visited = (unsigned char *)calloc(n, sizeof(unsigned char));
	node_t ** array = (node_t *)malloc(sizeof(node_t) * n);
	node_t * p = NULL;
	int i = 0;
	int child = 0;
	int is_init = 0;
	for (i = 0; i < n; ++i){
		printf("Вершины связанные с %d: ", i);
		scanf("%d", &child);
		is_init = 1;
		while(child != -1){
			if (child >= n){
				printf("Error");
				return 1;
			}
			if (is_init){
				array[i] = init(child);
				p = array[i];
				is_init = 0;
			}
			else{
				p = add_to_list(p, child);
			}
			scanf("%d", &child);
		}
	}
	int start = 0;
	printf("Введите вершину с которой начать обход: ");
	scanf("%d", &start);	
	if (start < 0 || start >= n){
		printf("Wrong start!\n");
		return 2;
	}
	dfs(array, start, visited);
	printf("\n\n\n");
	stack_dfs(array, start, n);
	printf("\n\n\n");
	no_duplicates_stack_dfs(array, start, n);
	return 0;
}
