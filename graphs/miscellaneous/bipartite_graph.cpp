#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int v=graph.size();
        vector<int>color(v,0);
        for(int i=0;i<v;i++){
            if(color[i]==0){
                queue<int>q;
                q.push(i);
                color[i]=1;
                while(!q.empty()){
                    int vertex=q.front();
                    q.pop();
                    for(auto node:graph[vertex]){
                        if(color[node]==color[vertex]){
                            return false;
                        }
                        else if(color[node]==0){
                            q.push(node);
                            if(color[vertex]==1) color[node]=2;
                            if(color[vertex]==2) color[node]=1;
                        }
                    }
                }
            }
        }
        return true;
    }
};