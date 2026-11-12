class Solution {
public:
    int RabinKarp(string txt,string pat){
        int q=101;
        int d=256;
        int m=pat.size();
        int n=txt.size();

        if(m>n) return 0;

        int p=0;
        int t=0;

        int h=1;
        for(int i=0;i<m-1;i++){
            h=(h*d)%q;
        }

        for(int i=0;i<m;i++){
            p=(p*d+pat[i])%q;
            t=(t*d+txt[i])%q;
        }

        for(int i=0;i<=n-m;i++){
            if(p==t){
                int j;
                for(j=0;j<m;j++){
                    if(txt[i+j]!=pat[j]){
                        break;
                    }
                }
                if(j==m){
                    return 1;
                }
            }

            if(i+m<n){
                t=(d*(t-txt[i]*h)+txt[i+m])%q;
                if(t<0) t+=q;
            }
        }
        return 0;
    }
    int repeatedStringMatch(string a, string b) {
        if(a==b) return 1;

        int count=1;
        string source=a;
        while(source.size()<b.size()){
            count++;
            source+=a;
        }

        if(RabinKarp(source,b)){
            return count;
        }

        if(RabinKarp(source+a,b)){
            return count+1;
        }
        return -1;
    }
};
