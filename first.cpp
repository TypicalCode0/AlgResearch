#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
#include <thread>
#include <chrono>

std::vector <std::vector <int>> generation_arr(int x, bool mode = 1, int n = pow(2, 13)) {
    int m = pow(2, x);
    std::vector <std::vector <int>> arr(m, std::vector <int> (n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mode) arr[i][j] = (n / m * i + j) * 2;
            else arr[i][j] = (n / m * i * j) * 2;
        }
    }
    return arr;
}

bool alg1(std::vector <std::vector <int>> &arr, int target) {
    int j = arr[0].size() - 1, i = 0;
    while (i < arr.size() && j >= 0) {
        if (arr[i][j] < target) {
            ++i;
        }
        else if (arr[i][j] > target) {
            --j;
        }
        else if (arr[i][j] == target) {
            return true;
        }
    }
    return false;
}

int main() {
    int n = pow(2, 13);
    for (int i = 0; i < 14; ++i) {
        std::vector <std::vector <int>> arr = generation_arr(i);
        bool ans = alg1(arr, 2 * n + 1);
        if (ans) std::cout << "YES" << std::endl;
        else std::cout << "NO" << std::endl;
    }
}
