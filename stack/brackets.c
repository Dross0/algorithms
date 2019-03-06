#include <stdio.h>
#include "stack.h"
#include <string.h>

#define MAX_STR_SIZE 1000

int is_open_bracket(char c){
	return (c == '(' || c == '[' || c == '{');
}

int check_open_close_brackets(stack_t * stack, char c){
	return     (!is_empty(stack))
			&& ((c == ')' && top(stack) == '(')
			|| (c == ']' && top(stack) == '[')
			|| (c == '}' && top(stack) == '{'));
}

int check_brackets(char str[]){
	stack_t stack;
	stack.size = 0;
	stack.data = NULL;
	int i = 0;
	while (str[i]){
		if (is_open_bracket(str[i])){
			push(&stack, str[i]);
		}
		else{
			if (check_open_close_brackets(&stack, str[i]))
				pop(&stack);
			else
				return 0;
		}
		++i;
	}
	return is_empty(&stack);
}

int main(){
	char bracket_str[MAX_STR_SIZE] = {0};
	scanf("%s", bracket_str);
	int is_correct = check_brackets(bracket_str);
	if (is_correct){
		printf("Correct\n");
	}
	else{
		printf("Wrong\n");
	}
	return 0;
}