#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>

enum class ObjectType
{
    Player,
    Monster,
    Projectile,
    Env
};


class Object
{
public:
    Object(ObjectType type) : _type(type) { }
    
    virtual ~Object() { }
    
    // start
    virtual void Init()
    {
        
    }
    
    // update
    virtual void Update()
    {
        
    }
    
public:
    ObjectType GetObjectType() { return _type; }
    
    int _id;
    ObjectType _type;
};


class Player : public Object
{
public:
    Player() : Object(ObjectType::Player) { }
    Player(int id) : Object(ObjectType::Player) { }
};


class Monster : public Object
{
public:
    Monster() : Object(ObjectType::Monster) { }
};


class Projectile : public Object
{
public:
    Projectile() : Object(ObjectType::Projectile) { }
};


class Env : public Object  // 채집물
{
public:
    Env() : Object(ObjectType::Env) { }
};

class Field
{
public:
    // 필드가 하나라면? 싱글톤
    static Field* GetInstance()
    {
        static Field field;
        return &field;
    }
    
    void Update()
    {
        for ( auto& item : _objects)
        {
            Object* obj = item.second;
            obj->Update();
        }
    }
    
    void Add(Object* player)
    {
        _objects.insert(make_pair(player->_id, player));
    }
    
    void Remove(int id)
    {
        _objects.erase(id);
    }
    
    Object* Get(int id)
    {
        auto findId = _objects.find(id);
        if ( findId != _objects.end() )
            return findId->second;
        return nullptr;
    }
    
private:
    // vector?
    // list?
    // map?
    // hash_map?
    //unordered_map<int, Player*> _players;
    //unordered_map<int, Monster*> _monsters;
    //unordered_map<int, Projectile*> _projectiles;
    //unordered_map<int, Env*> _env;
    // 위의 것들을 objects로 통일
    unordered_map<int, Object*> _objects;
};

int main()
{
    int* ptr = new int[5];
    delete[] ptr;
    // 몇개 칸인지 어떻게 알고 삭제를 하는가?
    // HEAP [header(32, 5)][]
    // HEAP 메모리 할당되는 곳 바로 뒤에 헤더가 붙어 있다. 헤더에 사이즈랑 데이터 정보가 적혀 있음.
    // 이걸 이용해서 딜리트할 때도 판별해서 삭제하는 것이라 보면 된다.
    
    
//    Player* p = new Player();
//    delete p; // 가상함수 소멸자 안 해 둬도 아무 문제 없음
    
//    Object* o = new Player();
//    delete o;   // 가상함수 소멸자 해야만 문제가 없음
                  //    메모리 릭 발생
    
    Field::GetInstance()->Add(new Player(1));
    
    Object* obj = Field::GetInstance()->Get(1);
    if ( obj && obj->GetObjectType() == ObjectType::Player )
    {
        // 이렇게 dynamic_cast 안 쓰고 관리하는 방법도 있다.
        Player* player = static_cast<Player*>(obj);
    }
     
//     dynamic_cast = cast가 안 되면 nullptr 을 리턴
//    Player* player = dynamic_cast<Player*>(Field::GetInstance()->Get(1));
    
//    if ( player )
//    {
//        
//    }
}
