#pragma once
#include <cstddef>
#include <cstdlib>

namespace puzz
{
    template <typename T>
    class __declspec(dllexport) ref_ptr
    {
    public:
        ref_ptr(T *ptr = nullptr) : m_ptr(ptr)
        {
            if (m_ptr)
            {
                m_ref_count = new std::size_t(1);
            }
            else
            {
                m_ref_count = nullptr;
            }
        }

        ref_ptr(const ref_ptr<T> &other) : m_ptr(other.m_ptr)
        {
            if (m_ptr)
            {
                ++*(other.m_ref_count);
                m_ref_count = other.m_ref_count;
            }
            else
            {
                m_ref_count = nullptr;
            }
        }

        ref_ptr<T> &operator=(const ref_ptr<T> &other)
        {
            if (this != &other)
            {
                if (m_ptr)
                {
                    unref();
                }
                m_ptr = other.m_ptr;
                if (m_ptr)
                {
                    ++*(other.m_ref_count);
                    m_ref_count = other.m_ref_count;
                }
                else
                {
                    m_ref_count = nullptr;
                }
            }
            return *this;
        }

        ~ref_ptr()
        {
            unref();
        }

        T &operator*() const { return *m_ptr; }
        T *operator->() const { return m_ptr; }

        void ref()
        {
            if (m_ptr)
            {
                ++*m_ref_count;
            }
        }

        void unref()
        {
            if (m_ptr)
            {
                --*m_ref_count;
                if (*m_ref_count == 0)
                {
                    delete m_ptr;
                    delete m_ref_count;
                    m_ptr = nullptr;
                    m_ref_count = nullptr;
                }
            }
        }

        std::size_t use_count() const
        {
            if (m_ptr)
            {
                return *m_ref_count;
            }
            else
            {
                return 0;
            }
        }

        operator bool() const { return m_ptr != nullptr; }

        // 重載比較運算子，才能使用 TreeMap<ref_ptr<T>, U>容器
        // 但只是用來比較指標，不是用來比較內容
        // 因此只能初步使用，不建議使用
        // 未來會實現比較內容的運算子

        bool operator==(const ref_ptr<T> &other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const ref_ptr<T> &other) const { return m_ptr != other.m_ptr; }
        bool operator<(const ref_ptr<T> &other) const { return m_ptr < other.m_ptr; }
        bool operator>(const ref_ptr<T> &other) const { return m_ptr > other.m_ptr; }
        bool operator<=(const ref_ptr<T> &other) const { return m_ptr <= other.m_ptr; }
        bool operator>=(const ref_ptr<T> &other) const { return m_ptr >= other.m_ptr; }

    private:
        T *m_ptr;
        std::size_t *m_ref_count;
    };
}
