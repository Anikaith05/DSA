#include<bits/stdc++.h>
using namespace std;

class Compare{
    public:
    vector<int>&degree;
    Compare(vector<int>&degree):degree(degree){}
    bool operator()(const int&a,const int&b){
        if(degree[a]==degree[b]){
            return a>b;
        }
        return degree[a]<degree[b];
    }
};
class Solution {
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        vector<int>degree(n,0);
        int r=roads.size();
        for(int i=0;i<r;i++){
            degree[roads[i][0]]++;
            degree[roads[i][1]]++;
        }
        unordered_map<int,int>rank;
        vector<int>sorted_nodes(n,0);
        for(int i=0;i<n;i++){
            sorted_nodes[i]=i;
        }
        sort(sorted_nodes.begin(),sorted_nodes.end(),Compare(degree));
        for(int i=0;i<n;i++){
            rank[sorted_nodes[i]]=i+1;
        }
        long long total=0;
        for(int i=0;i<r;i++){
            total+=rank[roads[i][0]]*1LL+rank[roads[i][1]]*1LL;
        }
        return total;
    }
};