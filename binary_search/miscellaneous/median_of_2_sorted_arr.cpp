#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int num_less_or_equal(vector<int>nums1,vector<int>nums2,int mid){
        int count=0;
        if(upper_bound(nums1.begin(),nums1.end(),mid)==nums1.end()){
            count+=nums1.size();
        }
        else{
            count+=upper_bound(nums1.begin(),nums1.end(),mid)-nums1.begin();
        }

        if(upper_bound(nums2.begin(),nums2.end(),mid)==nums2.end()){
            count+=nums2.size();
        }
        else{
            count+=upper_bound(nums2.begin(),nums2.end(),mid)-nums2.begin();
        }
        return count;
    }
    int kthSmallestNum(vector<int>nums1,vector<int>nums2,int k){
        int n=nums1.size();
        int m=nums2.size();
        if(n==0&&m==0){
            return -1.00;
        }
        int min1;
        int max1;
        if(n==0){
            max1=nums2.back();
            min1=nums2[0];
        }
        else if(m==0){
            max1=nums1.back();
            min1=nums1[0];
        }
        else{
            max1=max(nums1.back(),nums2.back());
            min1=min(nums1[0],nums2[0]);
        }
        int low=min1,high=max1;
        while(low<=high){
            if(low==high){
                return low;
            }
            int mid = low + (high - low) / 2;
            if(num_less_or_equal(nums1,nums2,mid)>=k){
                high=mid;
            }
            else{
                low=mid+1;
            }
        }
        return -1;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size();
        int m=nums2.size();
        if((n+m)%2==1){
            return kthSmallestNum(nums1,nums2,((n+m)/2)+1);
        }
        else{
            int n1=kthSmallestNum(nums1,nums2,((n+m)/2));
            int n2=kthSmallestNum(nums1,nums2,((n+m)/2)+1);
            return (n1+n2)/2.00;
        }
    return -1.00;
    }
};


