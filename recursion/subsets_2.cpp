#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void calc_subsets(vector<int>&nums,vector<vector<int>>&ans,vector<int>buffer,int i){
        if(i==nums.size()){
            sort(buffer.begin(),buffer.end());
            ans.push_back(buffer);
            return;
        }

        calc_subsets(nums,ans,buffer,i+1);
        buffer.push_back(nums[i]);
        calc_subsets(nums,ans,buffer,i+1);
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>>ans;
        vector<int>buffer;
        calc_subsets(nums,ans,buffer,0);

        set<vector<int>>st(ans.begin(),ans.end());
        vector<vector<int>>answer(st.begin(),st.end());
        return answer;
    }
};