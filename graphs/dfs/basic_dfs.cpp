#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void dfs_traversal(vector<vector<int>>& adj,int vertex,vector<int>&visited,vector<int>&vec){
        visited[vertex]=1;
        vec.push_back(vertex);
        for(auto node:adj[vertex]){
            if(visited[node]!=1){
                dfs_traversal(adj,node,visited);
            }
        }
    }
    vector<int> dfs(vector<vector<int>>& adj) {
        // Code here
        int n=adj.size();
        vector<int> visited(n+1,0);
        vector<int>vec;
        dfs_traversal(adj,0,visited,vec);
        return vec;
    }
};