#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n=s.length();
        int left=0;
        int maxl=0;
        unordered_set<int>st;
        for(int right=0;right<n;right++){
            while(st.find(s[right])!=st.end()){
                st.erase(s[left]);
                left++;
            }
            st.insert(s[right]);
            maxl=max(maxl,right-left+1);
        }
        return maxl;
    }
};