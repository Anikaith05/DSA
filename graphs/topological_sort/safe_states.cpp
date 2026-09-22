#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<int>degree(n,0);
        vector<vector<int>>adj(n);
        for(int i=0;i<n;i++){
            for(auto node:graph[i]){
                adj[node].push_back(i);
                degree[i]++;
            }
        } 

        vector<int>answer;
        queue<int>q;
        for(int i=0;i<n;i++){
            if(degree[i]==0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int vertex=q.front();
            q.pop();
            answer.push_back(vertex);
            for(auto node:adj[vertex]){
                degree[node]--;
                if(degree[node]==0){
                    q.push(node);
                }
            }
        }
        sort(answer.begin(),answer.end());
        return answer;
    }
};