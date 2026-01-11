#include <iostream>
using namespace std;
using u64 = unsigned long long;
const int N = 25;
int n;
u64 ans, v[N];
void dfs(int idx, int pos, u64 cur)
{
    if (idx == n)
    {
        if (pos > 0)
            ans ^= cur;
        return;
    }
    dfs(idx + 1, pos, cur), dfs(idx + 1, pos + 1, cur + (u64)(pos + 1) * v[idx]);
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    dfs(0, 0, 0);
    cout << ans << endl;
    return 0;
}
