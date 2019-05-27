#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(){
    string str;
    vector<pair<int,string> > list;
    while(cin>>str){
        int a = str.find("title="); 
        int b = str.find(".", a+6);
        int n = 0;
        if((a+1)*(b+1)) n = stoi(str.substr(a+6,b-a-6),0,10);
        list.push_back(make_pair(n,str));
    }
    sort(list.begin(), list.end());
    for(int i=0;i<list.size();i++)
        cout << list[i].second << endl;
    return 0;
}




