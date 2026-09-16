#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) {
        vector<int>degrees(n,0);
        int e=edges.size();
        for(int i=0;i<e;i++){
            degrees[edges[i][1]]++;
        }
        int ans=-1;
        for(int i=0;i<n;i++){
            if(degrees[i]==0&&ans!=-1) return -1;
            if(degrees[i]==0){
                ans=i;
            }
        }
        return ans;
    }
};