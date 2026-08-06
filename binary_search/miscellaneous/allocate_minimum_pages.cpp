#include<bitstdc++.h>
using namespace std;

class Solution {
  public:
    bool isValid(vector<int>arr,int k,long long mid){
        int n=arr.size();
        int students=1;
        long long pages=0;
        for(int i=0;i<n;i++){
            if(arr[i]>mid){
                return false;
            }
            if(pages+arr[i]<=mid){
                pages+=arr[i];
            }
            else{
                students++;
                pages=arr[i];
            }
        }
        return (students<=k)?true:false;
    }
    int findPages(vector<int> &arr, int k) {
        // code here
        if(k>arr.size()){
            return -1;
        }
        int n=arr.size();
        long long sum=0;
        long long maxi=INT_MIN;
        for(int i=0;i<n;i++){
            sum+=arr[i];
            maxi=max(maxi,(long long)arr[i]);
        }
        long long low=maxi,high=sum;
        int ans=-1;
        while(low<=high){
            long long mid=low+(high-low)/2;
            if(isValid(arr,k,mid)){
                ans=int(mid);
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }
        return ans;
    }
};

