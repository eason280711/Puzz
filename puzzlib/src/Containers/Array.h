#pragma once
#include <vector>
#include <cstddef>

namespace puzz
{
    template <typename T, typename Container = std::vector<T>>
    class Array
    {
    public:
        Array()
        {
        }

        Array(std::initializer_list<T> list) : data_(list)
        {
        }

        T& operator[](size_t index) { return data_[index]; }
        size_t size() const { return data_.size(); }
        void push_back(const T& value) { data_.push_back(value); }
        void push_front(const T& value) { data_.insert(data_.begin(), value); }
        void pop_back() { data_.pop_back(); }
        void pop_front() { data_.erase(data_.begin()); }
        void clear() { data_.clear(); }
        typename Container::iterator erase(typename Container::iterator it) { return data_.erase(it); }

        typename Container::iterator erase(typename Container::iterator first, typename Container::iterator last)
        {
            return data_.erase(first, last);
        }

        typename Container::iterator find(const T& value)
        {
            for (auto it = data_.begin(); it != data_.end(); ++it)
            {
                if (*it == value)
                {
                    return it;
                }
            }
            return data_.end();
        }

        typename Container::iterator begin() { return data_.begin(); }
        typename Container::iterator end() { return data_.end(); }

    private:
        Container data_;
    };
}