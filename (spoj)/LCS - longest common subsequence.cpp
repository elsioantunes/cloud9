// Longest Common Subsequence
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string a, b;

int main() {
    cin >> a >> b;
    vector<int> lcs[a.length()+1];
    vector<int> S[a.length()+1];
    for(int i=0; i<=a.length(); i++){
        for(int j=0; j<=b.length(); j++){
            lcs[i].push_back(0);
            S[i].push_back(0);
        }
    }

    for(int i=0; i<=a.length(); i++){
        for(int j=0; j<=b.length(); j++){
            if(i&&j){
                if(a[i-1]==b[j-1]){
                    lcs[i][j] = lcs[i-1][j-1] + 1;
                    S[i][j] = 1;
                }else{
                    if(lcs[i-1][j]>=lcs[i][j-1]){
                        lcs[i][j] = lcs[i-1][j];
                        S[i][j] = 2;
                    }else{
                        lcs[i][j] = lcs[i][j-1];
                        S[i][j] = 3;
                    }
                }
            }
        }
    }

    string resp = "";
    int m=a.length(), n=b.length();
    while(1){
        if(S[m][n]==1){
            resp = a[m-1] + resp;
            m--; n--;
        }else if(S[m][n]==2){
            m--;
        }else if(S[m][n]==3){
            n--;
        }else if(!S[m][n]) break;
    }


    cout << resp << endl;

    return 0;
}


