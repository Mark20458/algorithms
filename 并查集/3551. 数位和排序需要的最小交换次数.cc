#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int sum(int a) {
    int sum = 0;
    while (a != 0) {
        sum += (a % 10);
        a /= 10;
    }
    return sum;
}

class U_Set {
public:
    int n;
    int *const parent;

public:
    U_Set(int n) : n(n), parent(new int[n]) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x)
            return x;
        else
            return (parent[x] = find(parent[x]));
    }

    void join(int x, int y) {
        int root_x = find(x), root_y = find(y);
        parent[root_x] = root_y;
    }

    int count() {
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (parent[i] == i)
                res++;
        }
        return res;
    }
};

class Solution {
public:
    int minSwaps(vector<int> &nums) {
        const int n = nums.size();
        U_Set s(n);
        vector<pair<int, int>> array(n);
        for (int i = 0; i < n; i++)
            array[i] = make_pair(nums[i], i);
        sort(array.begin(), array.end(),
             [](pair<int, int> x, pair<int, int> y) {
                 if (sum(x.first) == sum(y.first))
                     return x.first < y.first;
                 return sum(x.first) < sum(y.first);
             });
        for (int i = 0; i < n; i++) {
            int k = array[i].second;
            s.join(i, k);
        }
        return n - s.count();
    }
};
