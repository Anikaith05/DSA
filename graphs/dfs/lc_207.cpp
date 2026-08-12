#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
void dfs_traversal(vector<vector<int>>&adj,int vertex,vector<int>&visited,bool &cycle){
    visited[vertex]=1;
    for(int node=0;node<adj[0].size();node++){
    if(adj[vertex][node]==1){
        if(visited[node]==0){
            dfs_traversal(adj,node,visited,cycle);
        }
        else if(visited[node]==1){
            cycle=true;
            return;
        }
    }
    }
    visited[vertex]=2;
}
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n=prerequisites.size();
        if(n==1||numCourses==1||n==0){
            return true;
        }
        vector<vector<int>>adj(numCourses,vector<int>(numCourses,0));
        for(int i=0;i<n;i++){
            adj[prerequisites[i][0]][prerequisites[i][1]]=1;
        }
        vector<int>visited(numCourses,0);
        bool cycle=false;
        for(int i=0;i<numCourses;i++){
        if(visited[i]==0){
            dfs_traversal(adj,i,visited,cycle);
        }
    }
        return !cycle;
    }
};