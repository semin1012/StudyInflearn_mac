#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 정점이 100개
// - 지하철 노선도 -> 서로 드문드문 연결됨
// - 페이스북 친구 -> 서로 빽빽하게 연결됨

// 드문드문 연결되어 있으면 인접리스트가 유리하다. 연결된 애들만 넣어주면 되니까
// 빽빽하게 연결되어 있을 경우에는 인접리스트 불리, 인접행렬이 유리하다.
//      -> 인접행렬은 메모리 소모가 심한데 어차피 다 연결되어 값이 차있다면 인접행렬이 유리. 접근도 빠름.

// 가장 직관적인 Vertex 방법이지만, 이것은 연결되었는지 여부를 확인하기 어려워서 사용 안 한다.
void CreateGraph_1()
{
    struct Vertex
    {
        // int data;
        vector<Vertex*> edges;
    };
    
    //vector<int> v2(10, -1); // v2(데이터 개수, 초기값)
    //vector<int> v3{1,2,3,4,5,6,7}; // 1,2,3,... 데이터 넣기
    
    vector<Vertex> v; // vector<Vertex> v(6)으로 만들어도 됨
    //v.resize(6);    // size, 실제로 이 크기의 데이터가 들어간다
    v.reserve(6);   // capacity, 데이터는 없지만 영역 확보
    
    v[0].edges.push_back(&v[1]);
    v[0].edges.push_back(&v[3]);
    v[1].edges.push_back(&v[0]);
    v[1].edges.push_back(&v[2]);
    v[1].edges.push_back(&v[3]);
    v[3].edges.push_back(&v[4]);
    v[5].edges.push_back(&v[4]);
    
    // Q) 0번->3번이 연결되어 있나요? -> 확인할 수는 있지만 확인하기 어려움
    bool connected = false;
    
    int size = v[0].edges.size();
    for (int i = 0; i< size; i++)
    {
        Vertex* vertex = v[0].edges[i];
        if ( vertex == &v[3])
        {
            connected = true;
        }
    }
}


// 인접 리스트: 실제 연결된 애들'만' 넣어준다.
void CreateGraph_2()
{
    struct Vertex
    {
        int data;
    };
    
    vector<Vertex> v(6);    // 버텍스는 여기에서 관리
    
    vector<vector<int>> adjacent; // 동적 배열 안에 동적 배열이 있다.
    adjacent.resize(6);
    // 연결된 애들을 따로 관리하기 때문에 인접 리스트라고 부른다.
    adjacent[0] = {1, 3};
    adjacent[1] = {0, 2, 3};
    adjacent[3] = {4};
    adjacent[5] = {4};
    
    // Q) 0번->3번 연결되어 있나요?
    bool connected = false;
    
    int size = adjacent[0].size();
    for ( int i = 0 ; i < size; i++ )
    {
        int vertex = adjacent[0][i];    // 0번을 다 돌아서
        if ( vertex == 3 )      // 3번이 있다면 true
            connected = true;
    }
}

// 인접 행렬
void CreateGraph_3()
{
    struct Vertex
    {
        int data;
    };
    
    vector<Vertex> v(6);    // 버텍스는 여기에서 관리
    
    // 연결된 목록을 행렬로 관리
    // 2차원 행렬로 관리하는 것
    // [x][o][x][o][x][x]
    // [o][x][o][o][x][x]
    // [x][x][x][x][o][x]
    // [x][x][x][x][x][x]
    // [x][x][x][x][o][x]
    
    // 6개 행을 만들고, 각각 행 안에 6개의 false 열을 다 넣음
    vector<vector<bool>> adjacent(6, vector<bool>(6, false));
    // adjacent[from][to] ?
    // 행렬을 이용한 그래프 표현
    // 메모리 소모 심하지만, 빠른 접근
    adjacent[0][1] = true;
    adjacent[0][3] = true;
    adjacent[1][0] = true;
    adjacent[1][2] = true;
    adjacent[1][3] = true;
    adjacent[3][4] = true;
    adjacent[5][4] = true;
    
    // Q) 0번->3번 연결되어 있나요?
    bool connected = adjacent[0][3];
    
    // 가중치를 표현하려면?
    vector<vector<int>> adjacent2 =
    {
        {-1, 15, -1, 35, -1, -1},
        {15, -1, +5, 10, -1, -1},
        {-1, +5, -1, -1, -1, -1},
        {35, 10, -1, -1, +5, -1},
        {-1, -1, -1, +5, -1, +5},
        {-1, -1, -1, -1, +5, -1}
    };
}

int main()
{
    vector<int> v;
    
    // 방향이 있으면 재귀함수로 모두 순회 가능
    // 가중치만 있으면 사이클이 일어날 수 있기에 재귀함수 순회 불가능
}
