#include <bits/stdc++.h>

using namespace std;

bool ans(long long a, long long b, long long n, long long m) {
    if (a == 0 && n == 0 && (b != 0 || m != 0))
        return false;
    if ((a != 0 || n != 0) && b == 0 && m == 0)
        return false;
    return (a + b) >= (n + m);
}
int main() {

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        long long  a, b, n, m;
        cin >> a >> b >> n >> m;
        if (ans(a, b, n, m)) cout << "Yes";
        else cout << "No";
        cout << endl;
    }
    return 0;
}
