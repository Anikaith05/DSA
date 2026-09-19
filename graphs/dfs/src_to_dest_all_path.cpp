#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(int vertex,vector<vector<int>>&graph,vector<int>&ans,vector<vector<int>>&result,int n){
        ans.push_back(vertex);
        if(vertex==n-1){
            result.push_back(ans);
        }
        for(auto node:graph[vertex]){
            dfs(node,graph,ans,result,n);
        }
        ans.pop_back();
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<vector<int>>result;
        vector<int>ans;
        dfs(0,graph,ans,result,n);
        return result;
    }
};