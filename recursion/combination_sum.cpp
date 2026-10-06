#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void calc_combinations(vector<int>&candidates,vector<vector<int>>&answer,int target,int i,vector<int>buffer){
        if(target==0){
            sort(buffer.begin(),buffer.end());
            answer.push_back(buffer);
            return;
        }
        if(target<0||i>=candidates.size()) return;

        for(int j=i;j<candidates.size();j++){
            buffer.push_back(candidates[j]);
            calc_combinations(candidates,answer,target-candidates[j],j,buffer);
            buffer.pop_back();
        }

    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>>answer;
        vector<int>buffer;
        calc_combinations(candidates,answer,target,0,buffer);

        set<vector<int>> st(answer.begin(),answer.end());

        vector<vector<int>> ans(st.begin(),st.end());

        return ans;
    }
};