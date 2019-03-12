#include <stdio.h>

typedef struct matrix_s{
	int rows;
	int cols;
}matrix_size;


void error(char * error_msg){
	printf("%s", error_msg);
	exit(0);
}

void user_input(int * row1, int * row2, int *col1, int *col2){
	printf("Input rows number of first matrix: ");
	scanf("%d", row1);
	printf("Input columns number of first matrix: ");
	scanf("%d", col1);
	printf("Input rows number of second matrix: ");
	scanf("%d", row2);
	printf("Input columns number of second matrix: ");
	scanf("%d", col2);
}

void matrix_filling(int ** matrix, matrix_size size){
	int i = 0;
	int j = 0;
	for (i = 0; i < size.rows; ++i){
		matrix[i] = (int *)malloc(sizeof(int) * size.cols);
		for (j = 0; j < size.cols; ++j){
			printf("m[%d][%d] = ", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
}

void print_matrix(int ** matrix, matrix_size size){
	int i = 0;
	int j = 0;
	for (i = 0; i < size.rows; ++i){
		for (j = 0; j < size.cols; ++j)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

int **multiply_matrix(int **first_matrix, int **second_matrix, matrix_size first_size, matrix_size second_size){
	int **res = (int *)malloc(sizeof(int *) * first_size.rows);
	int i = 0;
	int j = 0;
	int k = 0;
	int elem = 0;
	for (i = 0; i < first_size.rows; ++i){
		res[i] = (int *)malloc(sizeof(int) * second_size.cols);
		for (j = 0; j < second_size.cols; ++j){
			for (k = 0; k < first_size.cols; ++k){
				elem += first_matrix[i][k] * second_matrix[k][j];
			}
			res[i][j] = elem;
			elem = 0;
		}
	}
	return res;
}

int main(){
	matrix_size m1_size;
	matrix_size m2_size;
	user_input(&m1_size.rows, &m2_size.rows, &m1_size.cols, &m2_size.cols);
	if (m1_size.cols != m2_size.rows){
		error("Multiply of this matrix impossible");
	}
	int *first_matrix = (int *)malloc(sizeof(int *) * m1_size.rows);
	int *second_matrix = (int *)malloc(sizeof(int *) * m2_size.rows);
	matrix_filling(first_matrix, m1_size);
	print_matrix(first_matrix, m1_size);
	matrix_filling(second_matrix, m2_size);
	print_matrix(second_matrix, m2_size);
	int ** res = multiply_matrix(first_matrix, second_matrix, m1_size, m2_size);
	matrix_size res_size = {m1_size.rows, m2_size.cols};
	print_matrix(res, res_size);
	return 0;
}