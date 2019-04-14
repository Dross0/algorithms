#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

const int INF = INT_MAX - 1;

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
void print_result(pair_t ** res, int len);
pair_t * get_min(const int ** graph, const int * used, const int N);
int get_min_edge(const int ** graph, const int * used, const int N, const int node);
void prim(const int ** graph, const int N);
int ** create_graph(const int N);



int main(){
	int number_of_vertices = 0;
	int number_of_edges = 0;
	if (scanf("%d%d", &number_of_vertices, &number_of_edges) != 2){
		error("bad number of lines");
	}
	check_input(number_of_vertices, number_of_edges);
	int ** graph = create_graph(number_of_vertices);
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

int get_min_edge(const int ** graph, const int * used, const int N, const int node){
    int min_node = -1;
    int min_len = INF;
    int i = 0;
    for (i = 0; i < N; ++i){
        if (!used[i] && graph[node][i] < min_len){
            min_len = graph[node][i];
            min_node = i;
        }
    }
    return min_node;
}

pair_t * get_min(const int ** graph, const int * used, const int N){
    pair_t * pair = (pair_t *)malloc(sizeof(pair_t));
    pair->first = -1;
    pair->second = -1;
    int min_len = INF;
    int i = 0;
    int node = -1;
    for (i = 0; i < N; ++i){
        if (used[i]){
            node = get_min_edge(graph, used, N, i);
            if (node != -1 && graph[i][node] < min_len){
                min_len = graph[i][node];
                pair->first = i;
                pair->second = node;  
            }
        }
    }
    return pair;
}

void prim(const int ** graph, const int N){
    int * used = (int *)calloc(N, sizeof(int));
    pair_t ** res = (pair_t *)malloc(sizeof(pair_t *) * (N-1));
    int i = 0;
    int j = 0;
    used[0] = 1;
    pair_t * edge = 0;
    while (i < (N - 1)){
        edge = get_min(graph, used, N);
        if (edge->first == -1 || edge->second == -1){
            error("no spanning tree");
        }
        used[edge->second] = 1;
        used[edge->first] = 1;
        res[j++] = edge;
        i++;
    }
    print_result(res, j);
}


int ** create_graph(const int N){
    int **graph = (int *)malloc(sizeof(int *) * N);
    int i = 0;
    for (i = 0; i < N; ++i){
        graph[i] = (int *)malloc(sizeof(int) * N);
        for (int j = 0; j < N; ++j){
            graph[i][j] = INF;
        }
    }
    return graph;
}


void print_result(pair_t ** res, int len){
	int i = 0;
	for (i = 0; i < len; ++i){
		printf("%d %d\n", res[i]->first + 1, res[i]->second + 1);
	}
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
