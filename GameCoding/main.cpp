#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void Print()
{
    cout << "Hello World" << endl;
}

class Test
{
public:
    // test 안에 종속적인 스태틱 함수는 멤버 함수와 좀 다르다
    static void PrintStatic() {};
    void PrintTest() {};  // 멤버 함수
};

int main()
{
    // 멤버 함수 포인터는 (정적/전역 함수랑 다르다)
    // 보통의 함수 포인터처럼 사용할 수가 없다.
    // 함수 호출 규약에 안 맞아서 사용할 수 없다.
    // 함수 호출 규약: cdecl, thiscall
    //using FuncPtrType = void(*)();
    //FuncPtrType func = &Test::PrintTest; << 안 됨
    
    using MemFuncPtrType = void(Test::*)();
    MemFuncPtrType funcPtr = &Test::PrintTest;
    
    Test t;
    (t.*funcPtr)();
        
    // 이상하고 어려운 문법이지만 서버를 할 때 사용하게 될 것이다.
    // 함수를 실행하는 시점을 미룰 수 있다는 것이 굉장한 장점이다.
    Test* t2 = &t;
    (t2->*funcPtr)();
    
    // 서버에서 굉장히 많은 유저들의 주문서를 순서대로 수행해야 하는데
    // 함수 포인터를 사용하면 함수 변수의 멤버변수 (클래스의 멤버변수와 같은 것)을
    // 사용할 수가 없다. 즉, 변수의 멤버변수를 조종할 수가 없다.
    // 멤버 함수 포인터를 사용하면 이것마저 바인딩해서 데이터를 묶어 조종할 수가 있다.
    
    // 함수 객체를 이용하면 데이터를 묶어 관리할 수가 있다.
    // 그래서 이 다음으로 함수 객체를 공부할 것.
}

