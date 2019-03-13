def interpolation_search(arr, value):
	first = 0;
	last = len(arr) - 1
	while (arr[first] <= value and arr[last] >= value):
		mid = first + (((value - arr[first]) * (last - first)) // (arr[last] - arr[first]))
		if arr[mid] == value:
			return True
		elif arr[mid] > value:
			last = mid - 1
		else:
			first = mid + 1
		print(first, mid, last)
	return False
