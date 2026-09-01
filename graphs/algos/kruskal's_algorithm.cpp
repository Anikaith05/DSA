#include<bits/stdc++.h>
using namespace std;

class Compare{
    public:
    bool operator()(vector<int>a,vector<int>b){
        return a[2]>b[2];
    }
};
class Solution {
  public:
    int find(int x,vector<int>&parent){
        if(parent[x]==x){
            return x;
        }
        return find(parent[x],parent);
    }
    void unioni(int u,int v,vector<int>&parent){
        int rootu=find(u,parent);
        int rootv=find(v,parent);
        if(rootu==rootv) return;
        parent[rootu]=rootv;
    }
    int kruskalsMST(int V, vector<vector<int>> &edges) {
        int e=edges.size();
        vector<int>parent(V,-1);
        int mst_wt=0;
        for(int i=0;i<V;i++){
            parent[i]=i;
        }
        priority_queue<vector<int>,vector<vector<int>>,Compare>pq;
        for(int i=0;i<e;i++){
            pq.push(edges[i]);
        }
        while(!pq.empty()){
            vector<int>vertex=pq.top();
            pq.pop();
            int u=vertex[0];
            int v=vertex[1];
            int wt=vertex[2];
            if(find(u,parent)!=find(v,parent)){
                mst_wt+=wt;
                unioni(u,v,parent);
            }
        }
        return mst_wt;
    }
};