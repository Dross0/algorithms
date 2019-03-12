#include <stdio.h>

void swap(int * a, int * b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


void bubble_sort(int arr[], int n){
	int i = 0;
	int j = 0;
	for (i = 0; i < n; ++i){
		for (j = 0; j < n - i; ++j){
			if (arr[j] > arr[j + 1]){
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

int main(){
	int n = 0;
	scanf("%d", &n);
	int * arr = (int *)malloc(sizeof(int) * n);
	if (!arr)
		return 1;
	int i = 0;
	for (i = 0; i < n; ++i){
		scanf("%d", &arr[i]);
	}
	bubble_sort(arr, n);
	for (i = 0; i < n; ++i){
		printf("%d ", arr[i]);
	}
	return 0;
}