#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void calc(vector<vector<int>>&answer,vector<int>&nums,int i,vector<int>buffer,vector<int>visited){
        if(i==nums.size()){
            answer.push_back(buffer);
            return;
        }

        for(int j=0;j<nums.size();j++){
            if(visited[j]==1) continue;
            buffer.push_back(nums[j]);
            visited[j]=1;
            calc(answer,nums,i+1,buffer,visited);
            buffer.pop_back();
            visited[j]=0;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>answer;

        int n=nums.size();
        vector<int>buffer;
        vector<int>visited(n,0);
        calc(answer,nums,0,buffer,visited);

        return answer;

    }
};