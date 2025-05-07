//min max avg sum 
#include<bits/stdc++.h>
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

int main(){
    int N;
    cout<<"Enter the size of the array"<<endl;
    cin>>N;
    int *arr=new int[N];
    for(int i=0;i<N;i++){
        arr[i]=rand()%1000;
    }
    
    cout<<"Input array"<<endl;
    for(int i=0;i<N;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    
    int min_val=INT_MAX;
    int max_val=INT_MIN;
    int sum=0;
    double avg=0.0;
    
    auto start_time = high_resolution_clock::now();
    #pragma omp parallel for reduction(min:min_val)
    for(int i=0;i<N;i++){
        if(arr[i]<min_val){
            min_val=arr[i];
        }
    }
    
    #pragma omp parallel for reduction(max:max_val)
    for(int i=0;i<N;i++){
        if(arr[i]>max_val){
            max_val=arr[i];
        }
    }
    
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<N;i++){
        sum+=arr[i];
    }
    
    avg = double(sum)/N;
    
    auto end_time= high_resolution_clock::now();
    duration<double>timeTaken= end_time-start_time;
    
    
    
    
    auto start_time1=high_resolution_clock::now();
    for(int i=0;i<N;i++){
        if(arr[i]<min_val){
            min_val=arr[i];
        }
    }
    
    for(int i=0;i<N;i++){
        if(arr[i]>max_val){
            max_val=arr[i];
        }
    }
    
    for(int i=0;i<N;i++){
        sum+=arr[i];
    }
    
    avg = double(sum)/N;
    
    auto end_time1=high_resolution_clock::now();
    
    duration<double>timeTaken1=end_time1-start_time1;
    
    
    
    
    
    //output
    cout<<"Min value: "<<min_val<<endl;
    cout<<"Max Value: "<<max_val<<endl;
    cout<<"Sum: "<<sum<<endl;
    cout<<"Avg: "<<avg<<endl;
    cout<<"Execution time for Parallel algo's "<<timeTaken.count()<<" seconds"<<endl;
    
    cout<<"Execution time for Sequential algo's "<<timeTaken1.count()<<" seconds"<<endl;
    
    
    gcc -fopenmp filename.cpp -o minmaxsum
    ./minmaxsum
}