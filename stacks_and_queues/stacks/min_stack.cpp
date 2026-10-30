#include<bits/stdc+++.h>
using namespace std;

class MinStack {
public:
    stack<long long>st;
    int curr_min;
    MinStack(){
        while(!st.empty()){
            st.pop();
        }
    }
    
    void push(int value) {
        if(st.empty()){
            curr_min=value;
            st.push(1LL*value);
            return;
        }
        if(value<curr_min){
            st.push(2LL*value-curr_min);
            curr_min=value;
        }else{
            st.push(1LL*value);
        }
    }
    
    void pop() {
        if(st.top()<curr_min){
            curr_min=2LL*curr_min-st.top();
        }
        st.pop();
    }
    
    int top() {
        if(st.empty()){
            return INT_MIN;
        }
        if(st.top()<curr_min){
            return curr_min;
        }else{
            return st.top();
        }
    }
    
    int getMin() {
        if(st.empty()){
            return INT_MIN;
        }
        return curr_min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */