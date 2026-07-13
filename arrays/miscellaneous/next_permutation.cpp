#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n=nums.size();
        int j=n-2;
        int b=-1;
        while(j>=0){
            if(nums[j]<nums[j+1]){
                b=j;
                break;
            }
            j--;
        }
        if(b==-1){
            reverse(nums.begin(),nums.end());
            return;
        }

        int i=n-1;
        while(nums[i]<=nums[b]){
            i--;
        }
        swap(nums[b],nums[i]);
        reverse(nums.begin()+b+1,nums.end());
    }
};