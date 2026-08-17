#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool isCycle(int V, vector<vector<int>>& edges) {
        int e=edges.size();
        vector<vector<int>>adj(V);
        for(int i=0;i<e;i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        vector<int> visited(V,0);
        for(int i=0;i<V;i++){
            if(visited[i]==0){
            unordered_map<int,int>parent;
            parent[i]=-1;
            queue<int>q;
            q.push(i);
            visited[i]=1;
            while(!q.empty()){
                int v=q.front();
                q.pop();
                for(auto node:adj[v]){
                    if(node==v){
                        return true;
                    }
                    else if(node!=parent[v]&&visited[node]==1){
                        return true;
                    }
                    else if(visited[node]==0){
                        parent[node]=v;
                        q.push(node);
                        visited[node]=1;
                    }
                }
            }
            }
        }
        return false;
    }
};