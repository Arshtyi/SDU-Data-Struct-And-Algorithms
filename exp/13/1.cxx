#include <iostream>
#include <climits>
using namespace std;
template <class T>
class minHeap
{
private:
    int arrayLength, heapSize;
    T *heap;

public:
    minHeap(int initialCapacity = 10) : arrayLength(initialCapacity + 1), heapSize(0), heap(new T[arrayLength]) {}
    ~minHeap() { delete[] heap; }
    int size() const { return heapSize; }
    bool empty() const { return heapSize == 0; }
    void initialize(T *theHeap, int n)
    {
        delete[] heap;
        heap = new T[n + 1];
        heap[0] = T();
        for (int i = 1; i <= n; ++i)
            heap[i] = theHeap[i];
        arrayLength = n + 1, heapSize = n;
        for (int root = heapSize / 2; root >= 1; --root)
        {
            T rootElement = heap[root];
            int child = 2 * root;
            while (child <= heapSize)
            {
                if (child < heapSize && heap[child] > heap[child + 1])
                    child++;
                if (rootElement <= heap[child])
                    break;
                heap[child / 2] = heap[child], child *= 2;
            }
            heap[child / 2] = rootElement;
        }
    }
    void push(const T &theElement)
    {
        if (heapSize == arrayLength - 1)
        {
            arrayLength *= 2;
            T *newHeap = new T[arrayLength];
            for (int i = 1; i <= heapSize; ++i)
                newHeap[i] = heap[i];
            delete[] heap;
            heap = newHeap;
        }
        int currentNode = ++heapSize;
        while (currentNode != 1 && heap[currentNode / 2] > theElement)
            heap[currentNode] = heap[currentNode / 2], currentNode /= 2;
        heap[currentNode] = theElement;
    }
    T &top() const
    {
        if (heapSize == 0)
            throw runtime_error("Heap is empty!");
        return heap[1];
    }
    T pop()
    {
        if (heapSize == 0)
            throw runtime_error("Heap is empty!");
        T minElement = heap[1], lastElement = heap[heapSize--];
        int currentNode = 1, child = 2;
        while (child <= heapSize)
        {
            if (child < heapSize && heap[child] > heap[child + 1])
                child++;
            if (lastElement <= heap[child])
                break;
            heap[currentNode] = heap[child], currentNode = child, child *= 2;
        }
        heap[currentNode] = lastElement;
        return minElement;
    }
};
struct graphNode
{
    graphNode *next;
    int element, weight;
    graphNode(int e, graphNode *node, int w) : element(e), next(node), weight(w) {}
};
struct graphChain
{
    graphNode *st, *ed;
};
struct heapNode
{
    int node, key;
    heapNode(int n = 0, int k = 0) : node(n), key(k) {}
    bool operator>(const heapNode &other) const { return key > other.key || (key == other.key && node > other.node); }
    bool operator<=(const heapNode &other) const { return !(*this > other); }
};
class linkedGraph
{
protected:
    int n, e;
    graphChain *aList;

public:
    linkedGraph(int num = 0) : n(num), e(0), aList(new graphChain[num + 1])
    {
        for (int i = 0; i <= n; ++i)
            aList[i].st = nullptr;
    }
    ~linkedGraph()
    {
        if (aList)
        {
            for (int i = 0; i <= n; ++i)
            {
                graphNode *p = aList[i].st;
                while (p != nullptr)
                {
                    graphNode *q = p->next;
                    delete p;
                    p = q;
                }
                aList[i].st = aList[i].ed = nullptr;
            }
            delete[] aList;
            aList = nullptr;
        }
    }
    void insertEdge(int i, int j, int weight)
    {
        if (aList[i].st == nullptr)
            aList[i].st = aList[i].ed = new graphNode(j, nullptr, weight);
        else
            aList[i].ed->next = new graphNode(j, nullptr, weight), aList[i].ed = aList[i].ed->next;
        if (aList[j].st == nullptr)
            aList[j].st = aList[j].ed = new graphNode(i, nullptr, weight);
        else
            aList[j].ed->next = new graphNode(i, nullptr, weight), aList[j].ed = aList[j].ed->next;
    }
    long long prim()
    {
        long long totalWeight = 0;
        int *dist = new int[n + 1];
        bool *vis = new bool[n + 1];
        fill(dist, dist + n + 1, INT_MAX), fill(vis, vis + n + 1, false);
        dist[1] = 0;
        minHeap<heapNode> heap(n);
        heap.push(heapNode(1, 0));
        while (!heap.empty())
        {
            heapNode tmp = heap.pop();
            int v = tmp.node, weight = tmp.key;
            if (vis[v])
                continue;
            vis[v] = true;
            totalWeight += weight;
            for (graphNode *tmp = aList[v].st; tmp != nullptr; tmp = tmp->next)
            {
                int j = tmp->element;
                if (!vis[j] && dist[j] > tmp->weight)
                    dist[j] = tmp->weight, heap.push(heapNode(j, dist[j]));
            }
        }
        delete[] dist;
        delete[] vis;
        return totalWeight;
    }
};
int n, e;
int main()
{
    cin >> n >> e;
    linkedGraph graph(n);
    for (int k = 0; k < e; ++k)
    {
        int i, j, w;
        cin >> i >> j >> w;
        graph.insertEdge(i, j, w);
    }
    cout << graph.prim() << endl;
    return 0;
}
