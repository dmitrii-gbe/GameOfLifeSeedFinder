#include <atomic>
#include <filesystem>
#include <fstream>
#include <future>
#include <mutex>

#include "combinatorics.h"
#include "matrix.h"

void TestCombinationsInternal(int rows, int cols, double divider, int rounds,
                              int refresh_rate, int alive_threshold,
                              int good_combination_threshold, int thread_number,
                              std::mutex &m,
                              std::atomic<size_t> &counter_tested,
                              std::atomic<size_t> &counter_found,
                              std::atomic<int> &file_counter) {
  while (true) {
    auto v = GenerateVectorOfRandPoints(rows, rows * cols / divider);
    std::deque<std::vector<std::vector<bool>>> q;
    Matrix matrix(rows, cols, refresh_rate, alive_threshold, q);
    matrix.SetViableCells(v);
    int count = matrix.Play(rounds);
    if (count < rounds - good_combination_threshold) {
      std::lock_guard<std::mutex> lock(m);
      std::filesystem::path p(std::filesystem::current_path() /
                              "good_combinations");
      std::filesystem::create_directory(p);
      std::ofstream out(
          p / std::filesystem::path("seed" + std::to_string(file_counter++)),
          std::ios_base::ate);
      ++counter_found;
      out << v << '\n';
      std::cout << "Thread: " << thread_number << " Tested: " << counter_tested
                << " Found: " << counter_found << '\n';
      out.close();
    }
    ++counter_tested;
    if (counter_tested % 10000 == 0) {
      std::cout << "Thread: " << thread_number << " Tested: " << counter_tested
                << " Found: " << counter_found << '\n';
    }
  }
}

void TestCombinations(int rows, int cols, double divider, int rounds,
                      int refresh_rate, int alive_threshold,
                      int good_combination_threshold, int threads) {
  std::atomic<size_t> counter_tested = 0;
  std::atomic<size_t> counter_found = 0;
  std::vector<std::future<void>> threads_storage;
  std::mutex m;
  std::atomic<int> file_counter = 0;

  for (int i = 0; i < threads; ++i) {
    std::future<void> item =
        std::async([cols, rows, divider, rounds, refresh_rate, alive_threshold,
                    good_combination_threshold, i, &m, &counter_tested,
                    &counter_found, &file_counter] {
          TestCombinationsInternal(rows, cols, divider, rounds, refresh_rate,
                                   alive_threshold, good_combination_threshold,
                                   i, m, counter_tested, counter_found,
                                   file_counter);
        });
    threads_storage.push_back(std::move(item));
  }
}
int main() {
  int threads = 0;
  int cycles_count = 0;

  std::cout << "Please, enter a number of threads you wish the program should "
               "operate at: "
            << '\n';
  std::cin >> threads;

  std::cout
      << "Please, enter a minimal number of cycles the field should live for: "
      << '\n';
  std::cin >> cycles_count;

  std::cout << "Please, enter a field dimentions as rows and columns divided "
               "by a single white space (e.g. "
               "25 80). Then type Enter."
            << '\n';
  int rows, cols;
  std::cin >> rows >> cols;

  TestCombinations(rows, cols, 5, 10000, 1000, 10, cycles_count, threads);

  return 0;
}
