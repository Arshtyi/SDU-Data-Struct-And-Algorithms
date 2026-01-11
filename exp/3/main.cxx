#include <iostream>
#include <sstream>
using namespace std;
class contact
{
private:
    string name, telephone;
    int cls, dorm;

public:
    contact() {}
    void input() { cin >> name >> telephone >> cls >> dorm; }
    string get_name() { return name; }
    string get_telephone() { return telephone; }
    int get_cls() { return cls; }
    int get_dorm() { return dorm; }
    void set_telephone(string &tele) { telephone = tele; }
    void set_cls(int c) { cls = c; }
    void set_dorm(int d) { dorm = d; }
};
template <class T>
class arrayList
{
private:
    int arrayLength, listSize;
    T *element;

public:
    arrayList(int initialCapacity = 10) : arrayLength(initialCapacity), element(new T[arrayLength]), listSize(0) {}
    arrayList(const arrayList<T> &arr)
    {
        arrayLength = arr.arrayLength;
        listSize = arr.listSize;
        element = new T[arrayLength];
        copy(arr.element, arr.element + listSize, element);
    }
    ~arrayList() { delete[] element; }
    int get_size() { return listSize; }
    void check_idx(int theIndex) const
    {
        if (theIndex < 0 || theIndex >= listSize)
        {
            std::ostringstream s;
            s << "index = " << theIndex << "size = " << listSize;
            cout << s.str() << endl;
            exit(0);
        }
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
    void erase(int theIndex)
    {
        check_idx(theIndex);
        std::copy(element + theIndex + 1, element + listSize, element + theIndex);
        element[--listSize].~T();
    }
    T &get(int theIndex)
    {
        check_idx(theIndex);
        return element[theIndex];
    }
};
class contactList
{
private:
    arrayList<contact *> theList;

public:
    contactList() {}
    ~contactList() {}
    void insert_contact()
    {
        contact *c = new contact;
        c->input();
        theList.push_back(c);
    }
    void delete_contact(const string &name)
    {
        for (int i = 0; i < theList.get_size(); ++i)
            if (theList.get(i)->get_name() == name)
            {
                contact *p = theList.get(i);
                delete p;
                theList.erase(i);
            }
    }
    void edit_contact(const string &name)
    {
        int index;
        for (int i = 0; i < theList.get_size(); ++i)
            if (theList.get(i)->get_name() == name)
                index = i;
        int op;
        cin >> op;
        switch (op)
        {
        case 1:
        {
            string tele;
            cin >> tele;
            theList.get(index)->set_telephone(tele);
        }
        break;
        case 2:
        {
            int c;
            cin >> c;
            theList.get(index)->set_cls(c);
        }
        break;
        case 3:
        {
            int d;
            cin >> d;
            theList.get(index)->set_dorm(d);
        }
        break;
        }
    }
    void search_contact(const string &name)
    {
        for (int i = 0; i < theList.get_size(); i++)
            if (theList.get(i)->get_name() == name)
            {
                cout << "1" << endl;
                return;
            }
        cout << "0" << endl;
    }
    void output(int cla)
    {
        int sum = 0;
        for (int i = 0; i < theList.get_size(); i++)
            if (theList.get(i)->get_cls() == cla)
                sum ^= theList.get(i)->get_dorm();
        cout << sum << endl;
    }
};
int main()
{
    // cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    contactList list;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int op;
        cin >> op;
        switch (op)
        {
        case 0:
            list.insert_contact();
            break;
        case 1:
        {
            string name;
            cin >> name;
            list.delete_contact(name);
        }
        break;
        case 2:
        {
            string name;
            cin >> name;
            list.edit_contact(name);
        }
        break;
        case 3:
        {
            string name;
            cin >> name;
            list.search_contact(name);
        }
        break;
        case 4:
        {
            int c;
            cin >> c;
            list.output(c);
        }
        break;
        }
    }
    return 0;
}
