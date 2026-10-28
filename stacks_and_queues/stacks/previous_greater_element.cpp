#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> preGreaterEle(vector<int>& arr) {
        //  code here
        stack<int>st;
        int n=arr.size();
        vector<int>answer(n,0);
        for(int i=0;i<n;i++){
            if(st.empty()){
                answer[i]=-1;
            }
            else if(!st.empty()&&st.top()>arr[i]){
                answer[i]=st.top();
            }
            else{
                while(!st.empty()&&st.top()<=arr[i]){
                    st.pop();
                }
                if(st.empty()){
                    answer[i]=-1;
                }
                else{
                    answer[i]=st.top();
                }
            }
            st.push(arr[i]);
        }
        return answer;
    }
};