#include<bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

void combinations(string str,vector<int>&visited,vector<char>curr){
    if(curr.size()==str.length()){
        string c(curr.begin(),curr.end());
        cout<<c<<endl;
        return;
    }
    string c(curr.begin(),curr.end());
    cout<<c<<endl;
    int n=str.length();
    
    for(int i=0;i<n;i++){
        if(visited[i]==0){
            curr.push_back(str[i]);
            visited[i]=1;
            combinations(str,visited,curr);
            curr.pop_back();
            visited[i]=0;
        }
    }
    
}

int main() {
    string str;
    cin>>str;
    int n=str.length();
    vector<char>curr;
    vector<int>visited(n,0);
    combinations(str,visited,curr);
}
