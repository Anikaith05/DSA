#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        int e=edges.size();
        unordered_map<int,int>degrees;
        for(int i=0;i<e;i++){
            degrees[edges[i][0]]++;
            degrees[edges[i][1]]++;
        }
        int maxk=0,maxv=0;
        for(auto it:degrees){
            if(it.second>maxv){
                maxv=it.second;
                maxk=it.first;
            }
        }
        return
    }
};