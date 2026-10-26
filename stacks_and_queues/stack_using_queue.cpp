#include<bits/stdc++.h>
using namespace std;

class MyStack {

private:
queue<int>q1;

public:
    MyStack() {
        queue<int>q1;
        while(!q1.empty()){
            q1.pop();
        }
    }

    void push(int x){
        int n=q1.size();
        q1.push(x);
        for(int i=0;i<n;i++){
            q1.push(q1.front());
            q1.pop();
        }
    }
    
    int pop() {
        if(q1.empty()) return -1;
        int x=q1.front();
        q1.pop();
        return x;
    }
    
    int top() {
        if(q1.empty()) return -1;
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */