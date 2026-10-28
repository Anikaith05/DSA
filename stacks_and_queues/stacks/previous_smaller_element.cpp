#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> prevSmaller(vector<int>& arr) {
        //  code here
        int n=arr.size();
        vector<int>answer(n,0);
        stack<int>st;
        for(int i=0;i<n;i++){
            if(st.empty()){
                answer[i]=-1;
            }
            else if(!st.empty()&&st.top()<arr[i]){
                answer[i]=st.top();
            }
            else{
                while(!st.empty()&&st.top()>=arr[i]){
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