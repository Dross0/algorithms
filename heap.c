#include "heap.h"



int get_size(T * arr) {
	return sizeof(arr) / sizeof(T);
}

void swap(T * a, T * b) {
	T temp = *a;
	*a = *b;
	*b = temp;
}

void shift_down(heap_t * heap, int index) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int new_index = index;
	if (heap->type) {
		if (left < heap->size && heap->data[left].frequency > heap->data[index].frequency) {
			new_index = left;
		}
		if (right < heap->size && heap->data[right].frequency > heap->data[index].frequency) {
			new_index = right;
		}
	}
	else {
		if (left < heap->size && heap->data[left].frequency < heap->data[index].frequency) {
			new_index = left;
		}
		if (right < heap->size && heap->data[right].frequency < heap->data[new_index].frequency) {
			new_index = right;
		}
	}
	if (index != new_index) {
		swap(&heap->data[index], &heap->data[new_index]);
		shift_down(heap, new_index);
	}
}


void shift_up(heap_t * heap, int index) {
	int parent = 0;
	while (index > 0) {
		parent = (index - 1) / 2;
		if ((heap->type && heap->data[index].frequency <= heap->data[parent].frequency) ||
			(!heap->type &&  heap->data[index].frequency >= heap->data[parent].frequency)) {
			return;
		}
		swap(&heap->data[index], &heap->data[parent]);
		index = parent;
	}
}


heap_t * build_heap(T * arr, int size, int type) {
	heap_t * heap = (heap_t *)malloc(sizeof(heap_t));
	heap->data = arr;
	heap->size = size;
	heap->type = type;
	int i = 0;
	for (i = size / 2 - 1; i >= 0; --i) {
		shift_down(heap, i);
	}
	return heap;
}


void add_to_heap(heap_t * heap, T element) {
	//int max_heap_size = get_size(heap->data);
	//if (heap->size >= max_heap_size) {
	//	exit(1);
	//}
	heap->data[heap->size++] = element;
	shift_up(heap, heap->size - 1);
}

T extract(heap_t * heap) {
	if (heap->size <= 0) {
		exit(2);
	}
	T res = heap->data[0];
	heap->data[0] = heap->data[--heap->size];
	if (heap->size != 0) {
		shift_down(heap, 0);
	}
	return res;
}