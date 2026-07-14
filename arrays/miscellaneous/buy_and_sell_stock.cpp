#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        int minn=INT_MAX;
        int maxn=0;
        for(int i=0;i<n;i++){
            if(prices[i]<minn){
                minn=prices[i];
            }
            if(prices[i]-minn>maxn){
                maxn=(prices[i]-minn);
            }
        }
    return maxn;
    }
};