#include <iostream>
using namespace std;
using u64 = unsigned long long;
const int N = 20;
int n;
u64 ans, v[N];
void permute(int idx)
{
    if (idx == n)
    {
        u64 val = 0;
        for(int i = 0; i < n; ++i)
            val += (u64)(i + 1) ^ v[i];
            ans|= val;
        return;
    }
    for (int i = idx; i < n;++i){
        swap(v[idx], v[i]);
        permute(idx + 1);
        swap(v[idx], v[i]);
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    permute(0);
    cout << ans << endl;
    return 0;
}
