#include<bits/stdc++.h>
using namespace std;

struct item{
    int deadline;
    int profit;
};
struct Compare{
    bool operator()(const item&a,const item&b){
        return a.deadline<b.deadline;
    }
};
struct Compare1{
    bool operator()(const item&a,const item&b){
        return a.profit>b.profit;        
    }
};
class Solution {
  public:
    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit) {
        vector<struct item>items;
        int n=deadline.size();
        for(int i=0;i<n;i++){
            item s;
            s.deadline=deadline[i];
            s.profit=profit[i];
            items.push_back(s);
        }
        
        sort(items.begin(),items.end(),Compare());
        
        priority_queue<item,vector<struct item>,Compare1>pq;
        
        for(int i=0;i<n;i++){
            if(items[i].deadline>pq.size()){
                pq.push(items[i]);
            }
            else if(items[i].profit>pq.top().profit){
                pq.pop();
                pq.push(items[i]);
            }
        }
        int sum=0;
        int c=0;
        while(!pq.empty()){
            sum+=pq.top().profit;
            c++;
            pq.pop();
        }
        return {c,sum};
            
    }
};