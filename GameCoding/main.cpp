#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template<typename T, typename Predicate = less<T>>
class PrioityQueue
{
public:
    // O(log N), 트리의 높이에 의존적이기에 그렇다. 이렇게까지 깊게 알 필요는 없음.
    // 트리의 높이가 커질 때마다 2배의 데이터를 담을 수 있게 되기 때문에 logN
    void push(const T& data)
    {
        // 우선 힙 구조부터 맞춰 준다.
        _heap.push_back(data);

        // 도장 깨기 시작, 맨 뒤에서부터 시작
        int now = static_cast<int>(_heap.size()) - 1;

        // 루트 노드까지
        while ( now > 0 )
        {
            int next = (now - 1) / 2; // 부모 인덱스 공식
            //if (_heap[now] < _heap[next])
                //break; // 반란 실패하면 break로 빠져나오기
            if (_predicate(_heap[now], _heap[next]))
                break;

            // 반란 성공하면 데이터 교체
            ::swap(_heap[now], _heap[next]);
            now = next;
        }
    }

    // O(logN), 얘도 트리의 높이에 따른다.
    void pop()
    {
        _heap[0] = _heap.back(); // _heap.back() < 마지막 데이터를 의미
        _heap.pop_back(); // 데이터를 첫 번째로 옮기고, 마지막 자리는 삭제해 줌

        int now = 0;

        while(true)
        {
            int left = 2 * now + 1;
            int right = 2 * now + 2;

            // 리프에 도달할 경우 (더 내려갈 곳 없으면) break
            if ( left >= (int)_heap.size() )
                break;
            
            int next = now;

            // 왼쪽 비교
            if ( _heap[next] < _heap[left] )
                next = left;
            
            // 둘 중 승자를 오른쪽과 비교
            //if ( right < (int)_heap.size() && _heap[next] < _heap[right] )
            if (right < _heap.size() && _predicate(_heap[next], _heap[right]))
                next = right;

            // 왼쪽/오른쪽 둘 다 현재 값보다 작으면 종료
            if ( next == now )
                break;
            
            ::swap(_heap[now], _heap[next]);
            now = next;
        }
    }

    // O(1)
    T& top()
    {
        return _heap[0];
    }

    // O(1)
    bool empty()
    {
        return _heap.empty();
    }

    void PrintTree()
    {
    }

private:
    vector<T> _heap;    // 데이터를 넣어 줄 곳
    Predicate _predicate;
};

int main()
{
    vector<int> v;
    PrioityQueue<int, greater<int>> pq;
    // less -> 높은 값이 최상단으로 올라가게 해 줌
    // greater -> 작은 값이 최상단으로 올라가게 해 줌

    pq.push(10);
    pq.push(40);
    pq.push(30);
    pq.push(50);
    pq.push(20);
    

    pq.PrintTree();

    int value = pq.top();
    cout << pq.top() << endl;

    // 가장 큰값을 찾아내기 위한 효율적인 방법은?

    // 정렬 - 빠른 퀵 소트도 O(NlogN)
    // 가장 큰 값 스캔 - O(N)
    // [][][][][][][][][][]
    
    // push, pop 모두 log N이다.
    // 베스트 케이스 하나만 추출할 때 우선순위 큐는 진짜 너무나도 좋은 자료구조다.
    // 따라서 그림 그려 보면서 이해하고, 시간복잡도는 잘 알아두기. 구현부는 급한 것 아님.
}
