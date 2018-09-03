// RTE

# include <iostream>
# include <vector>
# include <list>

using namespace std;

int logs[2005];

class SparseTable {
public:
    vector<vector<int>> st;
    vector<int> &a;

    SparseTable(vector<int> &a): a(a) {
        int n = a.size();
        st = vector<vector<int>>(n, vector<int>(logs[n]));
        for (int i = 0; i < n; ++i) st[i][0] = i;
        for (int j = 1; j <= logs[n]; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                if (a[st[i][j - 1]] < a[st[i + (1 << (j - 1))][j - 1]])
                    st[i][j] = st[i][j - 1];
                else
                    st[i][j] = st[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    int query(int l, int r) {
        if (r < l) swap(l, r);
        int span = r - l + 1, j = logs[span];
        if (a[st[l][j]] < a[st[l + span - (1 << j)][j]])
            return st[l][j];
        else
            return st[l + span - (1 << j)][j];
    }
};

class LCA {
public:
    vector<int> euler, heights, first;
    vector<bool> visited;

    LCA(vector<list<int>> &adj_list) {
        visited.resize(adj_list.size(), false);
        first.resize(adj_list.size());
        dfs(0, 1, adj_list);
    }

    void dfs(int v, int h, vector<list<int>> &adj_list) {
        visited[v] = true;
        first[v] = euler.size(); euler.push_back(v); heights.push_back(h);

        for (auto &adj : adj_list[v]) {
            if (!visited[adj])
                dfs(adj, h + 1, adj_list), euler.push_back(v), heights.push_back(h);
        }
    }

    int query(int v1, int v2, SparseTable &st) {
        return euler[st.query(first[v1], first[v2])];
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t, n, m, cur, q, v, w;

    logs[1] = 0;
    for (int i = 2; i < 2005; ++i) logs[i] = logs[i/2] + 1;

    cin >> t;
    for (int c = 1; c <= t; ++c) {
        cout << "Case: " << c << ":\n";

        cin >> n;
        vector<list<int>> adj_list(n);
        for (int i = 0; i < n; ++i) {
            cin >> m;
            while (m--)
                cin >> cur, adj_list[i].push_back(--cur), adj_list[cur].push_back(i);
        }

        LCA lca(adj_list);
        SparseTable st(lca.heights);

        cin >> q;
        while (q--) {
            cin >> v >> w; --v; --w;
            cout << lca.query(v, w, st) + 1 << '\n';
        }
    }

    return 0;
}
