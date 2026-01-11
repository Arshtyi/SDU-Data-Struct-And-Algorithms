#include <iostream>
#include <cstdio>

class Chain
{
private:
    struct Node
    {
        int data;
        Node *next;
        Node() : data(0), next(nullptr) {}
        Node(int x) : data(x), next(nullptr) {}
    };

    Node *head;
    Node *tail; // 尾指针，优化pushBack

    static Node *mergeSortRec(Node *head);                      // 归并排序递归主过程
    static Node *merge(Node *a, Node *b);                       // 合并两个有序链表
    static void split(Node *source, Node *&front, Node *&back); // 链表拆分

public:
    Chain() : head(nullptr), tail(nullptr) {}

    void pushBack(int x)
    {
        Node *node = new Node(x);

        if (!head)
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
    }

    void mergeSort()
    {
        head = mergeSortRec(head);
    }

    void print() const
    {
        Node *cur = head;
        bool first = true;
        while (cur)
        {
            if (!first)
                printf(" ");
            printf("%d", cur->data);
            first = false;
            cur = cur->next;
        }
        printf("\n");
    }
};

// ====================== 主函数 ======================
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    scanf("%d", &n);

    Chain chain;
    for (int i = 0; i < n; ++i)
    {
        int x;
        scanf("%d", &x);
        chain.pushBack(x);
    }

    chain.mergeSort();
    chain.print();

    return 0;
}

Chain::Node *Chain::mergeSortRec(Node *head)
{
    if (!head || !head->next)
        return head;
    Node *front, *back;
    split(head, front, back);
    front = mergeSortRec(front), back = mergeSortRec(back);
    return merge(front, back);
}

Chain::Node *Chain::merge(Node *a, Node *b)
{
    Node *dummy = new Node(), *tail = dummy;
    while (a && b)
    {
        if (a->data <= b->data)
            tail->next = a, a = a->next;
        else
            tail->next = b, b = b->next;
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy->next;
}

void Chain::split(Node *source, Node *&front, Node *&back)
{
    if (!source || !source->next)
    {
        front = source, back = nullptr;
        return;
    }
    Node *slow = source, *fast = source->next;
    while (fast)
    {
        fast = fast->next;
        if (fast)
            slow = slow->next, fast = fast->next;
    }
    front = source, back = slow->next, slow->next = nullptr;
}
