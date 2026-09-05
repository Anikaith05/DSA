#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(int vertex,vector<int>&visited,vector<vector<int>>&adj,int &count){
        count++;
        visited[vertex]=1;
        for(auto node:adj[vertex]){
            if(visited[node]==0){
            dfs(node,visited,adj,count);
            }
        }
    }
    bool inrange(int i, int j, vector<vector<int>>& bombs) {
    long long dx = bombs[i][0] - bombs[j][0];
    long long dy = bombs[i][1] - bombs[j][1];

    return dx * dx + dy * dy <= 1LL * bombs[i][2] * bombs[i][2];
    }
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n=bombs.size();
        vector<vector<int>>adj(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j) continue;
                if(inrange(i,j,bombs)){
                    adj[i].push_back(j);
                }
            }
        }
        int max_count=0;
        for(int i=0;i<n;i++){
            vector<int>visited(n,0);
            int count=0;
            dfs(i,visited,adj,count);
            max_count=max(max_count,count);
        }
    return max_count;
    }
};