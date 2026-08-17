#include<bits/stdc++.h>

using namespace std;

class Solution {
  public:
    void dfs_traversal(vector<vector<int>>&adj,int vertex,vector<int>&visited,unordered_map<int,int>&parent,bool &cycle){
        visited[vertex]=1;
        for(auto node:adj[vertex]){
            if(node==vertex){
                cycle=true;
                return;
            }
            else if(node!=parent[vertex]&&visited[node]==1){
                cycle=true;
                return;
            }
            else if(visited[node]==0){
                parent[node]=vertex;
                visited[node]=1;
                dfs_traversal(adj,node,visited,parent,cycle);
            }
        }
        
    }
    bool isCycle(int V, vector<vector<int>>& edges) {
        int e=edges.size();
        vector<vector<int>>adj(V);
        for(int i=0;i<e;i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        vector<int> visited(V,0);
        bool cycle=false;
        for(int i=0;i<V;i++){
        if(visited[i]==0){
        unordered_map<int,int>parent;
        parent[i]=-1;
        dfs_traversal(adj,i,visited,parent,cycle);
        }
        }
        return cycle;
    }
};