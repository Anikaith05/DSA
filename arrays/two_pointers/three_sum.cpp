#include<bits/stdc++.h>

using namespace as std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n=nums.size();
        vector<vector<int>> st;
        sort(nums.begin(),nums.end());
        for(int k=0;k<n-1;k++){
            if(k>0&&nums[k]==nums[k-1]){
                continue;
            }
            int i=k+1;
            int j=n-1;
            while(i<j){
                if((nums[i]+nums[j]==-nums[k])&&(i!=j&&i!=k&&j!=k)){
                    st.push_back({nums[i],nums[j],nums[k]});
                    i++;
                    j--;
                    while(i<j&&nums[i]==nums[i-1]){
                        i++;
                    }
                    while(i<j&&nums[j]==nums[j+1]){
                        j--;
                    }
                }
                else if(nums[i]+nums[j]<-nums[k]){
                    i++;
                }
                else{
                    j--;
                }
            }
        }
        return st;
    }
};