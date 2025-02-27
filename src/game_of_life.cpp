#include "matrix.h"


int main(){

    size_t dimension_x, dimention_y = 0;
    std::cout << "Please, enter the dimensions of the field (two numbers, e.g. 80 25). Then type Enter." << '\n';
    std::cin >> dimension_x >> dimention_y;

    std::cout << "Please, enter a generation count for which the game is proceeded (single number, e.g. 1000). Then type Enter." << '\n';
    int generation_count = 0;

    std::cin >> generation_count;

    std::cout << "Please, enter a number of living cells in an initial state. Then type Enter." << '\n';
    int counter = 0;
    std::cin >> counter;

    std::cout << "Please, enter coordinates of living cells: two numbers divided by a single white space (e.g. 2 34). Then type Enter. Repeat, until all coordinates are entered." << '\n';
    const std::vector<Point> v = GetInputData(counter);

    int refresh_rate = 0;
    std::cout << "Please, enter a refresh rate expressed as times per second (e.g. 5). Then type Enter." << '\n';
    std::cin >> refresh_rate;

    std::deque<std::vector<std::vector<bool>>> q;

    Matrix matrix(dimention_y, dimension_x, refresh_rate, 2, q);

    matrix.SetViableCells(v);

    matrix.Play(generation_count);

    std::cout << "Win!!!" << '\n';

    return 0;
}
