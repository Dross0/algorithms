typedef int T;

typedef struct node_q{
	T data;
	struct node_q * next;
}node_q;

typedef struct queue_t{
	node_q * head;
	node_q * tail;
	unsigned int size;
}queue_t;

void enqueue(queue_t * queue, T value);
T dequeue(queue_t * queue);
int is_empty(queue_t * queue);