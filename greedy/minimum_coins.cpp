#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int findMin(int n) {
        int arr[]={1,2,5,10};
        int i=3;
        int count=0;
        while(n>0){
            if(arr[i]<n){
                n-=arr[i];
                count++;
            }
            else{
                i--;
            }
        }
        if(n<0) return -1;
        return count;
    }
};