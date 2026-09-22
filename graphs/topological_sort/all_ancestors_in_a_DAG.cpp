#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        int e=edges.size();
        vector<vector<int>>adj(n);
        vector<int>degree(n,0);
        for(int i=0;i<e;i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            degree[edges[i][1]]++;
        }
        vector<vector<int>>ancestors(n);
        queue<int>q;
        for(int i=0;i<n;i++){
            if(degree[i]==0){
                q.push(i);
            }
        }

        while(!q.empty()){
            int vertex=q.front();
            q.pop();

            for(auto node:adj[vertex]){
                degree[node]--;
                for(auto a:ancestors[vertex]){
                    if(find(ancestors[node].begin(),ancestors[node].end(),a)==ancestors[node].end()){
                    ancestors[node].push_back(a);
                    }
                }
                ancestors[node].push_back(vertex);
                sort(ancestors[node].begin(),ancestors[node].end());
                if(degree[node]==0){
                    q.push(node);
                }
            }
        }
    return ancestors;
    }
};