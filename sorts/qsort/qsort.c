#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int arr[], int first, int last)
{
    if (first < last)
    {
        int left = first;
        int right = last;
        int  middle = arr[(left + right) / 2];
        do
        {
            while (arr[left] < middle) left++;
            while (arr[right] > middle) right--;
            if (left <= right)
            {
                swap(&arr[right], &arr[left]);
                left++;
                right--;
            }
        } while (left <= right);
        quick_sort(arr, first, right);
        quick_sort(arr, left, last);
    }
}

int main(){
    int n = 0;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL)
        return 0;
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    quick_sort(arr, 0, n-1);
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    free(arr);
}