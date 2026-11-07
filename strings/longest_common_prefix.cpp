#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n=strs.size();
        sort(strs.begin(),strs.end());
        string str1=strs[0];
        string str2=strs[n-1];
        int i=0,j=0;
        string ans="";
        while(i<str1.length()&&j<str2.length()){
            if(str1[i]==str2[j]){
                ans+=str1[i];
                i++;
                j++;
            }else{
                break;
            }
        }
        return ans;
    }
};