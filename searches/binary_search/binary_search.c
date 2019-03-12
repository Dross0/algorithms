int recursive_binary_search(int arr[], int start, int end, int value){
	if (start > end){
		return 0;
	}	
	int mid = (start + end) / 2;
	if (arr[mid] == value){
		return 1;
	}
	else if (arr[mid] > value){
		return recursive_binary_search(arr, start, mid-1, value);
	}
	else{
		return recursive_binary_search(arr, mid + 1, end, value);
	}
}

int binary_search(int arr[], int size, int value){
	int first = 0;
	int last = size;
	int mid = 0;
	while (first <= last){
		mid = (first + last) / 2;
		if (arr[mid] == value){
			return 1;
		}
		else if (arr[mid] > value){
			last = mid - 1; 
		}
		else{
			first = mid + 1;
		}
	}
	return 0;
}
