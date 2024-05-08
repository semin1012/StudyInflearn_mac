#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// DFS(depth first search): 깊이 들어가며 정보를 파악하는 것, 깊이 우선
// DFS = 재귀함수 = 스택

// BFS (breath first search): 너비 우선 탐색.
// BFS = 큐 (먼저 접근한 것은 먼저 처리)

struct Vertex
{
    // int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

// 내가 방문한 목록 -> DFS일 때
vector<bool> visited;

// 내가 발견한 목록 -> BFS일 때
vector<bool> discovered;

void CreateGraph()
{
    vertices.resize(6);
    
    // 인접 리스트
    adjacent = vector<vector<int>>(6);
    adjacent[0] = { 1, 3 };
    adjacent[1] = { 0, 2, 3 };
    adjacent[3] = { 4 };
    adjacent[5] = { 4 };
    
    
    // 인접 행렬
//    adjacent = vector<vector<int>>
//    {
//        {0, 1, 0, 1, 0, 0},
//        {1, 0, 1, 1, 0, 0},
//        {0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 1, 0},
//        {0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 1, 0}
//    };
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

void Bfs(int here)
{
    // 아무 곳이나 들어가는 방식
    // 입구에서 얼마나 떨어져 있는지. 가까이 있는 곳부터 접근을 하겠다.
    // 쉽게 말해서 발견한 순서대로 접근하면 되는 것이다.
    
    // ex) 누구에 의해서 발견되었는지?
    vector<int> parent(6, -1);
    
    // ex) 시작점에서 얼만큼 떨어져 있는지?
    vector<int> dist(6, -1);
    
    queue<int> q;
    q.push(here);   // 예약 시스템
    discovered[here] = true;  // 발견한 곳인지
    // ex)에 관한 변수
    parent[here] = here;
    dist[here] = 0; // 거리
    
    
    while (q.empty() == false) // 새롭게 지점을 발견하지 못 할 때까지
    {
        // 처음에는 넣자마자 빼는 것처럼 보이지만 다음 턴에서는 새롭게 발견된 애들이 추가됨
        here = q.front();
        q.pop();
        
        // 방문 도장
        cout << "Visited: " << here << endl;
        
        // 인접한 애들 찾아주기, 인접 리스트로 만들었을 경우의 코드!
        int size = adjacent[here].size();
        for ( int i = 0; i < size; i++ )
        {
            int there = adjacent[here][i];
            if ( discovered[there]) // 이미 다른 경로를 통해 발견한 곳이라면
                continue;   // 넘어가기
            
            // 새롭게 발견된 곳이라면 예약해 주기
            q.push(there);
            // q에 새롭게 추가되었기 때문에 while문이 안 끝나고 더 돌게 됨
            discovered[there] = true;
            
            // ex)에 관한 코드
            parent[there] = here;
            // 여기까지 접근하는 데 here만큼 걸린 것에 +1을 하는 것
            dist[there] = dist[here] +1;
            
            cout << "there: " << there << "  parent: " << parent[there] << "  dist: " << dist[there] << endl;
        }
        
        // 인접 행렬일 경우의 코드!
//        for ( int there = 0; there < 6; there++ )
//        {
//            if ( adjacent[here][there] == 0 ) // 값 존재하지 않는다면
//                continue;
//            if ( discovered[there] == true )
//                continue;
//            // 밑에 부분은 인접리스트나, 인접행렬이나 똑같음
//            q.push(there);
//            discovered[there] = true;
//        }
    }
}

void BfsAll()
{
    discovered = vector<bool>(6, false);
    
    for ( int i = 0 ; i < 6; i++ )
        if (discovered[i] == false )
            Bfs(i);
        // 아직 못 찾은 숫자의 너비가 있다면 (0~5까지의 숫자 존재하기 때문에 6 숫자 넣음)
        // Bfs(i) 함수 실행
}

int main()
{
    CreateGraph();
    
    discovered = vector<bool>(6, false);
    
    BfsAll();
    // 너비 우선이기 때문에 가까운 애들부터 탐색한다는 특징이 있다.
    // Bfs랑 길찾기랑 무슨 상관이 있는가?
    // Bfs의 순서가 최단거리라는 것이 보장이 되는가?
    // -> Bfs로 찾은 최단거리보다 짧은 거리 찾을 수 없음. 순차적으로 몇 번째로 먼 건지 보기 때문에 더 빠른 경로가 나올 수 없다. 먼저 찾아지는 경로가 최단 거리임 ㅇㅇ. 따라서 최단경로를 찾음.
    // 대신 Dfs는 처음에 찾아지는 경로가 최단 거리인 건 아니지만, 검색 대상의 그래프가 정말 크다면 Dfs를 고려한다. 또한 경로에 저장해야 할 특징이 있을 때 사용한다.
    
}
