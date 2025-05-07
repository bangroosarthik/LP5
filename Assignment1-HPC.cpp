#include<bits/stdc++.h>
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

class Graph{
  public:
  int v,e;
  unordered_map<int,vector<int>>adjList;
  
  Graph(){
      v=e=0;
      adjList.clear();
  }
  
  void input(){
      cout<<"Enter the number of vertices"<<endl;
      cin>>v;
      for(int i=0;i<v;i++){
          adjList[i]={};
      }
      
      cout<<"Enter the number of edges"<<endl;
      cin>>e;
      for(int i=0;i<e;i++){
          int src,dest;
          cout<<"Enter the src and dest node(0 based indexing)"<<endl;
          cin>>src>>dest;
          adjList[src].push_back(dest);
          adjList[dest].push_back(src);
      }
  }
  
  
  void display(){
      for(int i=0;i<v;i++){
          cout<<i<<" -> ";
          for(auto &neigh:adjList[i]){
              cout<<neigh<<" ";
          }
          cout<<endl;
      }
  }
  
  
  void SeqDFS(int s,vector<bool>&visited){
      stack<int>st;
      st.push(s);
      visited[s]=true;
      while(!st.empty()){
          int t=st.top();
          st.pop();
          cout<<t<<" ";
          
          for(auto &neigh:adjList[t]){
              if(!visited[neigh]){
                st.push(neigh);
                visited[neigh]=true;
              }
          }
      }
      
  }
  
  
  void SeqBFS(int s){
      queue<int>q;
      q.push(s);
      vector<bool>visited(v,false);
      visited[s]=true;
      while(!q.empty()){
          int f=q.front();
          q.pop();
          cout<<f<<" ";
          for(auto &neigh:adjList[f]){
              if(!visited[neigh]){
                  q.push(neigh);
                  visited[neigh]=true;
              }
          }
      }
  }
  
  
  void parallelDFS(int s,vector<bool>&visited1){
      stack<int>st;
      st.push(s);
      visited1[s]=true;
      while(!st.empty()){
          int t=st.top();
          st.pop();
          cout<<t<<" ";
          vector<int>neighbours=adjList[t];
          
          #pragma omp parallel for
          for(int i=0;i<neighbours.size();i++){
              int neigh=neighbours[i];
              if(!visited1[neigh]){
                  #pragma omp critical
                  if(!visited1[neigh]){
                      st.push(neigh);
                      visited1[neigh]=true;
                  }
              }
          }
      }
  }
  
  
  void parallelBFS(int s){
      vector<bool>visited2(v,false);
      queue<int>q;
      q.push(s);
      visited2[s]=true;
      while(!q.empty()){
          int size=q.size();
          vector<int>currentLevel;
          for(int i=0;i<size;i++){
              int f=q.front();
              q.pop();
              cout<<f<<" ";
              currentLevel.push_back(f);
          }
          
          #pragma omp parallel for 
          for(int i=0;i<currentLevel.size();i++){
              int neighbour=currentLevel[i];
              for(auto &neigh:adjList[neighbour]){
                  if(!visited2[neigh]){
                      #pragma omp critical
                      if(!visited2[neigh]){
                          q.push(neigh);
                          visited2[neigh]=true;
                      }
                  }
              }
          }
      }
     
  }
  
  void runDFS(int s){
      vector<bool>visited(v,false);
      vector<bool>visited1(v,false);
      auto start_time=high_resolution_clock::now();
      SeqDFS(s,visited);
      auto end_time = high_resolution_clock::now();
      duration<double>timeTaken= end_time-start_time;
      cout<<"Execution Time for SeqDFS: "<<timeTaken.count()<<" seconds"<<endl;
      
      auto start_time1=high_resolution_clock::now();
      parallelDFS(s,visited1);
      auto end_time1=high_resolution_clock::now();
      duration<double>timeTaken1=end_time1-start_time1;
      cout<<"Execution Time for Parallel DFS: "<<timeTaken1.count()<<" seconds"<<endl;
  }
  
  
  void runBFS(int s){
      auto start_time=high_resolution_clock::now();
      SeqBFS(s);
      auto end_time = high_resolution_clock::now();
      duration<double>timeTaken= end_time-start_time;
      cout<<"Execution Time for SeqBFS: "<<timeTaken.count()<<" seconds"<<endl;
      
      auto start_time1=high_resolution_clock::now();
      parallelBFS(s);
      auto end_time1=high_resolution_clock::now();
      duration<double>timeTaken1=end_time1-start_time1;
      cout<<"Execution Time for Parallel BFS: "<<timeTaken1.count()<<" seconds"<<endl;
  }
  
};

int main(){
    Graph obj;
    obj.input();
    obj.display();
    
    while(true){
        cout<<"Enter 1 to perform BFS"<<endl;
        cout<<"Enter 2 to perform DFS"<<endl;
        int ip;
        cin>>ip;
        if(ip==1){
            int s;
            cout<<"Enter source vertex"<<endl;
            cin>>s;
            obj.runBFS(s);
        }
        
        else if(ip==2){
            int s;
            cout<<"Enter source vertex"<<endl;
            cin>>s;
            obj.runDFS(s);
        }
        else{
            cout<<"invalid option"<<endl;
        }
    }
    
    return 0;
}