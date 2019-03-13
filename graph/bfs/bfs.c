#include <stdio.h>
#include "list.h"
#include "queue.h"

void bfs(node_t ** graph, int start, int n){
	char * visited = (char *)calloc(n, sizeof(char));
	char * in_queue = (char *)calloc(n, sizeof(char));
	queue_t queue;
	queue.size = 0;
	queue.head = queue.tail = 0;
	int graph_node = 0;
	node_t * child = 0;
	enqueue(&queue, start);
	in_queue[start] = 1;
	while (!is_empty(&queue)){
		graph_node = dequeue(&queue);
		visited[graph_node] = 1;
		in_queue[graph_node] = 0;
		printf("%d\n", graph_node);
		child = graph[graph_node];
		while (child){
			if (!visited[child->data] && !in_queue[child->data]){
				enqueue(&queue, child->data);
				in_queue[child->data] = 1;
			}
			child = get_next_node(child);
		}
	}
}




int main(){
	int n = 0;
	printf("Количество вершин: ");
	scanf("%d", &n);
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
	bfs(array, start, n);
	return 0;
}