#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s){
        int n=s.length();
        int i=0,j=n-1;
        while(i<=j){
            if(s[i]!=s[j]){
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
    void calc(vector<vector<string>>&answer,int start,string str,vector<string>buffer){
        if(start==str.size()){
            answer.push_back(buffer);
            return;
        }

        for(int end=start;end<str.size();end++){
            string sub=str.substr(start,end-start+1);
            if(isPalindrome(sub)){
            buffer.push_back(sub);
            calc(answer,end+1,str,buffer);
            buffer.pop_back();
            }
        }
    }
    
    vector<vector<string>> partition(string s) {
        vector<vector<string>>answer;

        int n=s.length();
        vector<string>buffer;
        calc(answer,0,s,buffer);

        return answer;
    }
};