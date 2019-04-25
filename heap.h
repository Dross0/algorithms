#pragma once


enum heap_type {
	MIN_HEAP,
	MAX_HEAP
};

typedef unsigned char uchar;

typedef struct node_t {
	uchar symbol;
	int frequency;
	struct node_t * left;
	struct node_t * right;
}node_t;

typedef node_t T;

typedef struct heap_t {
	T *data;
	int size;
	enum heap_type type;
}heap_t;

int get_size(T * arr);
void swap(T * a, T * b);
void shift_down(heap_t * heap, int index);
void shift_up(heap_t * heap, int index);
heap_t * build_heap(T * arr, int size, int type);
void add_to_heap(heap_t * heap, T element);
T extract(heap_t * heap);



