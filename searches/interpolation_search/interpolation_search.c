int interpolation_search(int arr[], int n, int value){
	int first = 0;
	int last = n - 1;
	int mid = 0;
	while (arr[first] <= value && arr[last] >= value){
		mid = first + (((value - arr[first]) * (last - first)) / (arr[last] - arr[first]));
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
