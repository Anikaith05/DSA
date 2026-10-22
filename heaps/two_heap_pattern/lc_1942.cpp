#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct Compare{
        bool operator()(const vector<int>&a,const vector<int>&b){
            return a[1]>b[1];
        }
    };
    struct Compare2{
        bool operator()(const vector<int>&a,vector<int>&b){
            return a[0]<b[0];
        }
    };
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int n=times.size();
        priority_queue<int,vector<int>,greater<int>>chairs;//minHeap
        priority_queue<vector<int>,vector<vector<int>>,Compare>people;//minHeap based on [1]
        vector<vector<int>>friends;
        for(int i=0;i<n;i++){
            friends.push_back({times[i][0],times[i][1],i});
        }
        sort(friends.begin(),friends.end(),Compare2());

        for(int i=0;i<n;i++){
            chairs.push(i);
        }

        for(int i=0;i<n;i++){
            while(!people.empty()&&people.top()[1]<=friends[i][0]){
                chairs.push(people.top()[2]);
                people.pop();
            }
            if(friends[i][2]==targetFriend) return chairs.top();
            int chair=chairs.top();
            chairs.pop();
            people.push({friends[i][0],friends[i][1],chair});
        }
        return -1;
    }
};