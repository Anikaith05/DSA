#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(vector<int>&weights,int capacity,int days){
        int n=weights.size();
        int curr_weight=0;
        int curr_days=1;
        for(int i=0;i<n;i++){
            if(weights[i]>capacity){
                return false;
            }
            if(curr_weight+weights[i]<=capacity){
                curr_weight+=weights[i];
            }
            else{
                curr_days++;
                curr_weight=weights[i];
            }
        }
        return (curr_days<=days)?true:false;
    }
    int shipWithinDays(vector<int>& weights, int days) {
        int n=weights.size();
        if(days>n){
            return -1;
        }
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=weights[i];
        }
        int low=1,high=sum;
        int ans=-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(isValid(weights,mid,days)){
                high=mid-1;
                ans=mid;
            }
            else{
                low=mid+1;
            }
        }
        return ans;
    }
};
