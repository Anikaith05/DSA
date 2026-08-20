#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void dfs_traversal(vector<vector<int>>&adj,int vertex,vector<int>&visited,vector<int>&order){
        visited[vertex]=1;
        for(auto node:adj[vertex]){
            if(visited[node]==0){
                dfs_traversal(adj,node,visited,order);
            }
        }
        order.push_back(vertex);
    }
    vector<int> topoSort(int V, vector<vector<int>>& edges) {
        int e=edges.size();
        vector<vector<int>>adj(V);
        for(int i=0;i<e;i++){
            adj[edges[i][0]].push_back(edges[i][1]);
        }
        vector<int>visited(V,0);
        vector<int>order;
        for(int i=0;i<V;i++){
        if(visited[i]==0){
        dfs_traversal(adj,i,visited,order);
        }
        }
        reverse(order.begin(),order.end());
        return order;
    }
};