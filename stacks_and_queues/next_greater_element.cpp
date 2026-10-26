#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size();
        int m=nums2.size();

        vector<int>next_greatest(m,-1);
        stack<int>st;
        for(int i=m-1;i>=0;i--){
            while(!st.empty()&&nums2[i]>=st.top()){
                st.pop();
            }
            if(st.empty()){
                next_greatest[i]=-1;
            }
            else{
                next_greatest[i]=st.top();
            }
            st.push(nums2[i]);
        }
        vector<int>answer(n,-1);

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(nums1[i]==nums2[j]){
                    answer[i]=next_greatest[j];
                }
            }
        }

        return answer;
    }
};