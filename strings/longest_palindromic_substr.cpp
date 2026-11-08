#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s,int i,int j){
        string str=s.substr(i,j-i+1);
        int n=str.length();
        int k=0,l=n-1;
        while(k<=l){
            if(str[k]!=str[l]){
                return false;
            }
            k++;
            l--;
        }
        return true;
    }
    string longestPalindrome(string s) {
        int n=s.length();
        int max_len=INT_MIN;
        string max_str="";
        for(int i=0;i<n;i++){
            //odd center
            int j=i;
            int k=i;
            while(j>=0&&k<n){
                if(s[j]==s[k]){
                    if(k-j+1>max_len){
                        max_len=k-j+1;
                        max_str=s.substr(j,k-j+1);
                    }
                    j--;
                    k++;
                }else{
                    break;
                }
            }

            //even center
            if(i+1<n){
                j=i;
                k=i+1;
                while(j>=0&&k<n){
                    if(s[j]==s[k]){
                        if(k-j+1>max_len){
                            max_len=k-j+1;
                            max_str=s.substr(j,k-j+1);
                        }
                        j--;
                        k++;
                    }else{
                        break;
                    }
                }
            }
        }
        return max_str;
    }
};