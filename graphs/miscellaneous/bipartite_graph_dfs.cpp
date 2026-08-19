#include<bits/stdc++.h>
usiung namespace std;

class Solution {
public:
    void dfs_traversal(vector<vector<int>>&graph,int vertex,vector<int>&color,bool &flag){
        for(auto node:graph[vertex]){
            if(color[node]==color[vertex]){
                flag=false;
                return;
            }
            else if(color[node]==0){
                if(color[vertex]==1) color[node]=2;
                if(color[vertex]==2) color[node]=1;
                dfs_traversal(graph,node,color,flag);
            }
        }
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int v=graph.size();
        vector<int>color(v,0);
        bool flag=true;
        for(int i=0;i<v;i++){
            if(color[i]==0){
                color[i]=1;
                dfs_traversal(graph,i,color,flag);
            }
        }
        return flag;
    }
};