#import "@preview/ezexam:0.2.7": *
#import "@preview/cetz:0.4.2": canvas, draw, tree
#import "@preview/fletcher:0.5.8" as fletcher: diagram, edge, node

#set document(
    title: "山东大学计算机科学与技术学院24数据、智能班数据结构期末",
    author: "Arshtyi",
    date: datetime.today(),
)

#show: setup.with(
    mode: EXAM,
)

#show link: it => {
    set text(fill: blue)
    underline(it)
}

#title[
    山东大学计算机科学与技术学院

    24数据、智能班数据结构与算法期末试题
]

#notice(
    [出于方便使用#link("https://github.com/gbchu/ezexam", "gbcnu/ezexam:0.2.7")作模板.],
    [源码:#link("https://github.com/Arshtyi/SDU-Data-Struct-And-Algorithms").],
)

= 线性
#question[
    设入栈序列$A,B,C,D,E,F$,求有哪几个出栈序列满足$C$第一个出栈且$D$第二个出栈？
]
#question[
    现在欲将序列$11,20,33,43,86,99,107$升序排列.
    + 若使用及时终止的选择排序,使用什么样的初始序列能使得排序所需比较次数最少?给出这种情况和所需比较次数.
    + 若对(1)中初始序列使用快速排序,时间复杂度是多少?
]
#question[
    使用$0$base的size为$10$的数组实现循环队列,front指向队头元素,rear指向队尾元素的下一个位置.某个时刻,$"front"=7,"rear"=3$.
    + 如何判断队列为空和满足?
    + 此时队列中有多少个元素?
    + $0$base下,第$k$个元素的$"idx"(k)$表达式.
]
#question[
    哈希函数$h(k)=k % 11$,采用线性探测法插入序列$1,13,12,34,38,33,27,22$.
    + 画出哈希表,并给出每次插入的冲突次数.
    + 查找成功和不成功的平均查找桶数.
]
#question[
    补全代码将一个带有头结点的单链表原地逆置
    ```cpp
    void reverseList(Node* head){
        Node *pre = nullptr,cur = head->next, *nxt = nullptr;
        while(cur!= nullptr){
            1;
            2;
            3;
            4;
        }
        5;
    }
    ```
]
= 树
#question[
    一棵完全二叉树,没有度为$1$的节点,共有$83$个节点
    + 有多少个叶节点?
    + 树的高度是多少?(根节点高度为$1$)
]
#question[
    已知一棵二叉树的
    - 中序遍历: D B E A F C
    - 后序遍历: D E B F C A
    + 画出该二叉树.
    + 求该二叉树的先序遍历.
    + 求该二叉树的层序遍历.
]
#question[
    设序列$30,15,45,10,20,40,50$
    + 依次插入索引二叉树,标出每个节点的leftSize.
    + $20$和$45$的rank.
    + 删除$15$后,画出该树并标出新的leftSize.
]
#question[
    完全二叉树以层次遍历序列存储于$A[1..15]$
    + 给出$A[6]$的父节点、左孩子、右孩子的下标.
    + 给出所有叶节点的下标.
    + 求删除$A[4]$及其子树后,剩下多少个节点?
]
#question[
    一棵$3$阶$B$-树如下,画出经过下列操作后的$B$-树:
    #canvas({
        import draw: *

        set-style(content: (padding: 0.5em))
        tree.tree(
            (
                [$60$],
                ([$20$], [$3 space.en 10$], [$35 space.en 40$]),
                ([$80$], [$70$], [$100$]),
            ),
        )
    })
    + 插入$72$
    + 插入$70$
    + 删除$70$
]
= 图
#question[
    + 无向图$G$共有$25$条边,其中度数为$4$的节点有$5$个,度数为$3$的节点有$4$个,其余节点度数均为$2$.求$G$中有多少个节点?
    + 非连通无向图$G$有$21$条边,则至少有多少个节点?
]
#question[
    给出图如下
    #let data = (
        [$6$],
        ([$4$], [$1$], ([$2$], [$3$])),
        [$5$],
    )
    #canvas({
        import draw: *

        set-style(content: (padding: .2), fill: gray.lighten(70%), stroke: gray.lighten(70%))

        tree.tree(
            data,
            spread: 2.5,
            grow: 1.5,
            draw-node: (node, ..) => {
                circle((), radius: .45, stroke: none)
                content((), node.content)
            },
            draw-edge: (from, to, ..) => {
                line((a: from, number: .6, b: to), (a: to, number: .6, b: from), mark: (end: ">"))
            },
            name: "tree",
        )
        let (a, b) = ("tree.0-0", "tree.0-1")
        line((a, .6, b), (b, .6, a), mark: (end: ">"))
        let (a, b) = ("tree.0-0-0", "tree.0-0-1")
        line((a, .6, b), (b, .6, a), mark: (end: ">"))
        let (a, b) = ("tree.0-0-1", "tree.0-1")
        line((a, .6, b), (b, .6, a), mark: (end: ">"))
        let (a, b) = ("tree.0-0-1-0", "tree.0-1")
        line((a, .6, b), (b, .6, a), mark: (end: ">"))
    })
    + 写出该图的邻接矩阵(升序).
    + 若从$6$开始的DFS和BFS遍历序列均为$6,4,5,1,2,3$,求二者的生成树.
    + 所有拓扑排序序列
]
#question[
    给出图如下

    #diagram(
        $
                                  & 1 edge("ld", 1) edge("d", 3) edge("rd", 6) \
            2 edge("d", 5)edge(4) & 3 edge("ld", 4) edge("rd", 3)              & 4 edge("d", 5, #left) \
                  5 edge("rd", 2) &                                            &        6edge("ld", 7) \
                                  & 7
        $,
    )
    + 从节点$1$出发,列表Prim算法过程(选择边的顺序,连接的两边,边权).
    + 列表Kruskal算法过程(选择边的顺序,连接的两边,边权).
    + Kruskal算法过程中,怎样判断所选边会形成回路?
]
= 算法设计(CPP)
#question[
    定义链表节点
    ```cpp
    struct Node{
        int val;
        Node *left, *right;
    }
    ```
    现有一棵二叉树,设计算法求解:是否存在一条从根节点到叶节点的路径,使得路径上节点值之和等于给定值sum.
    + 设计算法并说明主要思路.
    + 实现.
    + 分析时间复杂度.
]
#question[
    设$1$base的升序序列$A[1..n]$的中位数为$A[ceil.l n/2 ceil.r]$.设$1$base的升序序列$A 1,A 2$的中位数为二者合并得到的升序序列的中位数.设计算法求解两个给定升序序列的中位数.
    + 设计算法并说明主要思路.
    + 实现.
    + 分析时间复杂度.
]
