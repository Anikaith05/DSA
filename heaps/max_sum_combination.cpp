#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    struct Compare{
        bool operator()(const int&a,const int&b){
            return a>b;
        }
    };
    vector<int> topKSumPairs(vector<int>& a, vector<int>& b, int k) {
        // code here
        int n=a.size();
        vector<int>sorted;
        sort(a.begin(),a.end(),Compare());
        sort(b.begin(),b.end(),Compare());
        
        priority_queue<vector<int>>pq;
        int i=0,j=0;
        pq.push({a[0]+b[0],0,0});
        set<pair<int,int>>visited;
        visited.insert({0,0});
        while(!pq.empty()&&sorted.size()<k){
            sorted.push_back(pq.top()[0]);
            i=pq.top()[1];
            j=pq.top()[2];
            pq.pop();
            if(i+1<n&&visited.find({i+1,j})==visited.end()){
                pq.push({a[i+1]+b[j],i+1,j});
                visited.insert({i+1,j});
            }
            if(j+1<n&&visited.find({i,j+1})==visited.end()){
                pq.push({a[i]+b[j+1],i,j+1});
                visited.insert({i,j+1});
            }
        }
        return sorted;
    }
};