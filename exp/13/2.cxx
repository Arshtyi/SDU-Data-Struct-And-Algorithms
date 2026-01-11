#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
template <class T>
class arrayList
{
private:
    int arrayLength, listSize;
    T *element;

public:
    arrayList(int initialCapacity = 10) : arrayLength(initialCapacity), listSize(0), element(new T[arrayLength])
    {
        for (int i = 0; i < arrayLength; ++i)
            element[i] = T();
    }
    arrayList(const arrayList<T> &arr) : arrayLength(arr.arrayLength), listSize(arr.listSize), element(new T[arrayLength]) { copy(arr.element, arr.element + listSize, element); }
    ~arrayList() { delete[] element; }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    void check_index(int theIndex) const
    {
        if (theIndex < 0 || theIndex >= listSize)
        {
            ostringstream s;
            s << "index = " << theIndex << "size = " << listSize;
            cout << s.str() << endl;
            exit(0);
        }
    }
    T &get(int theIndex)
    {
        check_index(theIndex);
        return element[theIndex];
    }
    int index_of(const T &theElement) const
    {
        for (int i = 0; i < listSize; ++i)
            if (element[i] == theElement)
                return i;
        return -1;
    }
    void insert(int theIndex, const T &theElement)
    {
        if (listSize == arrayLength)
        {
            arrayLength *= 2;
            T *newElement = new T[arrayLength];
            for (int i = 0; i < listSize; ++i)
                newElement[i] = element[i];
            delete[] element;
            element = newElement;
        }
        if (theIndex == listSize - 1)
            element[listSize++] = theElement;
        else
        {
            copy_backward(element + theIndex, element + listSize, element + listSize + 1);
            element[theIndex] = theElement, listSize++;
        }
    }
    void erase(int theIndex)
    {
        check_index(theIndex);
        copy(element + theIndex + 1, element + listSize, element + theIndex);
        element[--listSize].~T();
    }
    void push_back(const T &theElement)
    {
        if (listSize == arrayLength)
        {
            arrayLength *= 2;
            T *newElement = new T[arrayLength];
            for (int i = 0; i < listSize; ++i)
                newElement[i] = element[i];
            delete[] element;
            element = newElement;
        }
        element[listSize++] = theElement;
    }
    void output(ostream &out) const { copy(element, element + listSize, ostream_iterator<T>(out, " ")); }
    void adjust(int root, int n)
    {
        T tmp = element[root];
        int child = 2 * root + 1;
        while (child < n)
        {
            if (child + 1 < n && element[child] < element[child + 1])
                ++child;
            if (tmp < element[child])
                element[root] = element[child], root = child, child = 2 * root + 1;
            else
                break;
        }
        element[root] = tmp;
    }
    void sort()
    {
        for (int i = listSize / 2 - 1; i >= 0; --i)
            adjust(i, listSize);
        for (int i = listSize - 1; i > 0; --i)
        {
            std::swap(element[0], element[i]);
            adjust(0, i);
        }
    }
    void clear() { listSize = 0; }
    void reset(int length, T value)
    {
        this->clear();
        for (int i = 0; i < length; ++i)
            this->push_back(value);
    }
    T &operator[](int index)
    {
        check_index(index);
        return element[index];
    }
    const T &operator[](int index) const
    {
        check_index(index);
        return element[index];
    }
    T &operator*() { return element[0]; };
    const T &operator*() const { return element[0]; };
    operator T *() { return element; };
    operator const T *() const { return element; };
};
template <class T>
ostream &operator<<(ostream &out, const arrayList<T> &x)
{
    x.output(out);
    return out;
}
const int N = 2e5 + 10;
int ufs[N];
struct edge
{
    int i, j, w;
    bool operator<(const edge &e) const { return w < e.w; }
    edge(int i = 0, int j = 0, int w = 0) : i(i), j(j), w(w) {}
};
int find(int x) { return ufs[x] == x ? x : ufs[x] = find(ufs[x]); }
class graph
{
protected:
    int n, e;
    arrayList<edge> edges;

public:
    graph(int n, int e) : n(n), e(e) {}
    ~graph() {}
    void insertEdge(int i, int j, int weight) { edges.push_back(edge(i, j, weight)); }
    long long kruskal()
    {
        edges.sort();
        long long totalWeight = 0;
        for (int i = 1; i <= n; ++i)
            ufs[i] = i;
        for (int i = 0; i < e; ++i)
        {
            int u = edges[i].i, v = edges[i].j, w = edges[i].w, root_u = find(u), root_v = find(v);
            if (root_u != root_v)
                totalWeight += w, ufs[root_u] = root_v;
        }
        return totalWeight;
    }
};
int n, e;
int main()
{
    cin >> n >> e;
    graph graph(n, e);
    for (int k = 0; k < e; ++k)
    {
        int i, j, w;
        cin >> i >> j >> w;
        graph.insertEdge(i, j, w);
    }
    cout << graph.kruskal() << endl;
    return 0;
}
