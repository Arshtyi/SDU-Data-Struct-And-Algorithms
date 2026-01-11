#include <bits/stdc++.h>
template <class T>
struct node
{
    T cur;
    node<T> *next;
    node(T val, node<T> *n = nullptr) : cur(val), next(n) {}
};
template <class T>
class chain
{
private:
    node<T> *head, *tail;
    int listSize;
    void check_idx(int theIndex) const
    {
        if (theIndex < 0 || theIndex >= listSize)
            throw "Index out of range";
    }

public:
    chain(const int initialCapacity = 10)
    {
        if (initialCapacity < 1)
            throw "Initial capacity must be > 0";
        head = tail = nullptr;
        listSize = 0;
    }
    chain(const chain<T> &rhs)
    {
        listSize = rhs.listSize;
        if (!listSize)
        {
            head = tail = nullptr;
            return;
        }
        node<T> *sourceNode = rhs.head;
        head = new node<T>(sourceNode->cur);
        sourceNode = sourceNode->next;
        node<T> *targetNode = head;
        while (sourceNode)
        {
            targetNode->next = new node<T>(sourceNode->cur);
            targetNode = targetNode->next;
            sourceNode = sourceNode->next;
        }
    }
    ~chain()
    {
        while (head)
        {
            node<T> *nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int theIndex) const
    {
        check_idx(theIndex);
        node<T> *currentNode = head;
        for (int i = 0; i < theIndex; ++i)
            currentNode = currentNode->next;
        return currentNode->cur;
    }
    int idx_of(const T &theElement) const
    {
        node<T> *currentNode = head;
        int index = 0;
        while (currentNode)
        {
            if (currentNode->cur == theElement)
                return index;
            currentNode = currentNode->next;
            ++index;
        }
        return -1;
    }
    void erase(int theIndex)
    {
        check_idx(theIndex);
        node<T> *deleteNode;
        if (theIndex == 0)
        {
            deleteNode = head;
            head = head->next;
            if (listSize == 1)
                tail = nullptr;
        }
        else
        {
            node<T> *currentNode = head;
            for (int i = 0; i < theIndex - 1; ++i)
                currentNode = currentNode->next;
            deleteNode = currentNode->next;
            currentNode->next = currentNode->next->next;
            if (theIndex == listSize - 1)
                tail = currentNode;
        }
        delete deleteNode;
        --listSize;
    }
    void insert(int theIndex, const T &theElement)
    {
        if (theIndex < 0 || theIndex > listSize)
            throw "Index out of range";
        if (theIndex == 0)
        {
            head = new node<T>(theElement, head);
            if (listSize == 0)
                tail = head;
        }
        else
        {
            node<T> *currentNode = head;
            for (int i = 0; i < theIndex - 1; ++i)
                currentNode = currentNode->next;
            currentNode->next = new node<T>(theElement, currentNode->next);
            if (theIndex == listSize)
                tail = currentNode->next;
        }
        ++listSize;
    }
    void push_back(const T &theElement)
    {
        node<T> *newNode = new node<T>(theElement);
        if (listSize == 0)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        ++listSize;
    }
    void set(int theIndex, T &theElement)
    {
        check_idx(theIndex);
        chain<T>::iterator it = this->begin();
        for (int i = 0; i < theIndex; ++i, ++it)
            ;
        *it = theElement;
    }
    void reverse()
    {
        if (head == NULL || head->next == NULL)
            return;
        else
        {
            node<T> *p = NULL, *m = head, *q = head->next;
            while (m != NULL)
            {
                m->next = p;
                p = m;
                m = q;
                if (q != NULL)
                    q = q->next;
            }
            tail = head;
            head = p;
        }
    }
    void output(std::ostream &out) const
    {
        node<T> *currentNode = head;
        while (currentNode)
        {
            out << currentNode->cur << " ";
            currentNode = currentNode->next;
        }
    }
    class iterator
    {
    private:
        node<T> *node;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        iterator(node<T> *theNode = NULL) : node(theNode) {}
        T &operator*() const { return node->cur; }
        T &operator->() const { return &node->cur; }
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
    };
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
};
template <class T>
void meld(chain<T> &a, chain<T> &b, chain<T> &c)
{
    chain<int>::iterator ap = a.begin(), bp = b.begin(), cp = c.begin();
    while (ap != NULL || bp != NULL)
    {
        if (ap != NULL)
        {
            c.push_back(*ap);
            ap++;
        }
        if (bp != NULL)
        {
            c.push_back(*bp);
            bp++;
        }
    }
}
signed main()
{
    chain<int> a, b, c;
    for (int i = 0; i < 5; i++)
    {
        a.push_back(i);
        b.push_back(i + 5);
    }
    a.erase(4);
    a.erase(3);
    meld(a, b, c);
    c.output(std::cout);
    std::cout << std::endl;
    return 0;
}
