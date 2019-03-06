#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

T * new_array(int n){
	return (T *)malloc(sizeof(T) * n);
}

int * array_stock_span(int stocks[], int n){
	T * spans = new_array(n);
	int i = 0;
	int k = 0;
	for (i = 0; i < n; ++i){
		k = 1;
		while (i - k >= 0 && stocks[i-k] <= stocks[i])
			k++;
		spans[i] = k;
	}
	return spans;
}

int * stack_stock_span(int stocks[], int n){
	T * spans = new_array(n);
	stack_t s;
	s.size = 0;
	s.data = NULL;
	spans[0] = 1;
	push(&s, 0);
	int i = 0;
	for (i = 1; i < n; ++i){
		while (!is_empty(&s) && stocks[top(&s)] <= stocks[i])
			pop(&s);
		if (is_empty(&s))
			spans[i] = i + 1;
		else
			spans[i] = i - top(&s);
		push(&s, i);

	}
	remove_stack(&s);
	return spans;
}

int main(){
	T p[SIZE] = {0};
	srand(time(NULL));
	int i = 0;
	int type = 0;
	scanf("%d", &type);
	for (i = 0; i < SIZE; ++i){
		if (type)
			p[i] = i+1;
		else
			p[i] = rand() % 1000;
	}
	clock_t start = clock();
	T *array_stock = array_stock_span(p, SIZE);
	clock_t end = clock();
	free(array_stock);
	printf("Without stack (%s)= %.5f\n", (type) ? "sort": "random", (double)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	T *stack_stock = stack_stock_span(p, SIZE);
	end = clock();
	printf("With stack (%s)= %.5f\n", (type) ? "sort": "random",(double)(end - start) / CLOCKS_PER_SEC);
	free(stack_stock);
	return 0;
}