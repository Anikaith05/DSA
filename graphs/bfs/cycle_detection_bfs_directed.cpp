#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool isCyclic(int V, vector<vector<int>> &edges) {
        // code here
        int e=edges.size();
        vector<vector<int>>adj(V);
        vector<int>indegree(V,0);
        for(int i=0;i<e;i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            indegree[edges[i][1]]++;
        }
        int count=0;
        queue<int> q;
        for(int i=0;i<V;i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }
            while(!q.empty()){
                int v=q.front();
                q.pop();
                count++;
                for(auto node:adj[v]){
                    indegree[node]--;
                    if(indegree[node]==0){
                        q.push(node);
                    }
                }
            }
        return !(count==V);
    }
};