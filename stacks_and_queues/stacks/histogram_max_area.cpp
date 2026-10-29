#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void compute_prev(vector<int>arr,vector<int>&prev){
        int n=arr.size();
        stack<int>st;
        for(int i=0;i<n;i++){
            if(st.empty()){
                prev[i]=-1;
            }
            else if(!st.empty()&&arr[st.top()]<arr[i]){
                prev[i]=st.top();
            }
            else{
                while(!st.empty()&&arr[st.top()]>=arr[i]){
                    st.pop();
                }
                if(st.empty()){
                    prev[i]=-1;
                }
                else{
                    prev[i]=st.top();
                }
            }
            st.push(i);
        }
    }
    void compute_next(vector<int>arr,vector<int>&next){
        int n=arr.size();
        stack<int>st;
        for(int i=n-1;i>=0;i--){
            if(st.empty()){
                next[i]=n;
            }
            else if(!st.empty()&&arr[st.top()]<arr[i]){
                next[i]=st.top();
            }
            else{
                while(!st.empty()&&arr[st.top()]>=arr[i]){
                    st.pop();
                }
                if(st.empty()){
                    next[i]=n;
                }
                else{
                    next[i]=st.top();
                }
            }
            st.push(i);
        }
    }
    int getMaxArea(vector<int> &arr) {
        // code here
        int n=arr.size();
        vector<int>prev(n,0);
        vector<int>next(n,0);
        
        compute_prev(arr,prev);
        compute_next(arr,next);
        
        vector<int>area(n,0);
        int max_a=INT_MIN;
        for(int i=0;i<n;i++){
            int area=(next[i]-prev[i]-1)*arr[i];
            max_a=max(max_a,area);
        }
    return max_a;
    }
};
