
def is_prime(number):
	if (number <= 1):
		return False
	divider = 1
	dividers_number = 0
	limit = int(number ** 0.5) + 1
	while divider <= limit:
		if number % divider == 0:
			dividers_number += 1
		if dividers_number > 2:
			return False
		divider += 1
	return True

def main():
	number = int(input("Введите число для проверки: "))
	print("Число {}-{}".format(number, "простое" if is_prime(number) else "составное"))

if __name__ == '__main__':
	main()
	
