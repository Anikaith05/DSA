#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void calc_sub_sums(vector<int>&arr,int sum,vector<int>&sums,int i){
        if(i==arr.size()){
            sums.push_back(sum);
            return;
        }
        
        calc_sub_sums(arr,sum+arr[i],sums,i+1);
        calc_sub_sums(arr,sum,sums,i+1);
    }
    vector<int> subsetSums(vector<int>& arr) {
        // code here
        vector<int>sums;
        int n=arr.size();
        
        int sum=0;
        calc_sub_sums(arr,sum,sums,0);
        return sums;
    }
};