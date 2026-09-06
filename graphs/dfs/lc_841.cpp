#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(int vertex,vector<int>&visited,vector<vector<int>>&rooms,int &count){
        visited[vertex]=1;
        count++;
        for(auto node:rooms[vertex]){
            if(visited[node]==0){
                dfs(node,visited,rooms,count);
            }
        }
    }
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n=rooms.size();
        for(int i=0;i<n;i++){
            int count=0;
            vector<int>visited(n,0);
            dfs(i,visited,rooms,count);
            if(count==n){
                return true;
            }
        }
        return false;
    }
};