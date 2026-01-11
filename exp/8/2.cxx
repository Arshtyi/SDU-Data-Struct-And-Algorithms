#include <iostream>
#include <string>
using namespace std;
template <class T>
struct chainNode
{
    T element;
    chainNode<T> *next;
    chainNode() {}
    chainNode(const T &e) : element(e) {}
    chainNode(const T &e, chainNode<T> *p) : element(e), next(p) {}
};
template <class T>
class chain
{
protected:
    void check_idx(int theIndex) const
    {
        if (theIndex < 0 || theIndex >= listSize)
            throw "Illegal index";
    }
    chainNode<T> *firstNode, *lastNode;
    int listSize;

public:
    chain(int initialCapacity = 10) : firstNode(nullptr), lastNode(nullptr), listSize(0) {}
    ~chain()
    {
        while (firstNode != nullptr)
        {
            chainNode<T> *nextNode = firstNode->next;
            delete firstNode;
            firstNode = nextNode;
        }
    }
    chain(const chain<T> &rhs)
    {
        listSize = rhs.size();
        if (!listSize)
        {
            firstNode = lastNode = nullptr;
            return;
        }
        chainNode<T> *sourceNode = rhs.firstNode;
        firstNode = new chainNode<T>(sourceNode->element);
        sourceNode = sourceNode->next;
        chainNode<T> *targetNode = firstNode;
        while (sourceNode != nullptr)
            targetNode->next = new chainNode<T>(sourceNode->element), targetNode = targetNode->next, sourceNode = sourceNode->next;
        targetNode->next = nullptr;
        lastNode = targetNode;
    }
    chain<T> &operator=(const chain<T> &right)
    {
        if (this != &right)
        {
            chainNode<T> *current = firstNode;
            while (current != nullptr)
            {
                chainNode<T> *nextNode = current->next;
                delete current;
                current = nextNode;
            }
            listSize = right.listSize;
            if (right.firstNode == nullptr)
                firstNode = lastNode = nullptr;
            else
            {
                firstNode = new chainNode<T>(right.firstNode->element);
                chainNode<T> *current = firstNode, *sourceNode = right.firstNode->next;
                while (sourceNode != nullptr)
                    current->next = new chainNode<T>(sourceNode->element), current = current->next, sourceNode = sourceNode->next;
                lastNode = current;
            }
        }
        return *this;
    }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int theIndex) const
    {
        check_idx(theIndex);
        chainNode<T> *currentNode = firstNode;
        for (int i = 0; i < theIndex; ++i)
            currentNode = currentNode->next;
        return currentNode->element;
    }
    int idx_of(const T &theElement) const
    {
        chainNode<T> *currentNode = firstNode;
        int idx = 0;
        for (; currentNode != nullptr && currentNode->element != theElement; ++idx)
            currentNode = currentNode->next;
        if (currentNode == nullptr)
            return -1;
        else
            return idx;
    }
    void erase(int theIndex)
    {
        check_idx(theIndex);
        chainNode<T> *deleteNode;
        if (theIndex == 0)
        {
            deleteNode = firstNode, firstNode = firstNode->next;
            if (firstNode == nullptr)
                lastNode = nullptr;
        }
        else
        {
            chainNode<T> *frontNode = firstNode;
            for (int i = 0; i < theIndex - 1; ++i)
                frontNode = frontNode->next;
            deleteNode = frontNode->next, frontNode->next = deleteNode->next;
            if (frontNode->next == nullptr)
                lastNode = frontNode;
        }
        listSize--;
        delete deleteNode;
    }
    void insert(int theIndex, const T &theElement)
    {
        if (theIndex < 0 || theIndex > listSize)
            throw "Invalid index for insert";
        if (theIndex == 0)
            firstNode = new chainNode<T>(theElement, firstNode);
        else
        {
            chainNode<T> *frontNode = firstNode;
            for (int i = 0; i < theIndex - 1; ++i)
                frontNode = frontNode->next;
            frontNode->next = new chainNode<T>(theElement, frontNode->next);
            if (frontNode->next->next == nullptr)
                lastNode = frontNode->next;
        }
        listSize++;
    }
    void reverse()
    {
        if (firstNode == nullptr || firstNode->next == nullptr)
            return;
        else
        {
            chainNode<T> *p = nullptr, *m = firstNode, *q = firstNode->next;
            while (m != nullptr)
            {
                m->next = p, p = m, m = q;
                if (q != nullptr)
                    q = q->next;
            }
            lastNode = firstNode, firstNode = p;
        }
    }
    void push_back(const T &theElement)
    {
        chainNode<T> *newNode = new chainNode<T>(theElement, nullptr);
        if (firstNode == nullptr)
            firstNode = lastNode = newNode;
        else
            lastNode->next = newNode, lastNode = newNode;
        listSize++;
    }
    void output(ostream &out) const
    {
        for (chainNode<T> *currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next)
            out << currentNode->element << " ";
    }
    class iterator;
    iterator begin() { return iterator(firstNode); }
    iterator end() { return iterator(nullptr); }
    class iterator
    {
    public:
        iterator(chainNode<T> *theNode = nullptr) : node(theNode) {}
        T &operator*() const { return node->element; }
        T &operator->() const { return &node->element; }
        iterator &operator++()
        {
            node = node->next;
            return *this;
        }
        iterator &operator++(int)
        {
            iterator old = *this;
            node = node->next;
            return old;
        }
        bool operator!=(const iterator right) const { return node != right.node; }
        bool operator==(const iterator right) const { return node == right.node; }

    protected:
        chainNode<T> *node;
    };
};
class hashChain
{
private:
    chain<int> *table;
    int D;

public:
    hashChain(int d) : D(d), table(new chain<int>[d]) {}
    ~hashChain() { delete[] table; }
    void hashInsert(int x)
    {
        int hash_value = x % D;
        if (table[hash_value].idx_of(x) != -1)
            cout << "Existed" << endl;
        else
            table[hash_value].push_back(x);
    }
    void hashSearch(int x)
    {
        int hash_value = x % D;
        if (table[hash_value].idx_of(x) == -1)
            cout << "Not Found" << endl;
        else
            cout << table[hash_value].size() << endl;
    }
    void hashDelete(int x)
    {
        int hash_value = x % D;
        if (table[hash_value].idx_of(x) == -1)
            cout << "Delete Failed" << endl;
        else
        {
            int index = table[hash_value].idx_of(x);
            table[hash_value].erase(index);
            cout << table[hash_value].size() << endl;
        }
    }
};
template <class T>
ostream &operator<<(ostream &out, const chain<T> &x)
{
    x.output(out);
    return out;
}
int D, m;
int main()
{
    cin >> D >> m;
    hashChain table(D);
    for (int i = 0; i < m; ++i)
    {
        int op, x;
        cin >> op >> x;
        if (op == 0)
            table.hashInsert(x);
        else if (op == 1)
            table.hashSearch(x);
        else
            table.hashDelete(x);
    }
    return 0;
}
