#include<bits/stdc++.h>
using namespace std;

struct item{
    int val;
    int wt;
};

class Compare{
    public:
    bool operator()(const item&a,const item&b){
        return ((1.00*a.val)/a.wt)>((1.00*b.val)/b.wt);
    }
};

class Solution {
  public:
    double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {
        // code here
        int n=val.size();
        vector<struct item>items;
        for(int i=0;i<n;i++){
            item s;
            s.val=val[i];
            s.wt=wt[i];
            items.push_back(s);
        }
        
        sort(items.begin(),items.end(),Compare());
        
        double value=0;
        
        for(int i=0;i<n;i++){
            if(items[i].wt<capacity){
                value+=items[i].val;
                capacity-=items[i].wt;
            }
            else{
                value+=(1.00*capacity/items[i].wt)*items[i].val;
                break;
            }
        }
        return value;
    }
};
