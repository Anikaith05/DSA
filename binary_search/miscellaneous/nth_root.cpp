#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int pow(int x,int n){
        if(n==0){
            return 1;
        }
        if(x==0){
            return 0;
        }
        long long ans=1;
        while(n>0){
            if(n%2==1){
                ans*=x;
                n--;
            }
            else{
                x=x*x;
                n=n/2;
            }
        }
        return int(ans);
    }
    int nthRoot(int n, int m){
        int low=0,high=m;
        while(low<=high){
            int mid=(low+high)/2;
            int val=pow(mid,n);
            if(val==m){
                return mid;
            }
            else if(val<m){
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
        return -1;
    }
};