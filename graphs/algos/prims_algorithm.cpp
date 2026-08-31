#include<bits/stdc++.h>
using namespace std;

class Compare{
    public:
    bool operator()(pair<int,int>a,pair<int,int>b){
        return a.second>b.second;
    }
};

class Solution {
  public:
    int spanningTree(int V, vector<vector<int>>& edges) {
        int e=edges.size();
        vector<int>visited(V,0);
        vector<vector<pair<int,int>>>adj(V);
        for(int i=0;i<e;i++){
            adj[edges[i][0]].push_back({edges[i][1],edges[i][2]});
            adj[edges[i][1]].push_back({edges[i][0],edges[i][2]});
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,Compare>pq;
        for(auto node:adj[0]){
            pq.push({node.first,node.second});
        }
        visited[0]=1;
        int weight=0;
        while(!pq.empty()){
            pair<int,int>vertex=pq.top();
            pq.pop();
            if(visited[vertex.first]){
                continue;
            }
            visited[vertex.first]=1;
            weight+=vertex.second;
            for(auto node:adj[vertex.first]){
                if(visited[node.first]==0){
                    pq.push(node);
                }
            }
        }
        return weight;
    }
};