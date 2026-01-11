#include <iostream>
using namespace std;
template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;
    int leftSize;
    binaryTreeNode(const T &theElement) : element(theElement), leftChild(nullptr), rightChild(nullptr), leftSize(0) {}
    binaryTreeNode(const T &theElement, binaryTreeNode<T> *theLeft, binaryTreeNode<T> *theRight, int LeftSize) : element(theElement), leftChild(theLeft), rightChild(theRight), leftSize(LeftSize) {}
};
template <class T>
class indexedBST
{
private:
    int size;
    binaryTreeNode<T> *root;

public:
    indexedBST() : size(0), root(nullptr) {}
    int insert(const T &theElement)
    {
        binaryTreeNode<T> *p = root, *pp = nullptr;
        int sum = 0;
        while (p != nullptr)
        {
            if (p->element < theElement)
                sum ^= p->element, pp = p, p = p->rightChild;
            else if (p->element > theElement)
                sum ^= p->element, pp = p, p = p->leftChild;
            else
                return 0;
        }
        binaryTreeNode<T> *newNode = new binaryTreeNode<T>(theElement);
        if (pp == nullptr)
            root = newNode;
        else
        {
            if (theElement > pp->element)
                pp->rightChild = newNode;
            else if (theElement < pp->element)
                pp->leftChild = newNode;
        }
        ++size, p = root;
        while (p->element != theElement)
            if (p->element < theElement)
                p = p->rightChild;
            else if (p->element > theElement)
                p->leftSize++, p = p->leftChild;
        return sum;
    }
    int find(const T &theElement)
    {
        binaryTreeNode<T> *p = root;
        int sum = 0;
        while (p != nullptr && p->element != theElement)
        {
            sum ^= p->element;
            if (p->element > theElement)
                p = p->leftChild;
            else if (p->element < theElement)
                p = p->rightChild;
        }
        if (p == nullptr)
            return 0;
        sum ^= p->element;
        return sum;
    }
    int erase(const T &theElement)
    {
        binaryTreeNode<T> *p = root, *pp = nullptr;
        int sum = 0;
        while (p != nullptr && p->element != theElement)
        {
            sum ^= p->element, pp = p;
            if (p->element > theElement)
                p = p->leftChild;
            else if (p->element < theElement)
                p = p->rightChild;
        }
        if (p == nullptr)
            return 0;
        sum ^= p->element, p = root;
        while (p != nullptr && p->element != theElement)
            if (p->element < theElement)
                p = p->rightChild;
            else if (p->element > theElement)
                p->leftSize--, p = p->leftChild;
        if (p->leftChild != nullptr && p->rightChild != nullptr)
        {
            binaryTreeNode<T> *min_right = p->rightChild, *delete_r = p;
            while (min_right->leftChild != nullptr)
                min_right->leftSize--, delete_r = min_right, min_right = min_right->leftChild;
            binaryTreeNode<T> *newNode = new binaryTreeNode<T>(min_right->element, p->leftChild, p->rightChild, p->leftSize);
            if (pp == nullptr)
                root = newNode;
            else if (p == pp->leftChild)
                pp->leftChild = newNode;
            else
                pp->rightChild = newNode;
            if (delete_r == p)
                pp = newNode;
            else
                pp = delete_r;
            delete p;
            p = min_right;
        }
        binaryTreeNode<T> *c;
        if (p->leftChild != nullptr)
            c = p->leftChild;
        else
            c = p->rightChild;
        if (p == root)
            root = c;
        else
        {
            if (p == pp->leftChild)
                pp->leftChild = c;
            else
                pp->rightChild = c;
        }
        size--;
        delete p;
        return sum;
    }
    int findByIndex(int a)
    {
        binaryTreeNode<T> *p = root;
        int sum = 0;
        while (p != nullptr && p->leftSize != a)
        {
            sum ^= p->element;
            if (p->leftSize > a)
                p = p->leftChild;
            else
                a = a - p->leftSize - 1, p = p->rightChild;
        }
        if (p == nullptr)
            return 0;
        sum ^= p->element;
        return sum;
    }
    int deleteByIndex(int a)
    {
        binaryTreeNode<T> *p = root;
        int sum = 0;
        while (p != nullptr && p->leftSize != a)
        {
            sum ^= p->element;
            if (p->leftSize > a)
                p = p->leftChild;
            else if (p->leftSize < a)
                a = a - p->leftSize - 1, p = p->rightChild;
        }
        if (p == nullptr)
            return 0;
        sum ^= p->element;
        int theElement = p->element;
        this->erase(theElement);
        return sum;
    }
};
int m, op, param;
indexedBST<int> bsTree;
int main()
{
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> op >> param;
        if (op == 0)
            cout << bsTree.insert(param) << endl;
        else if (op == 1)
            cout << bsTree.find(param) << endl;
        else if (op == 2)
            cout << bsTree.erase(param) << endl;
        else if (op == 3)
            cout << bsTree.findByIndex(--param) << endl;
        else if (op == 4)
            cout << bsTree.deleteByIndex(--param) << endl;
    }
    return 0;
}
