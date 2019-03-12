def qsort(arr, reverse=False):
	if len(arr) <= 1:
		return arr
	lower = []
	greater = []
	equal = []
	pivot = arr[len(arr) // 2]
	for i in range(len(arr)):
		if arr[i] == pivot:
			equal.append(pivot)
		elif arr[i] > pivot:
			greater.append(arr[i])
		else:
			lower.append(arr[i])
	if reverse:
		return qsort(greater, True) + equal + qsort(lower, True)
	return qsort(lower) + equal + qsort(greater)


