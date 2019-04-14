#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


typedef unsigned int uint;
const uint INF = INT_MAX + 1;

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
void check_edge(edge_t edge, int vertices, int edges);
void check_number_of_lines(int number_of_lines, int number_of_edges);
void error(char * error_msg);
void print_result(pair_t * res, int len);
void prim(const uint ** graph, const int N);
uint ** create_graph(const int N);



int main(){
	int number_of_vertices = 0;
	int number_of_edges = 0;
	if (scanf("%d%d", &number_of_vertices, &number_of_edges) != 2){
		error("bad number of lines");
	}
	check_input(number_of_vertices, number_of_edges);
	uint ** graph = create_graph(number_of_vertices);
	int number_of_lines = 0;
	edge_t edge;
	while (number_of_lines != number_of_edges && scanf("%d%d%d", &edge.start, &edge.end, &edge.len) == 3 && !feof(stdin)){
		check_edge(edge, number_of_vertices, number_of_edges);
		graph[edge.start - 1][edge.end - 1] = edge.len;
        graph[edge.end - 1][edge.start - 1] = edge.len;
        number_of_lines++;
	}
	check_number_of_lines(number_of_lines, number_of_edges);
	prim(graph, number_of_vertices);
}

void prim(const uint ** graph, const int N){ 
	int * used = (int *)calloc(N, sizeof(int));
	uint * min_len_for_node = (uint *)malloc(N *sizeof(uint));
	int * min_edge_for_node = (int *)malloc(sizeof(int) * N);
	pair_t * res = (pair_t *)malloc(sizeof(pair_t) * (N-1));
	pair_t edge;
	int i = 0;
	for (i = 0; i < N; ++i){
	 	min_len_for_node[i] = INF;
		min_edge_for_node[i] = -1;
	}
	int k = 0;
	int vert = 0;
	int j = 0;
 	min_len_for_node[0] = 0;
	for (i = 0; i < N; ++i) {
    	vert = -1;
    	for (j = 0; j < N; ++j)
        	if (!used[j] && (vert == -1 || min_len_for_node[j] < min_len_for_node[vert]))
            	vert = j;
    	if  (min_len_for_node[vert] == INF) {
        	error("no spanning tree");
    	} 
    	used[vert] = 1;
    	if (min_edge_for_node[vert] != -1){
    		edge.first = vert;
    		edge.second = min_edge_for_node[vert];
        	res[k++] = edge;
    	}
 		int node = 0;
    	for (node=0; node < N; ++node){
        	if (!used[node] && graph[vert][node] < min_len_for_node[node]) {
             	min_len_for_node[node] = graph[vert][node];
            	min_edge_for_node[node] = vert;
        	}
    	}
    }
    print_result(res, k);
}

uint ** create_graph(const int N){
    uint **graph = (uint *)malloc(sizeof(uint *) * N);
    int i = 0;
    for (i = 0; i < N; ++i){
        graph[i] = (uint *)malloc(sizeof(uint) * N);
        for (int j = 0; j < N; ++j){
            graph[i][j] = INF;
        }
    }
    return graph;
}

void print_result(pair_t * res, int len){
	int i = 0;
	for (i = 0; i < len; ++i){
		printf("%d %d\n", res[i].first + 1, res[i].second + 1);
	}
}

void check_input(int vertices, int edges){
	if (vertices == 0 && edges == 0){
		error("no spanning tree");
	}
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