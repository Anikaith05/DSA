#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n=nums.size();
        unordered_set<int>st(nums.begin(),nums.end());
        int maxl=0;
        for(auto x:st){
            int len=1;
            int ele=x;
            if(st.find(ele-1)==st.end()){
                while(st.find(ele+1)!=st.end()){
                    len++;
                    ele++;
                }
                maxl=max(maxl,len);
            }
        }
        return maxl;
    }
};