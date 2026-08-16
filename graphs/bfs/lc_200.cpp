#include<bits/stdc++.h>
using namespace std;

//do a bfs 
//add the node to the queue only if the node if not 0
//when the queue is empty you increase the count by 1
//do the bfs starting from each of the nodes, and visited array should be global in this context
class Solution {
public:
    void bfs_traversal(vector<vector<char>>&grid,int i,int j,int &count){
        int m=grid.size();
        int n=grid[0].size();
        queue<pair<int,int>>q;
        q.push({i,j});
        vector<int> dr={-1,0,1,0};
        vector<int> dc={0,-1,0,1};

        while(!q.empty()){
            auto [i,j]=q.front();
            q.pop();
            grid[i][j]='0';
            for(int k=0;k<4;k++){
                int nr=i+dr[k];
                int nc=j+dc[k];
                if(nr>=0&&nr<m&&nc>=0&&nc<n&&(grid[nr][nc]=='1')){
                    q.push({nr,nc});
                    grid[nr][nc]='0';
                }
            }
        }
        count++;
        
    }
    int numIslands(vector<vector<char>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        int count=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='1'){
                    bfs_traversal(grid,i,j,count);
                }
            }
        }
        return count;
    }
};