#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n=nums.size();
        int msum=INT_MIN;
        int sum=0;
        for(int i=0;i<n;i++){
            sum=max(nums[i],nums[i]+sum);
            if(sum>msum){
                msum=sum;
            }
        }
        return msum;
    }
};