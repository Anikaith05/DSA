#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        vector<int>degree(n,0);
        int r=roads.size();
        for(int i=0;i<r;i++){
            degree[roads[i][0]]++;
            degree[roads[i][1]]++;
        }

        vector<vector<int>>adj(n);
        for(int i=0;i<r;i++){
            adj[roads[i][0]].push_back(roads[i][1]);
            adj[roads[i][1]].push_back(roads[i][0]);
        }
        
        vector<vector<int>>ranks(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j){
                    ranks[i][j]=degree[i];
                    continue;
                }
                if(find(adj[i].begin(),adj[i].end(),j)!=adj[i].end()){
                    ranks[i][j]=degree[i]+degree[j]-1;
                }
                else{
                    ranks[i][j]=degree[i]+degree[j];
                }
            }
        }
        int maxn=INT_MIN;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                maxn=max(maxn,ranks[i][j]);
            }
        }
        return maxn;
    }
};