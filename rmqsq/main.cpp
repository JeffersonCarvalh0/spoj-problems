# include <iostream>

using namespace std;

int st[100005][25];
int logs[100005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q, l, r, a[100005];

    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i], st[i][0] = a[i];

    logs[1] = 0;
    for (int i = 2; i <= n + 1; ++i) logs[i] = logs[i/2] + 1;

    for (int j = 1; j <= logs[n]; ++j)
        for (int i = 0; i + (1 << j) <= n; ++i)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);

    cin >> q;
    while (q--) {
        cin >> l >> r;
        int span = r - l + 1, j = logs[span];
        cout << min(st[l][j], st[l + span - (1 << j)][j]) << '\n';
    }

    return 0;
}
