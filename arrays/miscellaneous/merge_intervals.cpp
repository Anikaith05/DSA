#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n=intervals.size();
        vector<vector<int>> merged_intervals;
        sort(intervals.begin(),intervals.end(),[](vector<int>a,vector<int>b){
            return a[0]<b[0];
        });
        
        for(auto arr:intervals){
            if(merged_intervals.size()==0){
                merged_intervals.push_back(arr);
                continue;
            }
            vector<int> ori=merged_intervals.back();
            int a1=ori[0];
            int b1=ori[1];
            int a2=arr[0];
            int b2=arr[1];

            if(a1<=a2&&a2<=b1){
                arr[0]=a1;
                arr[1]=max(b1,b2);
                merged_intervals.pop_back();
                merged_intervals.push_back(arr);
            }
            else{
                merged_intervals.push_back(arr);
            }
        }

    return merged_intervals;
    }
};