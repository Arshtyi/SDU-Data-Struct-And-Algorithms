#include <iostream>
using namespace std;
template <class E, class K>
class hashTable
{
private:
    int D;
    E *ht;
    bool *empty;
    int hSearch(const K &k) const
    {
        int index = k % D, real_index = index;
        do
        {
            if (empty[real_index] || ht[real_index] == k)
                return real_index;
            real_index = (real_index + 1) % D;
        } while (real_index != index);
        return real_index;
    }

public:
    hashTable(int divisor = 11) : D(divisor), ht(new E[D]), empty(new bool[D])
    {
        for (int i = 0; i < D; ++i)
            empty[i] = true;
    }
    ~hashTable()
    {
        delete[] ht;
        delete[] empty;
    }
    void search(const K &k, E &e)
    {
        int place = hSearch(k);
        if (empty[place] || ht[place] != k)
            cout << -1 << endl;
        else
            cout << place << endl;
    }
    hashTable<E, K> &insert(const E &e)
    {
        K k = e;
        int place = hSearch(k);
        if (empty[place])
        {
            empty[place] = false;
            ht[place] = e;
            cout << place << endl;
        }
        else
            cout << "Existed" << endl;
        return *this;
    }
    int del(const E &e)
    {
        K k = e;
        int place = hSearch(k), cnt = 0;
        if (empty[place])
        {
            cout << "Not Found" << endl;
            return -1;
        }
        else if (ht[place] == k)
        {
            empty[place] = true;
            int idx1 = place, idx2 = place, idx;
            do
            {
                idx1 = (idx1 + 1) % D;
                if (empty[idx1])
                    break;
                idx = ht[idx1] % D;
                if ((idx1 != idx && idx1 > idx2 && idx <= idx2) || (idx1 < idx && (idx2 < idx1 || idx2 >= idx)))
                {
                    empty[idx2] = false;
                    ht[idx2] = ht[idx1];
                    empty[idx1] = true;
                    cnt++;
                    idx2 = idx1;
                }
            } while (!empty[idx1 + 1] && (idx1 + 1) != idx2);
        }
        cout << cnt << endl;
        return cnt;
    }
};
int D, m;
int main()
{
    cin >> D >> m;
    hashTable<int, int> table(D);
    for (int i = 1; i <= m; ++i)
    {
        int op, x;
        cin >> op >> x;
        if (op == 0)
            table.insert(x);
        else if (op == 1)
            table.search(x, x);
        else
            table.del(x);
    }
    return 0;
}
