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

bool alg2(std::vector <std::vector <int>> &arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        int l = 0, r = arr[0].size() - 1;
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
    }
    return false;
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
    std::vector <std::vector <long double>> times(3);
    int n = pow(2, 13);
    for (int i = 0; i < 14; ++i) {
        std::vector <std::vector <int>> arr = generation_arr(i);
        auto begin = std::chrono::steady_clock::now();
        bool ans = alg1(arr, 2 * n + 1);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        times[0].push_back(elapsed_ms.count());
        begin = std::chrono::steady_clock::now();
        ans = alg2(arr, 2 * n + 1);
        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        times[1].push_back(elapsed_ms.count());
        begin = std::chrono::steady_clock::now();
        ans = alg3(arr, 2 * n + 1);
        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        times[2].push_back(elapsed_ms.count());
    }
    for (int i = 0; i < times.size(); ++i) {
        for (int j = 0; j < times[i].size(); ++j) {
            if (i == 0 && j == 0) std::cout << "alg1" << std::endl; 
            else if (i == 1 && j == 0) std::cout << "alg2" << std::endl; 
            else if (i == 2 && j == 0) std::cout << "alg3" << std::endl; 
            std::cout << times[i][j] << std::endl;
        }
    }
    int x = 0;
    std::cout << "===================================================================" << std::endl;
    for (int i = 0; i < 14; ++i) {
        std::vector <std::vector <int>> arr = generation_arr(i, 0);
        auto begin = std::chrono::steady_clock::now();
        bool ans = alg1(arr, 16 * n + 1);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        times[0][x] = elapsed_ms.count();
        begin = std::chrono::steady_clock::now();
        ans = alg2(arr, 16 * n + 1);
        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        times[1][x] = elapsed_ms.count();
        begin = std::chrono::steady_clock::now();
        ans = alg3(arr, 16 * n + 1);
        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        times[2][x++] = elapsed_ms.count();
    }
    for (int i = 0; i < times.size(); ++i) {
        for (int j = 0; j < times[i].size(); ++j) {
            if (i == 0 && j == 0) std::cout << "alg1" << std::endl; 
            else if (i == 1 && j == 0) std::cout << "alg2" << std::endl; 
            else if (i == 2 && j == 0) std::cout << "alg3" << std::endl; 
            std::cout << times[i][j] << std::endl;
        }
    }
}
