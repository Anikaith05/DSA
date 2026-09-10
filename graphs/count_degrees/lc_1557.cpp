#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int>count_in(n,0);
        int e=edges.size();
        for(int i=0;i<e;i++){
            count_in[edges[i][1]]++;
        }
        vector<int>final_ans;
        for(int i=0;i<n;i++){
            if(count_in[i]==0){
                final_ans.push_back(i);
            }
        }
        return final_ans;
    }
};