#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPrime(int n){
        if(n==1){
            return false;
        }
        if(n==2){
            return true;
        }
        int flag=false;
        for(int i=2; i<=sqrt(n);i++){
            if(n%i==0){
                flag=true;
            }
        }
        return !flag;
    }
    int minOperations(vector<int>& nums) {
        int len=nums.size();
        int count=0;
        for(int i=0;i<len;i++){
            if(i%2==0){
                if(isPrime(nums[i])){
                    continue;
                }
                else{
                    while(!isPrime(nums[i])){
                    nums[i]+=1;
                    count++;
                    }
                }
            }
            else{
                if(!isPrime(nums[i])){
                    continue;
                }
                else{
                    while(isPrime(nums[i])){
                    nums[i]+=1;
                    count++;
                    }
                }
            }
        }
        return count;
    }
};

//i am running into TLE here