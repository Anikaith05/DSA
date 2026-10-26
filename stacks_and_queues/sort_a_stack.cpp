#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void sortStack(stack<int> &st) {
        // Your code goes here
        if(st.empty()) return;

        int x=st.top();
        st.pop();
        sortStack(st);

        stack<int>st2;
        while(!st.empty()&&x<=st.top()){
            st2.push(st.top());
            st.pop();
        }
        st.push(x);
        while(!st2.empty()){
            st.push(st2.top());
            st2.pop();
        }
    }
};