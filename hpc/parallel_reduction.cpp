#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int minVal(int arr[], int n)
{
    int minVal = arr[0];
    for(int i = 1; i < n;i++)
    {
        if(arr[i] < minVal)
        {
            minVal = arr[i];
        }
    }
    
    return minVal;
}

int parallel_minVal(int arr[], int n)
{
    int minVal = arr[0];

    #pragma omp parallel for reduction(min : minVal)
    for(int i = 1; i < n;i++)
    {
        if(arr[i] < minVal)
        {
            minVal = arr[i];
        }
    }
    
    return minVal;
}

int maxVal(int arr[], int n)
{
    int maxVal = arr[0];
    for(int i = 1; i < n; i++)
    {
        if(arr[i] > maxVal)
        {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

int parallel_maxVal(int arr[], int n)
{
    int maxVal = arr[0];

    #pragma omp parallel for reduction(max : maxVal)
    for(int i = 1; i < n; i++)
    {
        if(arr[i] > maxVal)
        {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

int sum(int arr[], int n)
{
    int sum = 0;
    for(int i =0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int parallel_sum(int arr[], int n)
{
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for(int i =0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}
double average(int arr[],int n)
{
    return (double)sum(arr,n)/n;
}

double parallel_average(int arr[],int n)
{
    return (double)parallel_sum(arr,n)/n;
}

int main()
{
    // int n;
    // cout<<"Enter total number of elements : ";
    // cin>> n;
    // int arr[n];
    // for(int i = 0; i < n;i++)
    // {
    //     cout<<"\nEnter "<<i+1<<" element : ";
    //     cin>>arr[i];
    // }
    int n = 100;
    int arr[n];
    for(int i = 0; i < n;i++)
    {
        arr[i] = i+1;
    }
    double startTime,endTime;
    startTime = omp_get_wtime();
    cout<<"\nSequential min : "<<minVal(arr,n);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by sequential min : "<<endTime-startTime<<" seconds";
    startTime = omp_get_wtime();
    cout<<"\nParallel min : "<<parallel_minVal(arr,n);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by parallel min : "<<endTime-startTime<<" seconds";
    startTime = omp_get_wtime();
    cout<<"\nSequential max : "<<maxVal(arr,n);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by sequential max : "<<endTime-startTime<<" seconds";
    startTime = omp_get_wtime();
    cout<<"\nParallel max : "<<parallel_maxVal(arr,n);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by parallel max : "<<endTime-startTime<<" seconds";
    startTime = omp_get_wtime();
    cout<<"\nSequential sum : "<<sum(arr,n);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by sequential sum : "<<endTime-startTime<<" seconds";
    startTime = omp_get_wtime();
    cout<<"\nParallel sum : "<<parallel_sum(arr,n);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by parallel sum : "<<endTime-startTime<<" seconds";
    startTime = omp_get_wtime();
    cout<<"\nSequential average : "<<average(arr,n);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by sequential average : "<<endTime-startTime<<" seconds";
    startTime = omp_get_wtime();
    cout<<"\nParallel average : "<<parallel_average(arr,n);
    endTime = omp_get_wtime();
    cout<<"\nTime taken by parallel average : "<<endTime-startTime<<" seconds";
    return 0;
}

/*
Parallel Reduction : technique used to efficiently perform a reduction operation on a set of data across multiple processors or threads.
working:
1.Partitioning: The data is divided into chunks that are distributed across multiple processors or threads.
2.Local Reduction: Each processor or thread performs the reduction operation on its assigned chunk of data, resulting in a local reduced value.
3.Global Reduction: The local reduced values are then combined or reduced further in a hierarchical manner, often using a tree structure, until a single global reduced value is obtained.
*/