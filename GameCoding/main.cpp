#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void Print()
{
    cout << "Hello World" << endl;
}

int Add(int a, int b)
{
    return a + b;
}

// 콜백 함수
// - ex) UI
// - ex) 온라인 게임
// - ex) 키보드 입력

using FuncPtrType = int(*)(int a, int b);
int DoSometing(int a, int b, FuncPtrType func)
{
    return func(a, b);
}

void Fire()
{
    cout << "공격" << endl;
}

class Item
{
public:
    
public:
    int _itemId = 0;
    int _rarity = 0;
    int _ownerId = 0;
};

using ItemSelectorType = bool(*)(Item* item);
Item* FindItem(Item items[], int itemCount, ItemSelectorType selector)
{
    for ( int i = 0 ; i < itemCount ; i++ )
    {
        Item* item = &items[i];
        if (selector(item))
            return item;
    }
    
    return nullptr;
}

bool IsRare(Item* item)
{
    return item->_rarity == 1;
}

int main()
{
    // 함수 객체, 함수 펑션이 greater, less다.
    //priority_queue<int, vector<int>, greater<int>> pq;
    
    int a = 10;
    //typedef int DataType;
    using DataType = int;   // 위와 같은 뜻
    // DataType* ptr = &a;
    
    // 포인터: 이것을 타고 가면 무엇이 있는지 주장하는 것
    // 함수도 포인터를 들고 있을 수 있다는 것이 오늘의 주제다.
    
    //typedef void FuncType();      // << 옛날 방식
    using FuncType = void();    // << 현대 방식
    // 함수는 함수인데 보이드를 뱉어내고 보이드를 받아주는 FuncType이라는 뜻
    
    FuncType* ptr = &Print;     // FuncType에 함수 포인터를 넣을 수가 있게 된다
    
    ptr();
    // 함수를 막 호출하는 것이 아니라 함수의 주소를 가지고 부른다는 의미다.
    
    //-----------------------------------------------------------------
    
    // ptr = &add; // << 이건 안 된다.
    // 왜냐하면 FuncType형은 void를 받아 void를 뱉어나는 사용자 자료형인데 형이 다름
    
    using FuncType2 = int(int, int);
    FuncType2* ptr2 = &Add;
    
    ptr2(10, 20);   // << 이제 형식이 맞아서 가능
    
    //-----------------------------------------------------------------
    // 사실 위의 함수 포인터들 정말 안 씀. 있는 줄도 모르는 사람 많다
    // 그래서 밑에처럼 쓴다.
    
    // void(*FuncPtrType)();        // << 옛날 문법
    //using FuncPtrType = void(*)();  // << 현대 문법
    // 보이드를 받고, 보이드를 뱉는 함수 포인터라는 뜻
    
    //FuncPtrType ptr3 = &Print;
    //ptr3();
    
    
    
    
    
    // !!!!!! 대체 왜 이 짓거리를 하는가? 어떤 의미길래? !!!!!!
    // 생각보다 유용할 때가 많다.
    // - 콜백, 비동기 상황 등
    // '행동' 자체를 인자로 넘기고 싶을 때 << DoSomething과 같이 만든다
    DoSometing(10, 20, &Add);
    DoSometing(10, 20, [](int a, int b) { return a - b;});
    // 이처럼 정말 다양하게 사용할 수가 있다.
    
    
    // 키보드 조작 시 사용
    using OnClickKeyboard = void(*)();
    OnClickKeyboard gSkill = &Fire;
    // if ( Q버튼을 눌렀으면)
    //  gSkill()
    
    
    // 인벤토리 상황
    Item items[10];
    items[3]._rarity = 1;   // RARE
    
    // IsRare 같은 함수를 조건으로 넣을 수가 있다. 다양한 조건 넣어서 만들 수 있다. 
    FindItem(items, 10, IsRare);
    
}

