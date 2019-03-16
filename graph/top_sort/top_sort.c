#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"

typedef char bit;

enum COLOR{ WHITE, GREY, BLACK};

int dfs(node_t ** graph, int node, stack_t * stack, int vertices, char *color);
void top_sort(void **graph, int number_of_vertices, int flag);
void check_input(int vertices, int edges);
void error(char * error_msg);
void check_vertices(int start, int end, int vertices);
int matrixdfs(bit ** graph, int node, stack_t * stack, int vertices, char *color);
void clear_memory(bit **matrix, node_t ** graph, int number_of_vertices, int flag);
int is_dense_graph(int number_of_vertices, int number_of_edges);

int main(){
	int number_of_vertices = 0;
	int number_of_edges = 0;
	if (scanf("%d%d", &number_of_vertices, &number_of_edges) != 2){
		error("bad number of lines");
	}
	check_input(number_of_vertices, number_of_edges);
	
	int flag = is_dense_graph(number_of_vertices, number_of_edges);
	bit **matrix = 0;
	node_t **graph = 0;
	int i = 0;
	if (flag){
		matrix = (bit *)malloc(sizeof(bit *) * number_of_vertices);
		for (i = 0; i < number_of_vertices; ++i){
			matrix[i] = (bit *)calloc(number_of_vertices, sizeof(bit));
		}
	}
	else{
		graph = (node_t *)calloc(number_of_vertices, sizeof(node_t));
	}
	unsigned int edges_count = 0;
	int start = 0;
	int end = 0;
	while (scanf("%d%d", &start, &end) == 2 && !feof(stdin)){
		edges_count++;
		check_vertices(start, end, number_of_vertices);
		if (flag)
			matrix[start-1][end-1] = 1;
		else
			graph[start-1] = add_to_list(graph[start-1], end-1);
	}
	if (edges_count != number_of_edges){
		error("bad number of lines");
	}	
	top_sort(flag ? matrix : graph, number_of_vertices, flag);		
	clear_memory(matrix, graph, number_of_vertices, flag);
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

int matrixdfs(bit ** graph, int node, stack_t * stack, int vertices, char *color){
	if (color[node] == GREY){
		return 1;
	}
	if (color[node] == BLACK){
		return 0;
	}
	color[node] = GREY;
	int i = 0;
	for (i = 0; i < vertices; ++i){
		if (graph[node][i] && matrixdfs(graph, i, stack, vertices, color)){
			return 1;
		}
	}
	push(stack, node);
	color[node] = BLACK;
	return 0;
}


void top_sort(void **graph, int number_of_vertices, int flag){
	char * color = (char *)calloc(number_of_vertices, sizeof(char));
	stack_t stack;
	stack.size = 0;
	stack.data = NULL;
	int i = 0;
	int cycle = 0;
	for (i = 0; i < number_of_vertices; ++i){
		if (flag){
			cycle = matrixdfs(graph, i, &stack, number_of_vertices, color);
		}
		else{
			cycle = dfs(graph, i, &stack, number_of_vertices, color);
		}
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


void check_input(int vertices, int edges){
	if (vertices < 0 || vertices > 1000){
		error("bad number of vertices");
	}
	if (edges < 0 || edges > vertices * ((vertices + 1) / 2)){
		error("bad number of edges");
	}
	return 0; 
}

void check_vertices(int start, int end, int vertices){
	if (start < 1 || start > vertices || end < 1 || end > vertices){
		error("bad vertex");
	}
}

void clear_memory(bit **matrix, node_t ** graph, int number_of_vertices, int flag){
	for (int i = 0; i < number_of_vertices; ++i){
		if (flag)
			free(matrix[i]);
		else
			free(graph[i]);		
	}
	free(graph);
	free(matrix);
}

int is_dense_graph(int number_of_vertices, int number_of_edges){
	return number_of_edges > ((number_of_vertices * (number_of_vertices + 1)) / 3);
}

void error(char * error_msg){
	printf("%s", error_msg);
	exit(0);
}


