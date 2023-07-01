#pragma once
#include <map>
#include <cstddef>
#include <stdexcept>

namespace puzz
{
    template <typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<std::pair
                  <const Key, T>>>
    class TreeMap
    {
    public:
        // 以TreeMapType代替std::map類型，方便以後修改
        using TreeMapType = std::map<Key, T, Compare, Allocator>;

        TreeMap() : data_()
        {
        }

        TreeMap(std::initializer_list<std::pair<const Key, T>> list) : data_(list)
        {
        }

        T& operator[](const Key& index) { return data_[index]; }
        typename TreeMapType::size_type size() const { return data_.size(); }
        void insert(const std::pair<const Key, T>& value) { data_.insert(value); }
        typename TreeMapType::iterator begin() { return data_.begin(); }
        typename TreeMapType::iterator end() { return data_.end(); }
        // find
        typename TreeMapType::iterator find(const Key& key) { return data_.find(key); }

        std::pair<const Key, T>& at(std::size_t index)
        {
            if (index >= data_.size())
            {
                throw std::out_of_range("Index out of range");
            }
            auto it = data_.begin();
            std::advance(it, index);
            return *it;
        }

    private:
        TreeMapType data_;
    };
}