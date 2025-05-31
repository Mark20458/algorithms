#include <vector>

using namespace std;

/**
 * 最近公共祖先模板
 */
class TreeAncestor {
private:
    vector<int> depth;
    vector<vector<int>> pa;

public:
    TreeAncestor(vector<pair<int, int>> edges) {
        int n = edges.size();
        int m = bit_width((unsigned)n);

        vector<vector<int>> g(n);
        for (auto &[x, y] : edges) {
            g[x].push_back(y);
            g[y].push_back(x);
        }

        depth.resize(n);
        pa.resize(n, vector<int>(m, -1));

        auto dfs = [&](this auto &&dfs, int x, int fa) -> void {
            pa[x][0] = fa;
            for (int y : g[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);

        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                int p = pa[x][i];
                if (p == -1)
                    continue;
                pa[x][i + 1] = pa[p][i];
            }
        }
    }

    int get_kth_ancestor(int node, int k) {
        int m = bit_width((unsigned)k);
        for (int i = 0; i < m; i++) {
            if (k >> i & 1) {
                node = pa[node][i];
                if (node == -1)
                    break;
            }
        }
        return node;
    }

    int get_lca(int x, int y) {
        if (depth[x] > depth[y])
            swap(x, y);
        y = get_kth_ancestor(y, depth[y] - depth[x]);
        if (x == y)
            return x;
        for (int i = pa[x].size() - 1; i >= 0; i--) {
            int px = pa[x][i], py = pa[y][i];
            if (px != py) {
                x = px;
                y = py;
            }
        }
        return pa[x][0];
    }
};
