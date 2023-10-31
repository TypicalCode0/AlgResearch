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
bool bin_search(std::vector <std::vector <int>> &arr, int target, int& r, int l, int i) {
    while (r - l >= 0) {
        int pivot = (r + l) / 2;
        if (arr[i][pivot] > target) {
            r = pivot - 1; 
        }
        else if (arr[i][pivot] < target) {
            l = pivot + 1; 
        }
        else if (arr[i][pivot] == target) {
            return true; 
        }
    }
    return false;
}


bool alg3(std::vector <std::vector <int>> &arr, int target) {
    int j = arr[0].size() - 1, i = 0;
    while (i < arr.size() && j >= 0) {
        if (arr[i][j] < target) {
            ++i;
        }
        else if (arr[i][j] > target) {
            int step = 1;
            while (1) {
                if (j - step > 0) j -= step;
                else j = 0;
                if (j > 0 && arr[i][j] > target) step *= 2;
                else if (arr[i][j] < target) {
                    int r = j + step - 1;
                    if (bin_search(arr, target, r, j + 1, i)) return true;
                    j = r;
                    ++i;
                    break;
                }
                else if (arr[i][j] == target) {
                    return true;
                }
                else return false;
            }
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
        bool ans = alg3(arr, 2 * n + 1);
        if (ans) std::cout << "YES" << std::endl;
        else std::cout << "NO" << std::endl;
    }
}
