#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"

typedef char bit;

enum COLOR{ WHITE, GREY, BLACK};

int dfs(node_t ** graph, int node, stack_t * stack, int vertices, char *color);
void top_sort(node_t **graph, int number_of_vertices);
int check_input(int vertices, int edges);
void error(char * error_msg);

int main(){
	int number_of_vertices = 0;
	int number_of_edges = 0;
	if (scanf("%d%d", &number_of_vertices, &number_of_edges) != 2){
		error("bad number of lines");
	}
	int error_code = check_input(number_of_vertices, number_of_edges);
	if (error_code){
		error(error_code == 1 ? "bad number of vertices" : "bad number of edges");
	}
	node_t **graph = (node_t *)calloc(number_of_vertices, sizeof(node_t));
	int i = 0;
	unsigned int edges_count = 0;
	int start = 0;
	int end = 0;
	while (scanf("%d%d", &start, &end) == 2 && !feof(stdin)){
		edges_count++;
		if (!check_vertices(start, end, number_of_vertices)){
			error("bad vertices");
		}
		graph[start-1] = add_to_list(graph[start-1], end-1);
	}
	if (edges_count != number_of_edges){
		error("bad number of lines");
	}
	top_sort(graph, number_of_vertices);
	for (i = 0; i < number_of_vertices; ++i){
		free(graph[i]);
	}
	free(graph);
	return 0;
}

int dfs(node_t ** graph, int node, stack_t * stack, int vertices, char *color){
	if (color[node] == GREY){
		return 1;
	}
	if (color[node] == BLACK){
		return 0;
	}
	color[node] = GREY;
	node_t * k = graph[node];
	while(k){
		if (dfs(graph, k->data, stack, vertices, color)){
			return 1;
		}
		k = get_next_node(k);
	}	
	push(stack, node);
	color[node] = BLACK;
	return 0;
}

void top_sort(node_t **graph, int number_of_vertices){
	char * color = (char *)calloc(number_of_vertices, sizeof(char));
	stack_t stack;
	stack.size = 0;
	stack.data = NULL;
	int i = 0;
	int cycle = 0;
	for (i = 0; i < number_of_vertices; ++i){
		cycle = dfs(graph, i, &stack, number_of_vertices, color);
		if (cycle){
			error("impossible to sort");
		}
	}
	free(color);
	int size = stack.size;
	for (i = 0; i < size; ++i){
		printf("%d ", pop(&stack) + 1);
	}
	remove_stack(&stack);
}

int check_input(int vertices, int edges){
	if (vertices < 0 || vertices > 1000){
		return 1;
	}
	if (edges < 0 || edges > vertices * ((vertices + 1) / 2)){
		return 2;
	}
	return 0; 
}

int check_vertices(int start, int end, int vertices){
	if (start < 1 || start > vertices || end < 1 || end > vertices){
		return 0;
	}
	return 1;
}


void error(char * error_msg){
	printf("%s", error_msg);
	exit(0);
}


