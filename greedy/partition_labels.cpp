#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n=s.length();
        unordered_map<char,int>mp;
        for(int i=0;i<n;i++){
            mp[s[i]]=i;
        }
        vector<pair<int,int>>partitions;
        partitions.push_back({0,0});
        int i=0;
        while(i<n-1){
            i=mp[s[partitions.back().first]];
            partitions.back().second=i;
            for(int j=partitions.back().first;j<=i;j++){
                if(mp[s[j]]>i){
                    i=mp[s[j]];
                    partitions.back().second=i;
                }
            }
            if(i!=n-1) partitions.push_back({i+1,i+1});
        }
        vector<int>answer;
        for(auto p:partitions){
            answer.push_back((p.second-p.first+1));
        }
        return answer;
    }
};