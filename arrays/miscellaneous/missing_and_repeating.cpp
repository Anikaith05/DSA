#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> findTwoElement(vector<int>& arr) {
        // code here
        int n=arr.size();
        long long sum1=0;
        long long sum=0;
        for(int i=0;i<n;i++){
            sum+=arr[i];
            sum1+=1LL*arr[i]*arr[i];
        }
        long long d=sum-((1LL*n*(n+1))/2);
        long long d1=sum1-((1LL*n*(n+1)*(2*n+1))/6);
        long long s=d1/d;
        
        int duplicate=(s+d)/2;
        int missing=(s-d)/2;
        
        return {duplicate,missing};
    }
};