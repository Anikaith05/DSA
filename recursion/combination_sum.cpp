#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void calc_combinations(vector<vector<int>>&answer,vector<int>&candidates,int target,int i,vector<int>buffer,int sum){
        if(sum==target){
            answer.push_back(buffer);
            return;
        }
        if(i>=candidates.size()){
            return;
        }

        calc_combinations(answer,candidates,target,i+1,buffer,sum);
        for(int j=1;j*candidates[i]<=target-sum;j++){
            vector<int>sample(buffer.begin(),buffer.end());
            for(int k=0;k<j;k++){
                sample.push_back(candidates[i]);
            }
        calc_combinations(answer,candidates,target,i+1,sample,sum+j*candidates[i]);
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>>answer;

        vector<int>buffer;
        calc_combinations(answer,candidates,target,0,buffer,0);
        
        return answer;
    }
};