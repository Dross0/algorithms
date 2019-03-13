from random import randint

def is_prime_ferma(p, test_amount = 1):
	for _ in range(test_amount):
		a = randint(2, p-1)
		if (a ** (p-1)) % p != 1:
			return False
	return True

def main():
	number = int(input("Введите число для проверки: "))
	test_amount = int(input("Введите количество тестов: "))
	if is_prime_ferma(number, test_amount):
		print("Число {}-простое".format(number))
	else:
		print("Число {}-составное".format(number))

if __name__ == '__main__':
	main()
