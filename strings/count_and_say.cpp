#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        string str="1";
        char curr;
        for(int i=2;i<=n;i++){
            int j=str.length()-1;
            string newstr="";
            int c=0;
            while(j>=0){
                if(j==str.length()-1){
                    curr=str[str.length()-1];
                    c++;
                }else if(str[j]==str[j+1]){
                    curr=str[j];
                    c++;
                }else{
                    newstr=curr+newstr;
                    newstr=to_string(c)+newstr;
                    c=1;
                    curr=str[j];
                }
                j--;
            }

            newstr=curr+newstr;
            newstr=to_string(c)+newstr;

            
            str=newstr;
        }
        return str;
    }
};

