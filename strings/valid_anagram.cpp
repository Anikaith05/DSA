#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        int n=s.size();
        int m=t.size();
        if(n!=m) return false;
        int c[256]={0};
        for(int i=0;i<n;i++){
            c[s[i]-'a']++;
        }
        for(int j=0;j<m;j++){
            c[t[j]-'a']--;
        }
        for(int i=0;i<256;i++){
            if(c[i]!=0){
                return false;
            }
        }
        return true;
    }
};