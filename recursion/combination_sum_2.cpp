#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void calc_combinations(vector<vector<int>>&answer,vector<int>&candidates,vector<int>buffer,int target,int i){
        if(target==0){
            sort(buffer.begin(),buffer.end());
            answer.push_back(buffer);
            return;
        }
        if(target<0||i>=(int)candidates.size()){
            return;
        }
        for(int j=i+1;j<candidates.size();j++){
            if(j>i+1&&candidates[j]==candidates[j-1]) continue;
            buffer.push_back(candidates[j]);
            calc_combinations(answer,candidates,buffer,target-candidates[j],j);
            buffer.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>>answer;

        vector<int>buffer;
        sort(candidates.begin(),candidates.end());
        calc_combinations(answer,candidates,buffer,target,-1);

        return answer;
    }
};