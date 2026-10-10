#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void calc_all_routes(vector<vector<int>>&maze,vector<string>&answer,string buffer,int i,int j){
        int n=maze.size();
        if(i==n-1&&j==n-1){
            answer.push_back(buffer);
            return;
        }
        
        if(i+1<n&&i+1>=0&&j<n&&j>=0&&maze[i+1][j]==1){
            buffer+="D";
            maze[i][j]=0;
            calc_all_routes(maze,answer,buffer,i+1,j);
            buffer.pop_back();
            maze[i][j]=1;
        }
        
        if(j-1>=0&&j-1<n&&i>=0&&i<n&&maze[i][j-1]==1){
            buffer+="L";
            maze[i][j]=0;
            calc_all_routes(maze,answer,buffer,i,j-1);
            buffer.pop_back();
            maze[i][j]=1;
        }
        
        if(j+1<n&&j+1>=0&&i>=0&&i<n&&maze[i][j+1]==1){
            buffer+="R";
            maze[i][j]=0;
            calc_all_routes(maze,answer,buffer,i,j+1);
            buffer.pop_back();
            maze[i][j]=1;
        }
        
        if(i-1>=0&&i-1<n&&j<n&&j>=0&&maze[i-1][j]==1){
            buffer+="U";
            maze[i][j]=0;
            calc_all_routes(maze,answer,buffer,i-1,j);
            buffer.pop_back();
            maze[i][j]=1;
        }
    }
    vector<string> ratInMaze(vector<vector<int>>& maze) {
        // code here
        vector<string>answer;
        if(maze[0][0]==0) return {""};
        
        string buffer="";
        
        calc_all_routes(maze,answer,buffer,0,0);
        
        return answer;
        
    }
};