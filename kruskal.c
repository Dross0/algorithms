#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct edge_t{
	int len;
	int start;
	int end;
}edge_t;

typedef struct pair_t{
	int first;
	int second;
}pair_t;

void check_input(int vertices, int edges);
int comp(const edge_t * edge1, const edge_t * edge2);
void check_edge(edge_t edge, int vertices, int edges);
void kruskal(edge_t * graph, int number_of_vertices, int number_of_edges);
void check_number_of_lines(int number_of_lines, int number_of_edges);
void error(char * error_msg);
void print_result(pair_t * res, int len);

int main(){
	int number_of_vertices = 0;
	int number_of_edges = 0;
	if (scanf("%d%d", &number_of_vertices, &number_of_edges) != 2){
		error("bad number of lines");
	}
	check_input(number_of_vertices, number_of_edges);
	edge_t *graph = (edge_t *)malloc(sizeof(edge_t) * number_of_edges);
	int number_of_lines = 0;
	edge_t edge;
	while (scanf("%d%d%d", &edge.start, &edge.end, &edge.len) == 3 && !feof(stdin)){
		check_edge(edge, number_of_vertices, number_of_edges);
		graph[number_of_lines++] = edge;
	}
	check_number_of_lines(number_of_lines, number_of_edges);
	qsort(graph, number_of_edges, sizeof(edge_t), (int(*) (const void *, const void *)) comp);
	kruskal(graph, number_of_vertices, number_of_edges);
}

void kruskal(edge_t * graph, int number_of_vertices, int number_of_edges){
	int * tree_id = (int *)malloc(sizeof(int) * number_of_vertices);
	int i = 0;
	for (i = 0; i < number_of_vertices; ++i){
		tree_id[i] = i;
	}
	pair_t *res = (pair_t *)calloc(number_of_edges, sizeof(pair_t));
	int start = 0;
	int end = 0;
	int new_id = 0;
	int old_id = 0;
	int j = 0;
	int k = 0;
	pair_t pair;
	for (i = 0; i < number_of_edges; ++i){
		start = graph[i].start - 1;
		end = graph[i].end - 1;
		if (tree_id[start] != tree_id[end]){
			pair.first = start + 1;
			pair.second = end + 1;
			res[k++] = pair;
			old_id = tree_id[end];
			new_id = tree_id[start];
			for (j = 0; j < number_of_vertices; ++j){
				if (tree_id[j] == old_id){
					tree_id[j] = new_id;
				}
			}
		}
	}
	for (i = 0; i < number_of_vertices; ++i){
		if (tree_id[i] != tree_id[0]){
			error("no spanning tree");
		}
	}
	print_result(res, k);
	free(tree_id);
	free(res);
}

void print_result(pair_t * res, int len){
	int i = 0;
	for (i = 0; i < len; ++i){
		printf("%d %d\n", res[i].first, res[i].second);
	}
}

int comp(const edge_t * edge1, const edge_t * edge2){
	return edge1->len - edge2->len;
}


void check_input(int vertices, int edges){
	if (vertices < 0 || vertices > 5000){
		error("bad number of vertices");
	}
	if (edges < 0 || edges > vertices * ((vertices + 1) / 2)){
		error("bad number of edges");
	}
}

void check_edge(edge_t edge, int vertices, int edges){
	if (edge.start < 1 || edge.start > vertices || edge.end < 1 || edge.end > vertices){
		error("bad vertex");
	}
	if (edge.len < 0 || edge.len > INT_MAX){
		error("bad length");
	}
}

void check_number_of_lines(int number_of_lines, int number_of_edges){
	if (number_of_edges != number_of_lines){
		error("bad number of lines");
	}
}

void error(char * error_msg){
	printf("%s", error_msg);
	exit(0);
}