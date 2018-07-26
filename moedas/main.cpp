# include <iostream>

# define INF 50005

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int m, n, a[105], dp[INF];

    while (true) {
        cin >> m;
        if (m == 0) break;

        cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i <= m; ++i) dp[i] = INF;
        dp[0] = 0;

        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - a[j] >= 0) dp[i] = min(dp[i], dp[i - a[j]] + 1);
            }
        }

        if (dp[m] == INF) cout << "Impossivel\n";
        else cout << dp[m] << '\n';
    }

    return 0;
}
