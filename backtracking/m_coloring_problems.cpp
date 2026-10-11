#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool isSafe(vector<vector<int>>&adj,vector<int>color,int i,int j){
        for(auto node:adj[i]){
            if(color[node]==j){
                return false;
            }
        }
        return true;
    }
    
    bool isPossible(vector<vector<int>>&adj,int v,int m,int i,vector<int>color){
        if(m==0||v>1&&m==1){
            return false;
        }
        if(i==v){
            return true;
        }
        
        bool curr=false;

        for(int j=0;j<m;j++){
            if(isSafe(adj,color,i,j)){
                color[i]=j;
                curr=curr||isPossible(adj,v,m,i+1,color);
                color[i]=-1;
            }
        }
         
        return curr;   
    }
    bool graphColoring(int v, vector<vector<int>> &edges, int m) {
        // code here
        int n=edges.size();
        vector<vector<int>>adj(v);
        for(int i=0;i<n;i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        
        
        vector<int>color(v,-1);
        return isPossible(adj,v,m,0,color);
    }
};