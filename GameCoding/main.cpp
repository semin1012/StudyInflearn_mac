#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// DFS(depth first search): 깊이 들어가며 정보를 파악하는 것, 깊이 우선

// DFS = 재귀함수
// BFS =

struct Vertex
{
    // int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

// 내가 방문한 목록
vector<bool> visited;

void CreateGraph()
{
    vertices.resize(6);
    
    // 인접 리스트
//    adjacent = vector<vector<int>>(6);
//    adjacent[0] = { 1, 3 };
//    adjacent[1] = { 0, 2, 3 };
//    adjacent[3] = { 4 };
//    adjacent[5] = { 4 };
    
    
    // 인접 행렬
    adjacent = vector<vector<int>>
    {
        {0, 1, 0, 1, 0, 0},
        {1, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0}
    };
}

void Dfs(int here)
{
    // 방문 도작
    visited[here] = true;
    cout << "Visited : " << here << endl;
    
    // 인접한 길을 다 체크해서
// 이건 방향 그래프일 때, 인접리스트일 때 사용
    // E(edge) = 총 개수
    // 인접리스트 -> O(V+E). E가 V 개수 그대로라면 결국 V^2이 될 수 있음.
//    const int size = adjacent[here].size();
//    for ( int i = 0 ; i < size; i++ )
//    {
//        int there = adjacent[here][i];
//        if ( visited[there] == false )
//            Dfs(there);
//    }
    
    
    // 인접 행렬 -> O(V^2) = 정점마다 한 번씩 + for문을 V마다 한 번씩 하기 때문. 행렬 ㅇㅇ
    for ( int there = 0; there < 6; there++)
    {
        // 길은 있는지
        if (adjacent[here][there] == 0)
            continue;
        
        // 아직 방문하지 않은 곳에 한해서 방문
        if ( visited[there] == false )
            Dfs(there);
        // 이렇게 하면 5번은 안 들리고 끝남
        // 4번에서 5번으로 가는 길 자체가 없기 때문에. 그래프의 문제임
        // 그래서 DfsAll()을 따로 만들어서 visited를 다 돌도록 만들어야 한다.
    }
}

// 빽빽할 때는 인접 행렬 쓰면 되고,
// 느슨하다면 인접 리스트를 써야 훨씬 빠름.

void DfsAll()
{
    visited = vector<bool>(6, false);
    
    for (int i = 0 ; i < 6; i++ )
        if (visited[i] == false )
        {
            Dfs(i);
            cout << "Hi" << endl;   // 두 번 호출되고 visited 다 돌아서 끝남
        }
}

int main()
{
    CreateGraph();
    
    DfsAll();
}
