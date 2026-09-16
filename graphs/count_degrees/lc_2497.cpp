#include<bits/stdc++.h>
using namespace std;

class Compare{
public:
    vector<int>&vals;
    Compare(vector<int>&vals):vals(vals){}
    bool operator()(const int&a,const int&b){
        return vals[a]>vals[b];
    }
};
class Solution {
public:
    int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) {
        int v=vals.size();
        int e=edges.size();
        vector<vector<int>>adj(v);
        for(int i=0;i<e;i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        for(int i=0;i<v;i++){
            sort(adj[i].begin(),adj[i].end(),Compare(vals));
        }
        int maxs=INT_MIN;
        for(int i=0;i<v;i++){
            int curr_sum=vals[i];
            for(int j=0;j<k;j++){
                if(j>=adj[i].size()) break;
                if(vals[adj[i][j]]>0) curr_sum+=vals[adj[i][j]];
            }
            maxs=max(maxs,curr_sum);
        }
        return maxs;
    }
};