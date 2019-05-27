#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    priority_queue<pair<int,string>> a;
    a.push(make_pair(5,"cinco"));
    a.push(make_pair(4,"quatro"));
    a.push(make_pair(1,"um"));
    a.push(make_pair(2,"dois"));
    a.push(make_pair(6,"seis"));

    while(!a.empty()){
        cout << a.top().first << endl;
        a.pop();
    }
    return 0;
}
#include <iostream>
