#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int num_less(vector<vector<int>>&matrix, int num){
        int n=matrix.size();
        int m=matrix[0].size();
        int count=0;
        for(int i=0;i<n;i++){
            if(upper_bound(matrix[i].begin(),matrix[i].end(),num)==matrix[i].end()){
                count+=m;
            }
            else{
                count+=upper_bound(matrix[i].begin(),matrix[i].end(),num)-matrix[i].begin();
            }
        }
        return count;
    }
    int median(vector<vector<int>> &mat) {
        // code here
        int n=mat.size();
        int m=mat[0].size();
        int min1=INT_MAX,max1=INT_MIN;
        for(int i=0;i<n;i++){
            min1=min(min1,mat[i][0]);
            max1=max(max1,mat[i][m-1]);
        }
        int low=min1,high=max1;
        while(low<=high){
            if(low==high){
                return low;
            }
            int mid=(low+high)/2;
            int count=num_less(mat,mid);
            if(count<=(n*m)/2){
                low=mid+1;
            }
            else{
                high=mid;
            }
        }
        return -1;
    }
};
