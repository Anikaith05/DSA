#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int num_less_or_eq(vector<int>a,vector<int>b,int mid){
        return (upper_bound(a.begin(),a.end(),mid)-a.begin())+(upper_bound(b.begin(),b.end(),mid)-b.begin());;
    }
    int kthElement(vector<int> &a, vector<int> &b, int k) {
        int n=a.size();
        int m=b.size();
        if(n==0&&m==0){
            return n;
        }
        int min1;
        int max1;
        if(n==0){
            max1=b.back();
            min1=b[0];
        }
        else if(m==0){
            max1=a.back();
            min1=a[0];
        }
        else{
            max1=max(a.back(),b.back());
            min1=min(a[0],b[0]);
        }
        int low=min1,high=max1;
        while(low<=high){
            if(low==high){
                return low;
            }
            int mid=(low+high)/2;
            if(num_less_or_eq(a,b,mid)>=k){
                high=mid;
            }
            else{
                low=mid+1;
            }
        }
        return -1;
    }
};