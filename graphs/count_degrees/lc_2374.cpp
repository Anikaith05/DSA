#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int edgeScore(vector<int>& edges) {
        int n=edges.size();
        vector<long long>scores(n,0);
        for(int i=0;i<n;i++){
            scores[edges[i]]+=i;
        }
        long long max_s=0;
        int maxi=0;
        for(int i=0;i<n;i++){
            if(scores[i]>max_s){
                max_s=scores[i];
                maxi=i;
            }
        }
        return maxi;
    }
};