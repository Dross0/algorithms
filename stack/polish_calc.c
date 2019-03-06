#include <stdio.h>
#include <string.h>
#include "stack.h"
#include <ctype.h>

#define MAX_STR_SIZE 1000

int count(stack_t * stack, const char sign){
	int x = pop(stack);
	int y = pop(stack);
	if (sign == '+'){
		return x + y;
	}
	else if (sign == '*'){
		return x * y;
	}
	else if (sign == '-'){
		return y - x;
	}
	else if (sign == '/'){
		if (x == 0){
			printf("division by zero");
			exit(1);
		}
		return y / x;
	}
}

int calc(char polish_str[]){
	int i = 0;
	stack_t stack;
	stack.size = 0;
	stack.data = NULL;
	char str_number[MAX_STR_SIZE] = {0};
	int j = 0;
	int number = 0;
	int flag = 0;
	while (polish_str[i]){
		if (isdigit(polish_str[i])){
			str_number[j++] = polish_str[i];
			flag = 1;
		}
		else if (polish_str[i] == ' '){
			if (flag){
				number = atoi(str_number);
				memset(str_number, '\0', sizeof(char) * j);
				j = 0;
				push(&stack, number);
				flag = 0;
			}
		}
		else{
			push(&stack, count(&stack, polish_str[i]));
			flag = 0;
		}
		i++;					
	}
	return pop(&stack);
}

int main(){
	char polish_str[MAX_STR_SIZE] = {0};
	gets(polish_str);
	int result = calc(polish_str);
	printf("%d\n", result);
	return 0;
}