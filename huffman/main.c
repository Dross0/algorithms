#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

enum mode {
	COMPRESSION = 'c',
	DECOMPRESSION = 'd'
};

typedef struct pair_t {
	uchar symbol;
	uchar *code;
}pair_t;

typedef struct tree_node_t{
	uchar symbol;
	struct tree_node_t * right, *left;
}tree_node_t;

void error(char * err_msg, int err_code);
node_t * make_node_arr(int * frequency_table, int number_of_unique_symbols, const int ALPHABET_SIZE);
int change_frequency(int * frequency_table, uchar * buffer, int size, const int ALPHABET_SIZE);
void print_node(node_t * root);
node_t * connect_node(node_t * node1, node_t * node2);
void make_code_table(pair_t * code_table, node_t * root, uchar *code, int pos, int * i);
uchar * get_symbol_code(const pair_t * code_table, const size_t code_table_size, const uchar symbol);
int power(int a, int n);
uchar convert_binary_to_int(const uchar * byte);
int insert_in_str(uchar * dest, uchar * source, const int count, const int pos);
int coding(const pair_t * code_table, const size_t code_table_size, uchar * res_str, const uchar * buffer, const int size, 
			uchar * byte, const int b_index, int * res_str_index);
void make_compression(const pair_t * code_table, const size_t code_table_size, FILE * in, const int file_size);
void save_file_info(const pair_t * code_table, const size_t code_table_size, const int file_size, FILE * out);
void decompression(FILE * in);
void compression(FILE * in);
void get_code_table_from_file(pair_t * code_table, const code_table_size, FILE * in);
void make_byte_str(uchar * byte_str, uchar * buffer, const int size);
int decoding(tree_node_t * code_tree, uchar * buffer, const int size, const int file_size, int real_file_size, FILE * out);
uchar * dec_to_binary(uchar symbol);
tree_node_t * make_tree(pair_t * code_table, const int code_table_size);
tree_node_t * create_node(const int symbol, tree_node_t * right, tree_node_t * left);


int main(){
	FILE * in = fopen("huffman\\out.txt", "rb");
	if (in == NULL) {
		error("Cant open input file", 0);
	}
	char mode = 0;
	//fscanf(in, "%c\n", &mode);
	//compression(in);
	decompression(in);
	/*if (mode == COMPRESSION){
		compression(in);
	}
	else if (mode == DECOMPRESSION){
		decompression(in);
	}
	else{
		error("Wrong mode", 3);
	}*/
	return 0;
}

void compression(FILE * in){
	const int BUFFER_SIZE = 1000;
	const int ALPHABET_SIZE =  256;
	uchar * buffer = (uchar *)calloc(BUFFER_SIZE, sizeof(uchar));
	int * frequency_table = (int *)calloc(ALPHABET_SIZE, sizeof(int));
	int size = 0;
	int number_of_unique_symbols = 0;
	int file_size = 0;
	while ((size = fread(buffer, sizeof(char), BUFFER_SIZE, in))) {
		number_of_unique_symbols += change_frequency(frequency_table, buffer, size, ALPHABET_SIZE);
		file_size += size;
	}
	printf("--%d %d--\n\n", number_of_unique_symbols, file_size);
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
	uchar c[100] = { 0 };
	int code_index = 0;
	make_code_table(code_table, &tree, c, 0, &code_index);
	for (int i = 0; i < number_of_unique_symbols; ++i){
		printf("sym %c - code %s\n", code_table[i].symbol, code_table[i].code);
	}
	make_compression(code_table, number_of_unique_symbols, in, file_size);
}

void decompression(FILE * in){
	const int ALPHABET_SIZE =  256;
	const int BUFFER_SIZE = 2; //исправить: размер буффера имеет значение (остаток в байт строке пропадает когда снова вызывается decodinng)
	int file_size = 0;
	int code_table_size = 0;
	fread(&file_size, sizeof(int), 1, in);
	fread(&code_table_size, sizeof(int), 1, in);
	printf("%d %d\n", file_size, code_table_size);
	pair_t * code_table = (pair_t *)malloc(sizeof(pair_t) * code_table_size);
	get_code_table_from_file(code_table, code_table_size, in);
	for (int i = 0; i < code_table_size; ++i){
		printf("%c == %s\n", code_table[i].symbol, code_table[i].code);
	}
	tree_node_t * code_tree = make_tree(code_table, code_table_size);
	FILE * out = fopen("dec_out.txt", "w");
	if (out == NULL){
		error("Cant open output file", 3);
	}
	uchar * buffer = (uchar *)calloc(BUFFER_SIZE + 1, sizeof(uchar));
	int size = 0;
	int real_file_size = 0;
	while ((size = fread(buffer, sizeof(uchar), BUFFER_SIZE, in))){
		real_file_size = decoding(code_tree, buffer, size, file_size, real_file_size, out);
	}
}

tree_node_t * make_tree(pair_t * code_table, const int code_table_size){
	tree_node_t * root = create_node(0, 0, 0);
	tree_node_t * cur = (tree_node_t *)malloc(sizeof(tree_node_t));
	cur = root;
	int size = 0;
	for (int i = 0; i < code_table_size; ++i){
		cur = root;
		size = strlen(code_table[i].code);
		for (int j = 0; j < size; ++j){
			if (code_table[i].code[j] == '0'){
				if (cur->left == NULL){
					cur->left = create_node(0, 0, 0);
				}
				if (j == (size - 1)){
					cur->left->symbol = code_table[i].symbol;
				}
				cur = cur->left;
			}
			else if (code_table[i].code[j] == '1'){
				if (cur->right == NULL){
					cur->right = create_node(0,0,0);
				}
				if (j == (size - 1)){
					cur->right->symbol = code_table[i].symbol;
				}
				cur = cur->right;
			}
		}

	}
	return root;
}

tree_node_t * create_node(const int symbol, tree_node_t * right, tree_node_t * left){
	tree_node_t * tmp = (tree_node_t *)malloc(sizeof(tree_node_t));
	tmp->symbol = symbol;
	tmp->right = right;
	tmp->left = left;
	return tmp;
}

int decoding(tree_node_t * code_tree, uchar * buffer, const int size, const int file_size, int real_file_size, FILE * out){
	int byte_str_size = size * 8;
	uchar * byte_str = (uchar *)calloc(byte_str_size + 1, sizeof(uchar));
	uchar * res_str = (uchar *)malloc(sizeof(uchar) * (file_size + 1));
	int res_str_index = 0;
	make_byte_str(byte_str, buffer, size);
	printf("byte = %s\n", byte_str);
	tree_node_t * cur = (tree_node_t *)malloc(sizeof(tree_node_t));
	cur = code_tree;
	for (int i = 0; i < byte_str_size && real_file_size < file_size; ++i){
		if (byte_str[i] == '0'){
			cur = cur->left;
		}
		else if (byte_str[i] == '1'){
			cur = cur->right;
		}
		if (cur->symbol != 0){
			res_str[res_str_index++] = cur->symbol;
			real_file_size++;
			cur = code_tree;
		}
	}
	fwrite(res_str, sizeof(uchar), res_str_index, out);
	free(res_str);
	free(byte_str);
	return real_file_size;
}

void make_byte_str(uchar * byte_str, uchar * buffer, const int size){
	int pos = 0;
	for (int i = 0; i < size; ++i){
		uchar * byte = dec_to_binary(buffer[i]);
		pos = insert_in_str(byte_str, byte, 8, pos);
		free(byte);
	}
}

uchar * dec_to_binary(uchar symbol){
	const int BYTE_SIZE = 8;
	uchar * byte = (uchar *)calloc(BYTE_SIZE + 1, sizeof(uchar));
	int i = 0;
	while (i < 8){
		byte[i++] = (symbol % 2) + '0';
		symbol /= 2;
	}
	reverse(byte, BYTE_SIZE);
	return byte;
}

void reverse(uchar * str, const int size){
	uchar tmp = 0;
	for (int i = 0; i < size / 2; ++i){
		tmp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = tmp;
	}
}

void get_code_table_from_file(pair_t * code_table, const code_table_size, FILE * in) {
	uchar symbol = 0;
	pair_t pair;
	uchar ch = 0;
	int code_index = 0;
	fread(&(pair.symbol), sizeof(uchar), 1, in);	
	for (int i = 0; i < code_table_size; ++i){
		uchar * code = (uchar *)calloc(16, sizeof(uchar));
		fread(&ch, sizeof(uchar), 1, in);
		while (ch == '1' || ch == '0'){
			code[code_index++] = ch;
			fread(&ch, sizeof(uchar), 1, in);
		}
		pair.code = code;
		code_index = 0;
		code_table[i] = pair;
		pair.symbol = ch;
	}
	fseek(in, -1, SEEK_CUR);
}

void make_compression(const pair_t * code_table, const size_t code_table_size, FILE * in, const int file_size) {
	const int BYTE_SIZE = 8;
	const int BUFFER_SIZE = 1000;
	fseek(in, 3, SEEK_SET);
	uchar * res_str = (uchar *)calloc(BUFFER_SIZE + 1, sizeof(uchar));
	uchar * buffer = (uchar *)calloc(BUFFER_SIZE + 1, sizeof(uchar));
	uchar * byte = (uchar *)calloc(BYTE_SIZE + 1, sizeof(uchar));
	FILE * out = fopen("out.txt", "wb");
	if (out == NULL){
		error("Cant open output file", 1);
	}
	save_file_info(code_table, code_table_size, file_size, out);
	int byte_index = 0;
	int size = 0;
	int res_str_index = 0;
	while ((size = fread(buffer, sizeof(uchar), BUFFER_SIZE, in))) {
		byte_index = coding(code_table, code_table_size, res_str, buffer, size, byte, byte_index, &res_str_index);
		fwrite(res_str, sizeof(uchar), res_str_index, out);
		if (size < BUFFER_SIZE){
			byte_fill(byte, byte_index, BYTE_SIZE);
			uchar sym = convert_binary_to_int(byte);
			fwrite(&sym, sizeof(uchar), 1, out);
		}
		memset(res_str, 0, sizeof(uchar) * res_str_index);		
	}
	fclose(out);
}

void save_file_info(const pair_t * code_table, const size_t code_table_size, const int file_size, FILE * out){
	fwrite(&file_size, sizeof(int), 1, out);
	fwrite(&code_table_size, sizeof(int), 1, out);
	uchar code = 0;
	for (int i = 0; i < code_table_size; ++i){
		fwrite(&(code_table[i].symbol), sizeof(uchar), 1, out);			
		fwrite(code_table[i].code, sizeof(uchar), strlen(code_table[i].code), out);
	}
}

void byte_fill(uchar * byte, const int byte_index, const int BYTE_SIZE){
	int b_ind = byte_index;
	for (b_ind; b_ind < BYTE_SIZE; ++b_ind){
		byte[b_ind] = '0';
	}
}


int coding(const pair_t * code_table, const size_t code_table_size, uchar * res_str, const uchar * buffer, const int size, 
			uchar * byte, const int b_index, int * res_str_index) {
	const int BYTE_SIZE = 8;
	int byte_index = b_index;
	uchar * symbol_code = 0;
	int code_size = 0;
	char res_symbol = 0;
	for (int i = 0; i < size; ++i) {
		symbol_code = get_symbol_code(code_table, code_table_size, buffer[i]);
		code_size = strlen(symbol_code);
		//printf("code = %s\n", symbol_code);
		if (code_size + byte_index <= BYTE_SIZE) { 																// maybe <
			byte_index = insert_in_str(byte, symbol_code, code_size, byte_index);
		}
		else {
			int count_to_save = code_size - (BYTE_SIZE - byte_index);
			byte_index = insert_in_str(byte, symbol_code, BYTE_SIZE - byte_index, byte_index);
			res_symbol = convert_binary_to_int(byte);
			//printf("%s == %c\n", byte, res_symbol);
			res_str[(*res_str_index)++] = res_symbol;
			memset(byte, 0, sizeof(char) * BYTE_SIZE);
			for (byte_index = 0; byte_index < count_to_save; ++byte_index){
				byte[byte_index] = symbol_code[code_size - count_to_save + byte_index];
			}
		}
	}
	return byte_index;
}

int insert_in_str(uchar * dest, uchar * source, const int count, const int pos) {
	int i = 0;
	int position = pos;
	while (i < count) {
		dest[position] = source[i++];
		position++;
	}
	return position;
}

uchar convert_binary_to_int(const uchar * byte) {
	uchar symbol = 0;
	int i = 0;
	int size = strlen(byte);
	for (i = 0; i < size; ++i) {
		if (byte[i] == '1') {
			symbol += power(2, size - 1 - i);
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


uchar * get_symbol_code(const pair_t * code_table, const size_t code_table_size, const uchar symbol) {
	int i = 0;
	for (i = 0; i < code_table_size; ++i) {
		if (code_table[i].symbol == symbol) {
			return code_table[i].code;
		}
	}
}

void make_code_table(pair_t * code_table, node_t * root, uchar *code, int pos, int * code_index) {
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
			code[pos] = '0';
			make_code_table(code_table, root->right, code, pos+1, code_index);
		}
		if (root->left) {
			code[pos] = '1';
			make_code_table(code_table, root->left, code, pos + 1, code_index);
		}
	}
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

node_t * make_node_arr(int * frequency_table, int number_of_unique_symbols, const int ALPHABET_SIZE) {
	node_t * arr = (node_t *)malloc(sizeof(node_t) * number_of_unique_symbols);
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
