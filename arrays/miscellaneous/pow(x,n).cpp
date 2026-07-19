#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double power(double x,long long n){
        if(n==0){
            return 1;
        }
        double y=power(x,n/2);
        if(n%2==0){
            return y*y;
        }
        else{
            return x*y*y;
        }
    }
    double myPow(double x, int n) {
        long long N=n;
        if(n<0){
            x=1/x;
            N=-N;
        }
        return power(x,n);
    }
};