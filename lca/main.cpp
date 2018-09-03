// WA

# include <iostream>
# include <cstring>
# include <vector>
# include <list>

# define MAXN 1005
# define SZ 2005

using namespace std;

int first[MAXN], visited[MAXN], st[SZ][10], logs[SZ], t, n, m, cur, sz, q, v, w;
vector<list<int>> adj_list;
vector<int> euler, heights;

void dfs(int v = 0, int h = 1) {
    visited[v] = true;
    euler.push_back(v);
    heights.push_back(h);
    first[v] = euler.size() - 1;

    for (auto &adj : adj_list[v]) {
        if (!visited[adj]) {
            dfs(adj, h + 1);
            euler.push_back(v);
            heights.push_back(h);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    logs[1] = 0;
    for (int i = 2; i < SZ; ++i) logs[i] = logs[i/2] + 1;

    cin >> t;

    for (int c = 1; c <= t; ++c) {
        cout << "Case " << c << ":\n";
        cin >> n;
        sz = (n * 2) - 1;

        adj_list.clear(); adj_list.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> m;
            for (int j = 0; j < m; ++j) {
                cin >> cur;
                adj_list[i].push_back(--cur);
                adj_list[cur].push_back(i);
            }
        }

        euler.clear(); heights.clear();
        memset(visited, 0, sizeof(visited));
        memset(first, sz + 5, sizeof(first));
        dfs();

        for (int i = 0; i < sz; ++i) st[i][0] = i;
        for (int j = 1; j <= logs[sz]; ++j) {
            for (int i = 0; i + (1 << j) <= sz; ++i) {
                if (heights[st[i][j - 1]] < heights[st[i + (1 << (j - 1))][j - 1]])
                    st[i][j] = st[i][j - 1];
                else
                    st[i][j] = st[i + (1 << (j - 1))][j - 1];
            }
        }

        cin >> q;
        while (q--) {
            cin >> v >> w; v = first[v - 1]; w = first[w - 1];
            if (w < v) swap(v, w);
            int span = w - v + 1, j = logs[span];
            cout << euler[min(st[v][j], st[v + span - (1 << j)][j])] + 1 << '\n';
        }
    }

    return 0;
}
