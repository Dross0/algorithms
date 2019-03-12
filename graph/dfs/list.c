typedef int T;

typedef struct node_t{
	T data;
	struct node_t * next;
}node_t;

node_t * add_to_list(node_t * prev, T value){
	node_t * tmp = (node_t *)malloc(sizeof(node_t));
	tmp->data = value;
	tmp->next = prev->next;
	prev->next = tmp;
	return tmp; 
}

node_t * init(T value){
	node_t * tmp = (node_t *)malloc(sizeof(node_t));
	tmp->data = value;
	tmp->next = 0;
	return tmp; 
}

node_t * remove_from_list(node_t * head, node_t * node_for_remove){
	node_t * cur = head;
	while (cur->next && cur->next != node_for_remove){
		cur = cur->next;
	}
	cur->next = node_for_remove->next;
	free(node_for_remove);
	return cur;
}

node_t * remove_head(node_t * head){
	node_t * tmp = head->next;
	free(head);
	return tmp;
}

node_t * search(node_t * head, T value){
	node_t * cur = head;
	while (cur && cur->data != value){
		cur = cur->next;
	}
	return cur;
}

node_t * remove_value(node_t * head, T value){
	node_t * tmp = search(head, value);
	if (tmp)
		return remove_from_list(head, tmp);
	return 0;
}

void print_list(node_t * head){
	node_t * cur = head;
	while (cur){
		printf("%d ", cur->data);
		cur = cur->next;
	}
}

node_t * get_next_node(node_t * node){
	return node->next;
}
