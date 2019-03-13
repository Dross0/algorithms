typedef int T;

typedef struct node_t{
	T data;
	struct node_t * next;
}node_t;

node_t * add_to_list(node_t * prev, T value);
node_t * init(T value);
node_t * remove_from_list(node_t * head, node_t * node_for_remove);
node_t * remove_head(node_t * head);
node_t * search(node_t * head, T value);
node_t * remove_value(node_t * head, T value);
void print_list(node_t * head);
node_t * get_next_node(node_t * node);