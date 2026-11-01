#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n=height.size();
        vector<int>prev_max(n,0);
        vector<int>next_max(n,0);
        prev_max[0]=height[0];
        next_max[n-1]=height[n-1];
        for(int i=1;i<n;i++){
            prev_max[i]=max(height[i],prev_max[i-1]);
        }
        for(int i=n-2;i>=0;i--){
            next_max[i]=max(height[i],next_max[i+1]);
        }
        int answer=0;
        for(int i=0;i<n;i++){
            answer+=min(prev_max[i],next_max[i])-height[i];
        }

        return answer;
    }
};