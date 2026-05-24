#pragma once

#include <functional>

template <class TKey, class TCompare = std::less<TKey>>
class Heap
{
public:
    using KeyT = TKey;

public:
    virtual ~Heap() = default;

    bool is_empty() const
    {
        return m_size == 0;
    }

    int get_size() const
    {
        return m_size;
    }

    virtual TKey const& get_top() const = 0;
    virtual void clear() = 0;
    virtual void push(TKey const& value) = 0;
    virtual void push(TKey&& value) = 0;
    virtual void pop() = 0;

protected:
    int m_size = 0;
};
