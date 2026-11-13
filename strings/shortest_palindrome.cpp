#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s){
        int n=s.length();
        int i=0,j=n-1;
        while(i<n&&j>=0){
            if(s[i]!=s[j]){
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
    vector<int> calc_lps(string s,vector<int>lps){
        lps[0]=0;
        int i=1,j=0;
        int n=s.length();

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
        return lps;
    }
    string shortestPalindrome(string s) {
        if(isPalindrome(s)){
            return s;
        }
        
        string rev_s=s;
        reverse(rev_s.begin(),rev_s.end());
    
        string lps_str=s+'#'+rev_s;
        int n=lps_str.size();

        vector<int>lps(n,0);

        lps=calc_lps(lps_str,lps);


        int max_len=lps[n-1];

        string str=s.substr(max_len,n-max_len);
        reverse(str.begin(),str.end());

        return str+s;
    }
};