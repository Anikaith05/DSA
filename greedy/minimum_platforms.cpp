#include<bits/stc++.h>
using namespace std;

class Solution {
  public:
    int minPlatform(vector<int>& arr, vector<int>& dep) {
        // code here
        int n=arr.size();
        int i=0,j=0;
        int count=0,maxi=0;
        sort(arr.begin(),arr.end());
        sort(dep.begin(),dep.end());
        while(i<n&&j<n){
            if(arr[i]<=dep[j]){
                count++;
                i++;
            }
            else{
                count--;
                j++;
            }
            maxi=max(maxi,count);
        }
        return maxi;
    }
};
