#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> topoSort(int V, vector<vector<int>>& edges) {
        int e=edges.size();
        vector<vector<int>>adj(V);
        vector<int> indegree(V,0);
        for(int i=0;i<e;i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            indegree[edges[i][1]]++;
        }
        int start=-1;

        queue<int>q;
        vector<int>sorted;
        vector<int>visited(V,0);
        for(int i=0;i<V;i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int v=q.front();
            q.pop();
            visited[v]=1;
            sorted.push_back(v);
            for(auto node:adj[v]){
                indegree[node]--;
                if(indegree[node]==0&&visited[node]==0){
                    q.push(node);
                    visited[node]=1;
                }
            }
        }
        return sorted;
        
    }
};