#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string join(vector<string>words,char ch){
        int n=words.size();
        string ans="";
        for(int i=0;i<n-1;i++){
            ans+=words[i];
            ans+=ch;
        }
        ans+=words[n-1];
        return ans;
    }
    string reverseWords(string s){
        int n=s.length();
        string curr="";
        vector<string>words;
        for(int i=0;i<n;i++){
            if(s[i]==' '){
                while(s[i]==' ') i++;
                i--;
                if(curr!=""){
                words.push_back(curr);
                }
                curr.clear();
            }else{
                curr+=s[i];
            }
        }
        if(curr!=""){
            words.push_back(curr);
        }
        reverse(words.begin(),words.end());
        string ans=join(words,' ');
        return ans;
    }
};