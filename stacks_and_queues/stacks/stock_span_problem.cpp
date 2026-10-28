#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> calculateSpan(vector<int>& arr) {
        // code here
        int n=arr.size();
        stack<int>st;
        vector<int>answer(n,0);
        for(int i=0;i<n;i++){
            if(st.empty()){
                answer[i]=-1;
            }
            else if(!st.empty()&&arr[st.top()]>arr[i]){
                answer[i]=st.top();
            }
            else{
                while(!st.empty()&&arr[st.top()]<=arr[i]){
                    st.pop();
                }
                if(st.empty()){
                    answer[i]=-1;
                }
                else{
                    answer[i]=st.top();
                }
            }
            st.push(i);
        }
        
    for(int i=0;i<n;i++){
        answer[i]=i-answer[i];
    }
    return answer;
    }
};