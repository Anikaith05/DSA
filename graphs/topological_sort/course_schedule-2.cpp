#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int>degrees(numCourses,0);
        int e=prerequisites.size();
        vector<int>indegree(numCourses,0);
        vector<vector<int>>adj(numCourses);
        for(int i=0;i<e;i++){
            adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
            indegree[prerequisites[i][0]]++;
        }
        queue<int>q;
        vector<int>res;
        for(int i=0;i<numCourses;i++){
            if(indegree[i]==0){
                q.push(i);
                res.push_back(i);
            }
        }
        while(!q.empty()){
            int vertex=q.front();
            q.pop();
            for(auto node:adj[vertex]){
                indegree[node]--;
                if(indegree[node]==0){
                    q.push(node);
                    res.push_back(node);
                }
            }
        }
        if(res.size()==numCourses){
            return res;
        }
        else{
            return {};
        }
    }
};