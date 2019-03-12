#include <stdio.h>
#include <stdlib.h> 
typedef int T;

typedef struct node_t{
	T data;
	unsigned char height;
	struct node_t * left;
	struct node_t * right;
}node;

unsigned char height(node * root);
int balance_factor(node * root);
void fix_height(node * root);
void free_tree(node * root);
node * right_rotate(node * root);
node * left_rotate(node * root);
node * balance(node * root);
node * insert(node * root, T value);


unsigned char height(node * root){
	return root ? root->height:0;
}

int balance_factor(node * root){
	return height(root->right) - height(root->left);
}

void fix_height(node * root){
	unsigned char hl = height(root->left);
	unsigned char hr = height(root->right);
	root->height = (hl > hr ? hl:hr) + 1;
}

node * right_rotate(node * root){
	node * t = root->left;
	root->left = t->right;
	t->right = root;
	fix_height(root);
	fix_height(t);
	return t;
}

node * left_rotate(node * root){
	node * t = root->right;
	root->right = t->left;
	t->left = root;
	fix_height(root);
	fix_height(t);
	return t;
}

node * balance(node * root){
	fix_height(root);
	char root_balance_factor = balance_factor(root);
	if (root_balance_factor == 2){
		if (balance_factor(root->right) < 0)
			root->right = right_rotate(root->right);
		return left_rotate(root);
	}
	else if (root_balance_factor == -2){
		if (balance_factor(root->left) > 0)
			root->left = left_rotate(root->left);
		return right_rotate(root);
	}
	return root;
}

node * insert(node * root, T value){
	if (root == NULL){
		root = (node *)malloc(sizeof(node));
		root->data = value;
		root->height = 1;
		root->left = root->right = NULL;
		return root;
	}
	if (root->data > value)
		root->left = insert(root->left, value);
	else
		root->right = insert(root->right, value);
	return balance(root);
}

void free_tree(node * root){
	if (root != NULL){
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

int main(){
	int n = 0;
	scanf("%d", &n);
	node * root = NULL;
	int i = 0;
	T element = 0;
	for (i = 0; i < n; ++i){
		scanf("%d", &element);
		root = insert(root, element);
	}
	printf("%d", height(root));
	free_tree(root);
	return 0;
}
