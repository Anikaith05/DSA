#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n=nums.size();
        int i=0,j=n-1;
        while(i<=j){
            if(i==j){
                return nums[i];
            }
            int mid=(i+j)/2;
            if(mid%2==1){
                mid--;
            }
            if(nums[mid]==nums[mid+1]){
                i=mid+2;
            } 
            else{
                j=mid;
            }
        }
        return -1;
    }
};