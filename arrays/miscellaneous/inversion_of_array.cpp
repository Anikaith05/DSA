#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void merge(vector<int>&arr,int low,int mid,int high,int &count){
        int i=low,j=mid+1,k=0;
        vector<int> arrn(high-low+1,0);
        while(i<=mid&&j<=high){
            if(arr[i]<=arr[j]){
                arrn[k]=arr[i];
                i++;
                k++;
            }
            else{
                arrn[k]=arr[j];
                k++;
                j++;
                count+=(mid-i+1);
            }
        }
        while(i<=mid){
            arrn[k]=arr[i];
            k++;
            i++;
        }
        while(j<=high){
            arrn[k]=arr[j];
            k++;
            j++;
        }
        for(int i=0;i<(high-low+1);i++){
            arr[low+i]=arrn[i];
        }
    }
    
    void mergesort(vector<int>&arr,int low,int high,int &count){
        int n=arr.size();
        if(low<high){
        int mid=(low+high)/2;
        mergesort(arr,low,mid,count);
        mergesort(arr,mid+1,high,count);
        merge(arr,low,mid,high,count);
        }
    }
    int inversionCount(vector<int> &arr) {
        // code here
        int n=arr.size();
        int count=0;
        mergesort(arr,0,n-1,count);
        return count;
    }
};