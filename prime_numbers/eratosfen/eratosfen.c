#include <stdio.h>


void eratoshpen(const int n){
	int * arr = (int *)malloc(sizeof(int) * (n + 1));
	int i = 0;
	for (i = 0; i < n + 1; ++i)
		arr[i] = i;
	int p = 0;
	int j = 0;
	for (p = 2; p < n + 1; ++p){
		if (arr[p] != 0){
			printf("%d\n", arr[p]);
			for (j = 2 * p; j < n + 1; j += p)
				arr[j] = 0;
		}
	}
	free(arr);
}


int main(){
	int n = 0;
	scanf("%d", &n);
	eratoshpen(n);
	return 0;
}
