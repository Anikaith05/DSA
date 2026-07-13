#include<bits/stdc++.h>

using namespace std;

void sortColors(vector<int>& nums){
    int n=nums.size();
    int start=0,mid=0,high=n-1;
    while(mid<=high){
        if(nums[mid]==0){
            swap(nums[mid],nums[start]);
            start++;
            mid++;
        }
        else if(nums[mid]==1){
            mid++;
        }
        else{
            swap(nums[mid],nums[high]);
            high--;
        }
    }
}