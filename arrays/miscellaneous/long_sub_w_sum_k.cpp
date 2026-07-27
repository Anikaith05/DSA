#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int longestSubarray(vector<int>& arr, int k) {
        int n=arr.size();
        vector<int>sum_arr(n,0);
        sum_arr[0]=arr[0];
        for(int i=1;i<n;i++){
            sum_arr[i]=sum_arr[i-1]+arr[i];
        }
        int maxl=0;
        unordered_map<int,int> mp;
        mp[0]=-1;
        for(int i=0;i<n;i++){
            if(mp.find(sum_arr[i])==mp.end()){
                mp[sum_arr[i]]=i;
            }
            if(mp.find(sum_arr[i]-k)!=mp.end()){
                int j=mp[sum_arr[i]-k];
                maxl=max(maxl,i-j);
            }
        }
        return maxl;
    }
};