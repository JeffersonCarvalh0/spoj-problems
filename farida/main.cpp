// DP
# include <iostream>

typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t, n;
    ll a[10005], dp[100005];

    cin >> t;

    for (int c = 1; c <= t; ++c) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];

        dp[0] = 0; dp[1] = a[0];

        for (int i = 2; i <= n; ++i) dp[i] = max(a[i - 1] + dp[i - 2], dp[i - 1]);

        cout << "Case " << c << ": " << dp[n] << '\n';
    }
    return 0;
}
