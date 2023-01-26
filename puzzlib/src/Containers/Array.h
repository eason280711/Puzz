#pragma once
#include <vector>
#include <cstddef>

namespace puzz
{

    template <typename T, typename Container>
    class ArrayInterface
    {
    public:
        virtual ~ArrayInterface() {}
        virtual T &operator[](size_t index) = 0;
        virtual size_t size() const = 0;
        virtual void push_back(const T &value) = 0;
        virtual void push_front(const T &value) = 0;
        virtual typename Container::iterator begin() = 0;
        virtual typename Container::iterator end() = 0;
    };

    template <typename T, typename Container = std::vector<T>>
    class Array : public ArrayInterface<T, Container>
    {
    public:
        Array() {}
        Array(std::initializer_list<T> list) : data_(list) {}
        T &operator[](size_t index) override { return data_[index]; }
        size_t size() const override { return data_.size(); }
        void push_back(const T &value) override { data_.push_back(value); }
        void push_front(const T &value) override { data_.insert(data_.begin(), value); }
        typename Container::iterator begin() override { return data_.begin(); }
        typename Container::iterator end() override { return data_.end(); }

    private:
        Container data_;
    };

}