

def binary_search(array, value):
	first = 0
	last = len(array) - 1
	while (first <= last):
		mid = (first + last) // 2
		if array[mid] == value:
			return True
		elif array[mid] > value:
			last = mid - 1
		else:
			first = mid + 1
	return False


def recursive_binary_search(array, value):
	if (len(array) == 0):
		return False
	mid = len(array) // 2
	if array[mid] == value:
		return True
	elif array[mid] > value:
		return recursive_binary_search(array[:mid], value)
	else:
		return recursive_binary_search(array[mid + 1:], value)
