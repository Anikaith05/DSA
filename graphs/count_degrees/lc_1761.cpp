#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        int e=edges.size();
        vector<vector<int>>adj(n+1,vector<int>(n+1,0));
        vector<int>degree(n+1,0);
        for(int i=0;i<e;i++){
            adj[edges[i][0]][edges[i][1]]=1;
            adj[edges[i][1]][edges[i][0]]=1;
            degree[edges[i][0]]++;
            degree[edges[i][1]]++;
        }

        int min_degree=INT_MAX;

        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                for(int k=j+1;k<=n;k++){
                    if(adj[i][j]&&adj[j][k]&&adj[k][i]){
                        min_degree=min(min_degree,degree[i]+degree[j]+degree[k]-6);
                    }
                }
            }
        }
        return (min_degree==INT_MAX)?-1:min_degree;
    }
};