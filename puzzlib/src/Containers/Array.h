#pragma once
#include <vector>
#include <cstddef>

namespace puzz
{

    template <typename T, typename Container = std::vector<T>>
    class Array
    {
    public:
        Array() {}
        Array(std::initializer_list<T> list) : data_(list) {}
        T &operator[](size_t index) { return data_[index]; }
        size_t size() const { return data_.size(); }
        void push_back(const T &value) { data_.push_back(value); }
        void push_front(const T &value) { data_.insert(data_.begin(), value); }
        typename Container::iterator begin() { return data_.begin(); }
        typename Container::iterator end() { return data_.end(); }

    private:
        Container data_;
    };

}