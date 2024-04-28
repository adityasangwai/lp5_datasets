#include <bits/stdc++.h>
#include<omp.h>
using namespace std;

void merge(int arr[], int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1];
    int right[n2];

    for(int i = 0; i < n1;i++)
    {
        left[i] = arr[low+i];
    }

    for(int j = 0; j < n2; j++)
    {
        right[j] = arr[mid+1+j];
    }

    int i = 0, j = 0, k = low;
    while(i < n1 && j < n2)
    {
        if(left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while(i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while(j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void sequentialMergeSort(int arr[], int low, int high)
{
    if(low < high){
        int mid = (low+high)/2;
        sequentialMergeSort(arr, low, mid);
        sequentialMergeSort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}

void parallelMergeSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int mid = (low+high)/2;

        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section
            {
              parallelMergeSort(arr, low, mid);
            }
            #pragma omp section
            {
                parallelMergeSort(arr, mid+1,high);
            }
        }
        merge(arr, low, mid, high);
    }
}

void sequentialBubbleSort(int arr[], int n)
{
    for(int i = 0; i < n-1;i++)
    {
        for(int j  = 0; j < n-i-1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void parallelBubbleSort(int arr[], int n)
{
    for(int i = 0; i < n;++i)
    {
        //Sort odd indexed numbers
        #pragma omp for
        for(int j =1 ; j < n; j+=2)
        {
            if(arr[j-1] > arr[j]) 
            {
                swap(arr[j-1],arr[j]);
            }
        }

         //synchronize
        #pragma omp barrier

        //Sort even indexed numbers
        #pragma omp for
        for(int j = 2; j < n ; j+=2)
        {
            if(arr[j-1] > arr[j])
            {
                swap(arr[j-1],arr[j]);
            }

        }
    }
}

void printArray(int arr[], int n)
{
    for(int i = 0; i < n;i++)
    {
       cout<<arr[i]<<" ";
    }
}

int main()
{
    int n = 1000;
    int arr[n];
    double startTime,endTime;
    // Create an array with numbers starting from n to 1.
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
    startTime = omp_get_wtime();
    sequentialMergeSort(arr,0,n-1);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by sequential merge sort : "<<endTime-startTime<<" seconds"<<endl;

    // Reset the array
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;

    startTime = omp_get_wtime();
    parallelMergeSort(arr,0,n-1);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by parallel merge sort : "<<endTime-startTime<<" seconds"<<endl;


    // Reset the array
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;

    startTime = omp_get_wtime();
    sequentialBubbleSort(arr,n);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by sequential bubble sort : "<<endTime-startTime<<" seconds"<<endl;

    // Reset the array
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;

    startTime = omp_get_wtime();
    parallelBubbleSort(arr,n);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by parallel bubble sort : "<<endTime-startTime<<" seconds"<<endl;
    return 0;
}

/*
Sequential Merge Sort: Efficient divide-and-conquer algorithm with O(nlogn) time complexity and O(n) space complexity.
Parallel Merge Sort: Can achieve lower time complexity (as low as O(logn⋅logn)) with sufficient processors, and similar O(n) space complexity.
Sequential Bubble Sort: Inefficient sorting algorithm with O(n^2) time complexity and O(1) space complexity.
Parallel Bubble Sort: Time complexity typically remains O(n^2) but may improve slightly with parallelization; space complexity is similar to sequential at 
O(1).
*/