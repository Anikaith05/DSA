#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(vector<string>&matrix,int i,int j,int n){
        for(int k=0;k<n;k++){
            if(matrix[k][j]=='Q'||matrix[i][k]=='Q'){
                return false;
            }
        }

        for(int k=0;k<n;k++){
            for(int q=0;q<n;q++){
                if((abs(k-i)==abs(q-j))||((k+q)==(i+j))){
                    if(matrix[k][q]=='Q'){
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void n_queens(vector<vector<string>>&answer,int i,int n,vector<string>buffer){
        if(i>=n){
            answer.push_back(buffer);
            return;
        }
        for(int j=0;j<n;j++){
            if(isValid(buffer,i,j,n)){
                buffer[i][j]='Q';
                n_queens(answer,i+1,n,buffer);
                buffer[i][j]='.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string>buffer(n);

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                buffer[i]+=".";
            }
        }

        vector<vector<string>>answer;

        n_queens(answer,0,n,buffer);

        return answer;
    }
};