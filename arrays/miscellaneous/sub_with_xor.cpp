#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    long subarrayXor(vector<int> &arr, int k) {
        int n=arr.size();
        int count=0;
        vector<int>acc_xor(n,0);
        acc_xor[0]=arr[0];
        for(int i=1;i<n;i++){
            acc_xor[i]=acc_xor[i-1]^arr[i];
        }
        unordered_map<int,vector<int>>mp;
        mp[0].push_back(-1);
        for(int i=0;i<n;i++){
            if(mp.find(acc_xor[i]^k)!=mp.end()){
                count+=mp[acc_xor[i]^k].size();
            }
            mp[acc_xor[i]].push_back(i);
        }
    return count;
    }
};