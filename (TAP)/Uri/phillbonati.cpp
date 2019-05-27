#include <iostream>
using namespace std;
long long a(int n){
    if(n==0) return 0;
    if(n==1) return 1;
    if(n%2)
        return a(n-1)*a(n-2);
    return a(n-1)+a(n-2);
};

    
int main(){
    int n;
    while(cin >> n){
        cout << a(n-1) << endl;
    }
    return 0;
}

