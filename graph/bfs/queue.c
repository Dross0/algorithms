
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

void enqueue(queue_t * queue, T value){
	node_q * node = (node_q *)malloc(sizeof(node_q));
	node->data = value;
	node->next = 0;
	if (queue->size == 0){
		queue->head = queue->tail = node; 
	}
	else{
		queue->tail->next = node;
		queue->tail = queue->tail->next;
	}
	queue->size++;
}

T dequeue(queue_t * queue){
	if (queue->size <= 0)
		exit(1);
	node_q * node = queue->head;
	queue->head = queue->head->next;
	T res = node->data;
	free(node);
	queue->size--;
	return res;
}

int is_empty(queue_t * queue){
	return !queue->size;
}




