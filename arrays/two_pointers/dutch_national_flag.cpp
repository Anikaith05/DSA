#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums){
        int n=nums.size();
        vector<int> freq(3,0);
        for(int i=0;i<n;i++){
            if(nums[i]==0){
                freq[0]++;
            }
            else if(nums[i]==1){
                freq[1]++;
            }
            else{
                freq[2]++;
            }
        }
        int i=0;
        while(freq[0]!=0){
            nums[i]=0;
            freq[0]--;
            i++;
        }
        while(freq[1]!=0){
            nums[i]=1;
            freq[1]--;
            i++;
        }
        while(freq[2]!=0){
            nums[i]=2;
            freq[2]--;
            i++;
        }
    }
};