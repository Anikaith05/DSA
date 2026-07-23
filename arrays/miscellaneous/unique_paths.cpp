#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        int t=m+n-2;
        int r=min(m-1,n-1);
        long long ans=1;
        for(int i=1;i<=r;i++){
            ans=ans*(t-r+i)/i;
        }
        return int(ans);
    }
};