#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        // Code here
        int e=edges.size();
        vector<int>distances(V,1e8);
        distances[src]=0;
        for(int i=0;i<=V;i++){
            for(int j=0;j<e;j++){
                if(distances[edges[j][0]]==1e8){
                    continue;
                }
                if(distances[edges[j][0]]+edges[j][2]<distances[edges[j][1]]){
                    if(i==V){
                        return {-1};
                    }
                    distances[edges[j][1]]=distances[edges[j][0]]+edges[j][2];
                }
            }
        }
        return distances;
    }
};
