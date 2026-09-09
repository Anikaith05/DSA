#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int>trust_out(n,0);
        vector<int>trust_in(n,0);
        int t=trust.size();
        for(int i=0;i<t;i++){
            trust_in[trust[i][1]-1]++;
            trust_out[trust[i][0]-1]++;
        }
        for(int i=0;i<n;i++){
            if(trust_in[i]==n-1&&trust_out[i]==0){
                return i+1;
            }
        }
        return -1;
    }
};