

typedef int T;

typedef struct tree_node{
	T data;
	struct tree_node * right;
	struct tree_node * left;
}tree_node;

tree_node * new_node(T value){
	tree_node * tmp = (tree_node *)malloc(sizeof(tree_node));
	tmp->right = tmp->left = 0;
	tmp->data = value;
	return tmp;
}

tree_node * add_to_tree(tree_node * root, T value){
	if (!root){
		return new_node(value);
	}
	if (root->data > value){
		root->left = add_to_tree(root->left, value);
	}
	else{
		root->right = add_to_tree(root->right, value);
	}
	return root;
}

void infix_print(tree_node * root){
	if (root){
		infix_print(root->left);
		printf("%d ", root->data);
		infix_print(root->right);
	}
}

void prefix_print(tree_node * root){
	if (root){
		printf("%d ", root->data);
		prefix_print(root->left);
		prefix_print(root->right);
	}

}

void postfix_print(tree_node * root){
	if (root){
		postfix_print(root->left);
		postfix_print(root->right);
		printf("%d ", root->data);
	}
}

tree_node * find(tree_node * root, T value){
	if (!root){
		return 0;
	}
	if (root->data == value){
		return root;
	}
	else if (root->data > value){
		find(root->left, value);
	}
	else{
		find(root->right, value);
	}
	return 0;
}


