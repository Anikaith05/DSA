#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

void dfs1(int node, vector<vector<int>>& adj,vector<int>& vis, stack<int>& st) {
        vis[node] = 1;
        for (int neighbour : adj[node]) {
            if (!vis[neighbour]) {
                dfs1(neighbour, adj, vis, st);
            }
        }
        st.push(node);
}
void dfs2(int node, vector<vector<int>>& revAdj,
              vector<int>& vis) {

        vis[node] = 1;

        for (int neighbour : revAdj[node]) {
            if (!vis[neighbour]) {
                dfs2(neighbour, revAdj, vis);
            }
        }
}

int kosaraju(int V, vector<vector<int>>& edges) {

        vector<vector<int>> adj(V);
        vector<vector<int>> revAdj(V);
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            revAdj[v].push_back(u);
        }


        vector<int> vis(V, 0);
        stack<int> st;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs1(i, adj, vis, st);
            }
        }


        fill(vis.begin(), vis.end(), 0);

        int sccCount = 0;

        while (!st.empty()) {

            int node = st.top();
            st.pop();

            if (!vis[node]) {
                dfs2(node, revAdj, vis);
                sccCount++;
            }
        }

        return sccCount;
    }
};