#include<bits/stdc++.h>
using namespace std;

//do the dfs_traversal
//each node in visited has 3 states-> 0->unvisited,1->processsing(in the stack),2->we are done processing(removed form the stack)
//in dfs traversal at every vertex we look at all of its neighbours and if visited[neighbour]==1->we say that the cycle is detected, else we just mark the neighbour as 1 in visited and then push it into the stack(call the recursive function), after we are done with processing all the node of a vertex we mark it as 2 in the visited 
class Solution {
public:
    void dfs_traversal(vector<vector<int>>&adj,int vertex,vector<int>&visited,bool&cycle){
        visited[vertex]=1;
        for(int node:adj[vertex]){
            if(visited[node]==1){
                cycle=true;
                return;
            }
            else if(visited[node]==0){
                visited[node]=1;
                dfs_traversal(adj,node,visited,cycle);
            }
        }
        visited[vertex]=2;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites){
        vector<vector<int>>adj(numCourses);
        for(vector<int> i:prerequisites){
            adj[i[1]].push_back(i[0]);
        }

        bool cycle=false;
        for(int i=0;i<numCourses;i++){
            vector<int>visited(numCourses,0);
            dfs_traversal(adj,i,visited,cycle);
        }
        return !cycle;
    }
};