#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
int factorial(int i){
    if(i==0||i==1){
        return 1;
    }
    return i*factorial(i-1);
}
    string getPermutation(int n, int k) {
        int left_over=k-1;
        vector<int>numbers;
        for(int i=0;i<n;i++){
            numbers.push_back(i+1);
        }
        string picked="";
        while(picked.length()!=n){
            int block_size=factorial((int)numbers.size()-1);
            int pick=(left_over)/block_size;
            picked+=to_string(numbers[pick]);
            numbers.erase(numbers.begin()+pick);
            left_over=left_over%block_size;
        }
        return picked;
    }
};