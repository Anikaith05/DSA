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
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        // Code here
        int e=edges.size();
        vector<int>distances(V,1e8);
        distances[src]=0;
        vector<vector<pair<int,int>>>adj(V);
        for(int e=0;e<edges.size();e++){
            adj[edges[e][0]].push_back({edges[e][1],edges[e][2]});
            adj[edges[e][1]].push_back({edges[e][0],edges[e][2]});
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,Compare>pq;
        for(auto it:adj[src]){
            pq.push(it);
            distances[it.first]=it.second;
        }
        while(!pq.empty()){
            pair<int,int>vertex=pq.top();
            pq.pop();
            if(vertex.second>distances[vertex.first]){
                continue;
            }
            for(auto node:adj[vertex.first]){
                if(distances[vertex.first]+node.second<distances[node.first]){
                    distances[node.first]=distances[vertex.first]+node.second;
                    pq.push({node.first,distances[node.first]});
                }
            }
        }
        return distances;
    }
};