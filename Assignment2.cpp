//Bubble Sort Merge Sort
#include<bits/stdc++.h>
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

void display(vector<int>&arr){
    int n=arr.size();
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void bubbleSort(vector<int>&arr){
    int n=arr.size();
    //rounds 
    auto start_time = high_resolution_clock::now();
    for(int i=1;i<n;i++){
        //comparison reduces
        for(int j=0;j<n-i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
    auto end_time = high_resolution_clock::now();
    duration<double> timetaken= end_time-start_time;
    cout<<"Execution time for sequential Bubble sort: "<<timetaken.count()<<" seconds"<<endl;
    display(arr);
}


void merge(vector<int>&arr,int low,int mid,int high){
    int left=low;
    int right=mid+1;
    vector<int>temp;
    while(left<=mid && right<=high){
        if(arr[left]<=arr[right]){
            temp.push_back(arr[left]);
            left++;
        }
        else{
            temp.push_back(arr[right]);
            right++;
        }
    }
    
    while(left<=mid){
        temp.push_back(arr[left]);
        left++;
    }
    
    while(right<=high){
        temp.push_back(arr[right]);
        right++;
    }
    
    for(int i=low;i<=high;i++){
        arr[i]=temp[i-low];
    }
}

void mergeSort(vector<int>&arr,int low,int high){
    
    if(low>=high) return;
    int mid=(low+high)/2;
    mergeSort(arr,low,mid);
    mergeSort(arr,mid+1,high);
    merge(arr,low,mid,high);
    
}


void parallelBubbleSort(vector<int>&arr){
    
    int n=arr.size();
    auto start_time = high_resolution_clock::now();
    for(int i=0;i<n;i++){
        if(i%2==0){
            #pragma omp parallel for 
            for(int j=0;j<n-1;j+=2){
                if(arr[j]>arr[j+1]){
                    swap(arr[j],arr[j+1]);
                }
            }
        }
        else{
            #pragma omp parallel for 
            for(int j=1;j<n-1;j+=2){
                if(arr[j]>arr[j+1]){
                    swap(arr[j],arr[j+1]);
                }
            }
        }
    }
    
    auto end_time= high_resolution_clock::now();
    duration<double>timetaken=end_time-start_time;
    cout<<"Execution time for parallel Bubble sort is: "<<timetaken.count()<<" seconds"<<endl;
    
    display(arr);
}

void parallelMergeSort(vector<int>&arr,int low,int high,int depth=0){
    
   
    if(low>=high) return;
    int mid=(low+high)/2;
    if(depth<=3){
        #pragma omp parallel sections
        {
            #pragma omp parallel section 
            parallelMergeSort(arr,low,mid,depth+1);
            
            #pragma omp parallel section
            parallelMergeSort(arr,mid+1,high,depth+1);
        }
    }
    else{
        mergeSort(arr,low,mid);
        mergeSort(arr,mid+1,high);
    }
    merge(arr,low,mid,high);
    
}

int main(){
    int N;
    cout<<"Enter the size of the array"<<endl;
    cin>>N;
    vector<int>arr(N);
    for(int i=0;i<N;i++){
        arr[i]=N-i;
        //worst case scenerio
    }
    vector<int>arr1=arr,arr2=arr,arr3=arr,arr4=arr;
    cout<<"input array"<<endl;
    display(arr);
    cout<<endl;
    while(true){
        cout<<"Enter 1 to perform bubble sort"<<endl;
        cout<<"Enter 2 to perform merge sort"<<endl;
        cout<<"Enter 3 to perform parallel bubble sort"<<endl;
        cout<<"Enter 4 to perform parallel merge sort"<<endl;
        int ip;
        cout<<"Enter the input"<<endl;
        cin>>ip;
        if(ip==1){
            
            bubbleSort(arr1);
            
        }
        else if(ip==2){
            auto start_time = high_resolution_clock::now();
            mergeSort(arr,0,arr.size()-1);
            auto end_time = high_resolution_clock::now();
            duration<double>timeTaken=end_time-start_time;
            cout<<"Execution time of sequential merge sort is : "<<timeTaken.count()<<" seconds"<<endl; 
            display(arr);
        }
        else if(ip==3){
            parallelBubbleSort(arr2);
        }
        
        else if(ip==4){
            auto start_time=high_resolution_clock::now();
            parallelMergeSort(arr4,0,arr4.size()-1);
            auto end_time = high_resolution_clock::now();
            duration<double>timeTaken2= end_time-start_time;
            cout<<"Time Taken by Parallel Merge sort is: "<<timeTaken2.count()<<" seconds"<<endl;
            display(arr4);
        }
    }
    
}