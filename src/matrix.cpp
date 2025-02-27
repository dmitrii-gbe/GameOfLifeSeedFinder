#include "matrix.h"
#include <algorithm>

#define MIN_CYCLE_LENGTH 120

using Field = std::vector<std::vector<bool>>;

std::vector<Point> GetInputData(int counter){
    std::vector<Point> result(counter);

    while (counter != 0){
        size_t x, y = 0;
        std::cin >> x >> y;
        result.push_back(Point(x, y));
        --counter;
    }

    return result;
}

Point::Point(size_t x, size_t y) : x_(x), y_(y){}
Point::Point() = default;

std::ostream& operator<<(std::ostream& out, const Point& point){
    out << point.x_ << " " << point.y_;
    return out; 
}

std::ostream& operator<<(std::ostream& out, const std::vector<Point>& v){
    bool is_first = true;
    for (const auto& item : v){
        if (is_first){
            out << item;
            is_first = false;
        }
        else {
            out << " " << item;
        }    
    }
    out << '\n';
    return out;
}


std::ostream& operator<<(std::ostream& out, const std::vector<bool>& v){
    bool is_first = true;
    for (const auto item : v){
        if (is_first){
            out << '|' << (item ? '+' : ' ') << '|';
            is_first = false;
        }
        else {
            out << (item ? '+' : ' ') << '|';
        }
    }
    out << '\n';
    return out;
}

Matrix::Matrix(size_t rows, size_t cols, int refresh_rate, int alive_threshold, std::deque<std::vector<std::vector<bool> > >& two_previous_states) : two_previous_states_(two_previous_states) {
        rows_ = rows;
        cols_ = cols;
        switched_count_ = rows_ * cols_;
        alive_threshold_ = rows_ * cols_ * (alive_threshold / (100 * 1.0));
        refresh_rate_ = refresh_rate;
        std::vector<bool> v(cols, false);
        storage_ = std::vector<std::vector<bool> >(rows, v);
}

Matrix::Matrix(const Matrix& other) : two_previous_states_(other.two_previous_states_) {
    Matrix tmp(other.rows_, other.cols_, other.refresh_rate_, other.alive_threshold_, other.two_previous_states_);
    this->Swap(tmp);
}

void Matrix::Print() const {
    for (const auto& item : storage_){
            std::cout << item;
    }
    std::cout << "Switched count: " << switched_count_ << '\n';
}

void Matrix::SetViableCells(const std::vector<Point>& v){        
    for (auto& item : v){
        if (item.x_ >= rows_ || item.y_ >= cols_ || item.x_ < 0 || item.y_ < 0){
            throw std::logic_error("Wrong_coordinates");
        }
        else {
            storage_[item.x_][item.y_] = true;
        }
    }

    this->alive_count_ = v.size();
}

void Matrix::Refresh(){

    Matrix tmp(rows_, cols_, refresh_rate_, alive_threshold_, two_previous_states_);
    tmp.switched_count_ = 0;

    for (size_t row = 0; row < rows_; ++row){
        for (size_t col = 0; col < cols_; ++col){

            int count = Matrix::CountNeighbours(row, col);

            if (storage_[row][col] == false && count == 3){
                tmp.storage_[row][col] = true;
                ++tmp.switched_count_;
            }

            if (storage_[row][col] == true && (count > 3 || count < 2)){
                tmp.storage_[row][col] = false;
                ++tmp.switched_count_;
            }

            if (storage_[row][col] == true && (count == 3 || count == 2)){
                tmp.storage_[row][col] = true;
            }
        }
    }

    if (two_previous_states_.size() > MIN_CYCLE_LENGTH){
        two_previous_states_.erase(two_previous_states_.begin());
        two_previous_states_.push_back(storage_);
    }
    else {
        two_previous_states_.push_back(storage_);
    }

    this->Swap(tmp);
}


void Matrix::Erase() const {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / refresh_rate_));
    system("clear");
}


int Matrix::CountNeighbours(size_t row, size_t col) const {
    int counter = 0;
    for (int i = (int)row - 1; i <= (int)row + 1; ++i){
        for (int j = (int)col - 1; j <= (int)col + 1; ++j){
            int x_index = (rows_ + i) % rows_;
            int y_index = (cols_ + j) % cols_;
            if (CheckIfCellIsAlive(x_index, y_index)){
                ++counter;
            }
        }
    }
    return (Matrix::CheckIfCellIsAlive(row, col)) ? counter - 1 : counter;
}

bool Matrix::CheckIfCellIsAlive(size_t row, size_t col) const {
    return storage_[row][col];
}

int Matrix::Play(int generation_count){
    while (generation_count > 0 && IsAlive()){
        //Erase();
        //Print();
        Refresh();
       // std::cout << "Generations to the end of the game: " << generation_count << '\n';
        --generation_count;
    }

    return generation_count;
}

bool Matrix::IsAlive() const {
    if (!two_previous_states_.empty()){
        return std::all_of(two_previous_states_.begin(), two_previous_states_.end(), [this](const auto& item){ return item != this->storage_; });
    }
    else {
        return true;
    }
}

void Matrix::Swap(Matrix& other){
    std::swap(this->storage_, other.storage_);
    std::swap(this->rows_, other.rows_);
    std::swap(this->cols_, other.cols_);
    std::swap(this->alive_count_, other.alive_count_);
    std::swap(this->refresh_rate_, other.refresh_rate_);
    std::swap(this->switched_count_, other.switched_count_);
    std::swap(this->two_previous_states_, other.two_previous_states_);
}

std::string Matrix::FieldToString() const {
    std::string result;
    for (const auto& item : storage_){
        for (char c : item){
            result += c;
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    return this->storage_ == other.storage_;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Matrix Matrix::operator=(const Matrix& other){
    Matrix tmp(other.rows_, other.cols_, other.refresh_rate_, other.alive_threshold_, other.two_previous_states_);
    return tmp;
}

