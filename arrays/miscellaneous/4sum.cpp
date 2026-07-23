#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n=nums.size();
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        for(int i=0;i<n-3;i++){
            if(i!=0&&nums[i]==nums[i-1]){
                continue;
            }
            for(int j=i+1;j<n-2;j++){
                if(j!=i+1&&nums[j]==nums[j-1]){
                    continue;
                }
                int l=j+1,m=n-1;
                while(l<m){
                    long long sum=1LL*nums[i]+nums[j]+nums[l]+nums[m];
                    if(sum==1LL*target){
                        ans.push_back({nums[i],nums[j],nums[l],nums[m]});
                        l++;
                        m--;
                        while(l<m&&nums[l]==nums[l-1]){
                            l++;
                        }
                        while(l<m&&nums[m]==nums[m+1]){
                            m--;
                        }
                    }
                    else if(sum<1LL*target){
                        l++;
                    }
                    else{
                        m--;
                    }
                }
            }
        }
        return ans;
    }
};