#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        int curr_level=0;
        queue<int>q;
        int n=friends.size();
        vector<int>visited(n,0);
        map<string,int>freq;
        q.push(id);
        visited[id]=1;
        while(!q.empty()){
            int num=q.size();
            for(int i=0;i<num;i++){
                int vertex=q.front();
                q.pop();
                for(auto node:friends[vertex]){
                    if(visited[node]==0){
                        q.push(node);
                        visited[node]=1;
                        if(curr_level==level-1){
                            for(auto m:watchedVideos[node]){
                                freq[m]++;
                            }
                        }
                    }
                }
            }
            curr_level++;
            if(curr_level==level) break;
        }
        vector<string>output;
        for(auto it:freq){
            output.push_back(it.first);
        }
        sort(output.begin(),output.end(),[&](const string&a,const string &b){
            if(freq[a]==freq[b]){
                return a<b;  
            }
            return freq[a]<freq[b];
        });
        return output;
    }
};