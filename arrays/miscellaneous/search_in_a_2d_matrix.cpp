#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n=matrix.size();
        int m=matrix[0].size();
        int i=0,j=n*m-1;
        while(i<=j){
            int mid=(i+j)/2;
            int row=mid/m;
            int col=mid%m;
            if(matrix[row][col]==target){
                return true;
            }
            if(matrix[row][col]<target){
                i++;
            }
            else{
                j--;
            }
        }
        return false;
    }
};