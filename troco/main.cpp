# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int v, m;

    cin >> v >> m;

    vector<int> a(m);
    for (int i = 0; i < m; ++i) cin >> a[i];
    sort(a.begin(), a.begin() + m);

    vector<vector<bool>> dp(m + 1, vector<bool>(v + 1, false));
    for (int i = 0; i <= m; ++i) dp[i][0] = true;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= v; ++j) {
            if (j - a[i - 1] >= 0) dp[i][j] = dp[i - 1][j] || dp[i - 1][j - a[i - 1]];
            else dp[i][j] = dp[i - 1][j];
        }
    }

    cout << (dp[m][v] ? 'S' : 'N') << '\n';

    return 0;
}
