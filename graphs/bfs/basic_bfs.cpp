#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> bfs(vector<vector<int>> &adj) {
        // code here
        int n=adj.size();
        vector<int>visited(n,0);
        vector<int>ans;
        queue<int> q;
        q.push(0);
        while(!q.empty()){
            int vertex=q.front();
            q.pop();
            ans.push_back(vertex);
            visited[vertex]=1;
            for(auto node:adj[vertex]){
                if(visited[node]!=1){
                    visited[node]=1;
                        q.push(node);
                }
            }
        }
        return ans;
    }
};