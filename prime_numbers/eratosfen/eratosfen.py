def eratosfen(n):
	arr = list(range(n + 1))
	for i in range(2, len(arr)):
		if arr[i]:
			print(arr[i])
			for j in range(arr[i], len(arr), arr[i]):
				arr[j] = 0


