#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> mergeArrays(vector<vector<int>> &mat) {
        // Code here
        int n=mat.size();
        int m=mat[0].size();
        
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>pq;
        for(int i=0;i<n;i++){
            pq.push({mat[i][0],i,0});
        }
        vector<int>sorted;
        
        while(!pq.empty()){
            sorted.push_back(pq.top()[0]);
            vector<int>curr=pq.top();
            pq.pop();
            if(curr[2]+1<m){
            pq.push({mat[curr[1]][curr[2]+1],curr[1],curr[2]+1});
            }
        }
        
        return sorted;
    }
};