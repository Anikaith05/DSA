#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool isValid(vector<int>&arr,int capacity,int cows){
        int n=arr.size();
        int curr_cows=1;
        int last_placed_cow=arr[0];
        for(int i=1;i<n;i++){
            if(abs(arr[i]-last_placed_cow)>=capacity){
                curr_cows++;
                last_placed_cow=arr[i];
            }
        }
        return (curr_cows>=cows)?true:false;
    }
    int aggressiveCows(vector<int> &arr, int k) {
        int n=arr.size();
        sort(arr.begin(),arr.end());
        int min_n=INT_MAX,max_n=INT_MIN;
        for(int i=0;i<n;i++){
            min_n=min(min_n,arr[i]);
            max_n=max(max_n,arr[i]);
        }
        int low=1,high=(max_n-min_n);
        int ans=-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(isValid(arr,mid,k)){
                ans=mid;
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
        return ans;
    }
};