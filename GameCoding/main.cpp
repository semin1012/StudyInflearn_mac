#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include "Vector.hpp"


int main()
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    Vector<int>::iterator it;
    // Vector에 iterator가 소속된 느낌
    
    for ( it = v.begin(); it!= v.end(); it++ )
    {
        int data = *it;
        cout << data << endl;
    }
//    it++;
//    v.begin();
//    v.end();
//    it != v.end();
//    *it;
// 위의 기능을 iterator로 구현할 수 있다. 
}
