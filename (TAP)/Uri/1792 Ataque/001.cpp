// constructing priority queues
#include <iostream>       // cout
#include <queue>          // priority_queue
#include <vector>         // vector
#include <functional>     // greater

class mycomparison{
    bool reverse;
public:
    mycomparison(const bool& revparam=false) {
        reverse = revparam;
    }
    
    bool operator() (const int& lhs, const int&rhs) const {
        if (reverse) 
            return (lhs>rhs);
        else 
            return (lhs<rhs);
    }
  
};

int main (){
  int myints[]= {10, 60, 50, 20};

  priority_queue<int> first;
  priority_queue<int> second (myints, myints + 4);
  priority_queue<int, vector<int>, greater<int> >  third (myints, myints+4);

  // using mycomparison:
  typedef priority_queue<int, vector<int>, mycomparison> mypq_type;

  mypq_type fourth;                       // less-than comparison

  mypq_type fifth (mycomparison(true));   // greater-than comparison

  return 0;
}