#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
struct Compare{
    unordered_map<int,int>&freq;
    Compare(unordered_map<int,int>&f): freq(f){}

    bool operator()(const int&a,const int&b){
        return freq[a]>freq[b];
    }
};
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n=nums.size();
        unordered_map<int,int> freq;

        for(int i=0;i<n;i++){
            freq[nums[i]]++;
        }
        Compare comp(freq);
        priority_queue<int,vector<int>,Compare>pq(comp);
        for(auto it:freq){
            pq.push(it.first);
            while(pq.size()>k){
                pq.pop();
            }
        }
        vector<int>ans;
        while(!pq.empty()){
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};