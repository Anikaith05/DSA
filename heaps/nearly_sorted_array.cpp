#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void nearlySorted(vector<int>& arr, int k) {
        // code here
        int n=arr.size();
        priority_queue<int,vector<int>,greater<int>>pq;
        vector<int>sorted;
        for(int i=0;i<n;i++){
            pq.push(arr[i]);
            while(pq.size()>k){
                sorted.push_back(pq.top());
                pq.pop();
            }
        }
        while(!pq.empty()){
            sorted.push_back(pq.top());
            pq.pop();
        }
        arr=sorted;
    }
};