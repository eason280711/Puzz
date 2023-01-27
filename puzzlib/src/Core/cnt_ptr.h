#pragma once
#include <cstddef>
#include <cstdlib>

namespace puzz
{
    template <typename T>
    class __declspec(dllexport) cnt_ptr
    {
    public:
        cnt_ptr(T *ptr = nullptr) : m_ptr(ptr)
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

        cnt_ptr(const cnt_ptr<T> &other) : m_ptr(other.m_ptr)
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

        cnt_ptr<T> &operator=(const cnt_ptr<T> &other)
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

        ~cnt_ptr()
        {
            unref();
        }

        T &operator*() { return *m_ptr; }
        T *operator->() { return m_ptr; }

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

    private:
        T *m_ptr;
        std::size_t *m_ref_count;
    };
} // namespace puzz
