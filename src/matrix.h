#pragma once

#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <deque>

struct Point {

    Point(size_t x, size_t y);
    Point();

    size_t x_ = 0;
    size_t y_ = 0;
};

std::ostream& operator<<(std::ostream& out, const Point& p);

std::ostream& operator<<(std::ostream& out, const std::vector<Point>& v);

std::vector<Point> GetInputData(int counter);

class Matrix {

    public:

        Matrix(size_t rows, size_t cols, int refresh_rate, int alive_threshold, std::deque<std::vector<std::vector<bool> > >& two_previous_states);

        Matrix(const Matrix& other);

        void Print() const;

        void SetViableCells(const std::vector<Point>& v);

        void Refresh();

        void Erase() const;

        int Play(int generation_count);

        bool IsAlive() const ;

    private:

        int CountNeighbours(size_t row, size_t col) const;

        bool CheckIfCellIsAlive(size_t row, size_t col) const;

        void Swap(Matrix& other);


        std::string FieldToString() const;

        bool operator==(const Matrix& other) const ;

        bool operator!=(const Matrix& other) const ;

        Matrix operator=(const Matrix& other);

        size_t rows_ = 0;
        size_t cols_ = 0;
        int refresh_rate_ = 0;
        int switched_count_ = 0;
        int alive_threshold_ = 0;
        int alive_count_ = 0;
        std::vector<std::vector<bool> > storage_;

        std::deque<std::vector<std::vector<bool> > >& two_previous_states_;
};