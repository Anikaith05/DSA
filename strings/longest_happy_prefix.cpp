#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void calc_lps(string s,vector<int>&lps,int n){
        lps[0]=0;
        int i=1,j=0;
        while(i<n){
            if(s[i]==s[j]){
                lps[i]=j+1;
                i++;
                j++;
            }else if(j>0){
                j=lps[j-1];
            }else{
                lps[i]=0;
                i++;
            }
        }
    }
    string longestPrefix(string s) {
        int n=s.length();
        
        vector<int>lps(n,0);
        calc_lps(s,lps,n);
        int maxe=lps[n-1];

        return s.substr(0,maxe);
    }
};