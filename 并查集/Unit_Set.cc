#include <iostream>

class Unit_Set {
private:
    int n;
    int *parent; // 指向父节点
    int *rank;   // 深度

public:
    Unit_Set(int n) : n(n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~Unit_Set() {
        delete[] parent;
        delete[] rank;
    }

    int find(int x) {
        if (x == parent[x])
            return x;
        return parent[x] = find(parent[x]); // 路径压缩
    }

    void join(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy)
            return; // 已经在同一集合中
        if (rank[fx] < rank[fy]) {
            parent[fx] = fy;
        } else if (rank[fx] > rank[fy]) {
            parent[fy] = fx;
        } else {
            parent[fx] = fy;
            rank[fy]++;
        }
    }

    int count() {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (parent[i] == i)
                count++;
        }
        return count;
    }
};

int main() {
    int n = 10;
    Unit_Set us(n);
    us.join(1, 2);
    us.join(2, 3);
    us.join(4, 5);
    us.join(6, 7);
    us.join(7, 8);
    us.join(8, 9);

    std::cout << "Find set of 1: " << us.find(1) << std::endl;
    std::cout << "Find set of 2: " << us.find(2) << std::endl;
    std::cout << "Find set of 3: " << us.find(3) << std::endl;
    std::cout << "Find set of 4: " << us.find(4) << std::endl;
    std::cout << "Find set of 5: " << us.find(5) << std::endl;
    std::cout << "Find set of 6: " << us.find(6) << std::endl;
    std::cout << "Find set of 7: " << us.find(7) << std::endl;
    std::cout << "Find set of 8: " << us.find(8) << std::endl;
    std::cout << "Find set of 9: " << us.find(9) << std::endl;

    std::cout << "Number of disjoint sets: " << us.count() << std::endl;
    return 0;
}