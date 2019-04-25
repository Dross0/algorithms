#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

enum mode {
	COMPRESSION = 'c',
	DECOMPRESSION = 'd'
};

typedef struct pair_t {
	char symbol;
	char *code;
}pair_t;

void error(char * err_msg, int err_code);
node_t * make_node_arr(int * frequency_table, int number_of_unique_symblols, const int ALPHABET_SIZE);
int change_frequency(int * frequency_table, uchar * buffer, int size, const int ALPHABET_SIZE);
void print_node(node_t * root);
node_t * connect_node(node_t * node1, node_t * node2);
void make_code_table(pair_t * code_table, node_t * root, char *code, int pos, int * i);
char * get_symbol_code(pair_t * code_table, int code_table_size, char symbol);
int power(int a, int n);
char convert_byte_to_char(char * byte, const int BYTE_SIZE);
void insert_in_str(char * dest, char * source, int count, int * pos);
uchar * coding(pair_t * code_table, int code_table_size, char * res_str, char * buffer, int size);
void mk(pair_t * code_table, int code_table_size, const int BUFFER_SIZE, FILE * in);


int main(){
	const int BUFFER_SIZE = 1000;
	const int ALPHABET_SIZE =  256;
	FILE * in = fopen("in.txt", "r");
	if (in == NULL) {
		error("Cant open input file", 0);
	}
	char mode = 0;
	fscanf(in, "%c\n", &mode);
	uchar * buffer = (uchar *)calloc(BUFFER_SIZE, sizeof(uchar));
	int * frequency_table = (int *)calloc(ALPHABET_SIZE, sizeof(int));
	int size = 0;
	int number_of_unique_symbols = 0;
	while ((size = fread(buffer, sizeof(char), BUFFER_SIZE, in))) {
		number_of_unique_symbols += change_frequency(frequency_table, buffer, size, ALPHABET_SIZE);
	}
	free(buffer);
	node_t * arr = make_node_arr(frequency_table, number_of_unique_symbols, ALPHABET_SIZE);
	heap_t * heap = build_heap(arr, number_of_unique_symbols, MIN_HEAP);
	while (heap->size != 1) {
		node_t  min_node1 = extract(heap);
		node_t  min_node2 = extract(heap);
		node_t * connected_node = connect_node(&min_node1, &min_node2);
		add_to_heap(heap, *connected_node);
		free(connected_node);
	}
	free(frequency_table);
	pair_t * code_table = (pair_t *)malloc(sizeof(pair_t) * number_of_unique_symbols);
	node_t tree = extract(heap);
	char c[100] = { 0 };
	int code_index = 0;
	make_code_table(code_table, &tree, c, 0, &code_index);
	for (int i = 0; i < number_of_unique_symbols; ++i) {
		printf("%c - %s\n", code_table[i].symbol, code_table[i].code);
	}
	return 0;
}

void mk(pair_t * code_table, int code_table_size, const int BUFFER_SIZE, FILE * in) {
	fseek(in, 2, SEEK_SET);
	uchar * res_str = (uchar *)calloc(BUFFER_SIZE + 1, sizeof(uchar));
	uchar * buffer = (uchar *)malloc((BUFFER_SIZE + 1) * sizeof(uchar));
	int size = 0;
	while ((size = fread(buffer, sizeof(uchar), BUFFER_SIZE, in))) {
		coding(code_table, code_table_size, res_str, buffer, size);
	}
}


uchar * coding(pair_t * code_table, int code_table_size, char * res_str, char * buffer, int size) {
	const int BYTE_SIZE = 8;
	char * byte = (char *)malloc((BYTE_SIZE + 1) * sizeof(char));
	int i = 0;
	char * symbol_code = 0;
	int code_size = 0;
	int byte_index = 0;
	char res_symbol = 0;
	int res_str_index = 0;
	for (i = 0; i < size; ++i) {
		symbol_code = get_symbol_code(code_table, code_table_size, buffer[i]);
		code_size = strlen(symbol_code);
		if (code_size + byte_index < BYTE_SIZE) {
			insert_in_str(byte, symbol_code, code_size, &byte_index);
		}
		else {
			insert_in_str(byte, symbol_code, BYTE_SIZE - byte_index - 1, &byte_index);
			res_symbol = convert_byte_to_char(byte, BYTE_SIZE);
			res_str[res_str_index++] = res_symbol;
			memset(byte, 0, sizeof(char) * BYTE_SIZE);
			int j = 0;
			//for (j = BYTE_SIZE ; j <)
			byte_index = 0;
		}

	}

}

void insert_in_str(char * dest, char * source, int count, int * pos) {
	int i = 0;
	while (count) {
		dest[*pos] = source[i++];
		*pos += 1;
		count--;
	}
}

char convert_byte_to_char(char * byte, const int BYTE_SIZE) {
	char symbol = 0;
	int i = 0;
	for (i = 0; i < BYTE_SIZE; ++i) {
		if (byte[i] == '1') {
			symbol += power(2, BYTE_SIZE - 1 - i);
		}
	}
	return symbol;
}

int power(int a, int n) {
	if (n == 0) {
		return 1;
	}
	else if (n % 2 == 0) {
		return power(a*a, n / 2);
	}
	return a * power(a, n - 1);
}


char * get_symbol_code(pair_t * code_table, int code_table_size, char symbol) {
	int i = 0;
	for (i = 0; i < code_table_size; ++i) {
		if (code_table[i].symbol == symbol) {
			return code_table[i].code;
		}
	}
}

void make_code_table(pair_t * code_table, node_t * root, char *code, int pos, int * code_index) {
	if (root) {
		if (!root->right && !root->left) {
			pair_t pair;
			pair.code = (char *)calloc(pos + 1, sizeof(char));
			memcpy(pair.code, code, pos);
			pair.symbol = root->symbol;
			code_table[*code_index] = pair;
			*code_index += 1;
		}
		if (root->right) {
			code[pos] = '1';
			make_code_table(code_table, root->right, code, pos+1, code_index);
		}
		if (root->left) {
			code[pos] = '0';
			make_code_table(code_table, root->left, code, pos + 1, code_index);
		}
	}
}

void print_node(node_t * root) {
	if (root == NULL) {
		return;
	}
	if (root->symbol) {
		printf("%c\n", root->symbol);
	}
	print_node(root->right);
	print_node(root->left);
}

node_t * connect_node(node_t * node1, node_t * node2) {
	node_t * res_node = (node_t *)malloc(sizeof(node_t));
	node_t *n1 = (node_t *)malloc(sizeof(node_t));
	node_t *n2 = (node_t *)malloc(sizeof(node_t));
	memcpy(n1, node1, sizeof(node_t));
	memcpy(n2, node2, sizeof(node_t));
	res_node->right = n1;
	res_node->left = n2;
	res_node->frequency = n1->frequency + n2->frequency;
	res_node->symbol = 0;
	return res_node;
}

node_t * make_node_arr(int * frequency_table, int number_of_unique_symblols, const int ALPHABET_SIZE) {
	node_t * arr = (node_t *)malloc(sizeof(node_t) * number_of_unique_symblols);
	int i = 0;
	int j = 0;
	node_t node;
	for (i = 0; i < ALPHABET_SIZE; ++i) {
		if (frequency_table[i]) {
			node.frequency = frequency_table[i];
			node.symbol = i;
			node.left = NULL;
			node.right = NULL;
			arr[j++] = node;
		}
	}
	return arr;
}

int change_frequency(int * frequency_table, uchar * buffer, int size, const int ALPHABET_SIZE) {
	int i = 0;
	int unique_symbols = 0;
	for (i = 0; i < size; ++i) {
		if (buffer[i] < 0 || buffer[i] >= ALPHABET_SIZE) {
			error("Wrong symbol", 0);
		}
		if (frequency_table[buffer[i]] == 0) {
			unique_symbols++;
		}
		frequency_table[buffer[i]]++;
	}
	return unique_symbols;
}

void error(char * err_msg, int err_code) {
	printf("%s\n", err_msg);
	exit(err_code);
}
