#include <stdio.h>
#include <math.h>

typedef unsigned long ulong;

int is_prime(ulong number){
	if (number <= 1){
		return 0;
	}
	ulong limit = (ulong)pow(number, 0.5) + 1;
	ulong divider = 1;
	unsigned int dividers_number = 0;
	while (divider <= limit){
		if (number % divider == 0){
			dividers_number++;
		}
		if (dividers_number > 2){
			return 0;
		}
		divider++;
	}
	return 1;
}

int main(){
	ulong number = 0;
	printf("Введите число для проверки: ");
	scanf("%ld", &number);
	if (is_prime(number)){
		printf("%ld-простое\n", number);
	}
	else{
		printf("%ld-составное\n", number);
	}
	return 0;
}
