#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int to_num(char ch){
        return ch-'0';
    }
    int myAtoi(string s) {
        int str_len=s.length();
        bool leading_zeroes=true;
        bool char_read=false;
        bool sign_read=false;
        bool whitespace_read=false;
        long long ans=0;
        int final_ans;
        int sign=1; 


        for(int i=0;i<str_len;i++){
            char ch=s[i];
            if(ch==' '){
                if(whitespace_read==true){
                    break;
                }
                continue;
            }else if(isalpha(ch)||ch=='.'){
                whitespace_read=true;
                break;
            }else if(ch=='+'){
                if(char_read==true){
                    break;
                }
                if(sign_read==true){
                    break;
                }
                sign_read=true;
                whitespace_read=true;
            }
            else if(ch=='-'){
                if(char_read==true){
                    break;
                }
                if(sign_read==true){
                    break;
                }
                sign=-1; 
                sign_read=true;
                whitespace_read=true;
            }else if(leading_zeroes&&ch=='0'){
                char_read=true;
                whitespace_read=true;
                continue;
            }else{
                char_read=true;
                leading_zeroes=false;
                ans*=10;
                ans+=to_num(ch);
                if(sign*ans<INT_MIN){
                    return INT_MIN;
                }else if(sign*ans>INT_MAX){
                    return INT_MAX;
                }
                whitespace_read=true;
            }
        }
        if(ans==0) return 0;
        ans=sign*ans;
        final_ans=(int)ans;
        return final_ans;
    }
};