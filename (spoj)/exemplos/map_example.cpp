#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;
int n1,n2,n3;
string disc;
unordered_map<string,char> mp;

int main(){
    while(true){ //professor
        cin >> n1 >> n2 >> n3;
        if (n1==0||n2==0||n3==0)break;
        for(int i=0;i<n1;i++){
            cin >> disc;
            mp[disc] |= 1;
        }
        for(int i=0;i<n2;i++){
            cin >> disc;
            mp[disc] |= 2;
        }
        for(int i=0;i<n3;i++){
            cin >> disc;
            mp[disc] |= 4;
        }

        bool t=true;
        for(auto &x:mp){
            if((int)x.second !=7)t=false;
        }
        mp.clear();
        if(t)
            cout << "sim";
        else
            cout << "nao";
        cout << endl;
    }
    return 0;
}

/*

3 2 3
BC1512 ME1311 BC1512
ME1311 BC1512
BC1512 BC1512 BC1512


*/
