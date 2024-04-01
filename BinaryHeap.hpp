#pragma once

#include "Heap.hpp"
#include "Helper.hpp"

#include <iterator>
#include <utility>
#include <vector>

template <class TKey, class TCompare = std::less<TKey>>
class BinaryHeap : public Heap<TKey, TCompare>
{
public:
    using SelfT = BinaryHeap<TKey, TCompare>;
    using ParentT = Heap<TKey, TCompare>;
    using typename ParentT::KeyT;

public:
    BinaryHeap() = default;

    template <class TIterator>
    BinaryHeap(TIterator first, TIterator last)
    {
        assign(first, last);
    }

    TKey const& get_top() const override
    {
        return m_container.front();
    }

    template <class TIterator>
    void assign(TIterator first, TIterator last)
    {
        m_container.assign(first, last);
        m_size = std::distance(first, last);
        make_heap();
    }

    void clear() override
    {
        *this = SelfT{};
    }

    void push(TKey const& value) override
    {
        ++m_size;
        m_container.push_back(value);
        bottom_up_heapify(m_size - 1);
    }

    void push(TKey&& value) override
    {
        ++m_size;
        m_container.push_back(std::move(value));
        bottom_up_heapify(m_size - 1);
    }

    template <class... Args>
    void emplace(Args&&... args)
    {
        ++m_size;
        m_container.emplace_back(std::forward<Args>(args)...);
        bottom_up_heapify(m_size - 1);
    }

    void pop() override
    {
        --m_size;
        Helper::swap(m_container.front(), m_container.back());
        m_container.pop_back();
        top_down_heapify(0);
    }

    void meld(SelfT&& other)
    {
        m_size += other.m_size;
        std::move(other.m_container.begin(), other.m_container.end(),
                  std::back_inserter(m_container));
        make_heap();
    }

private:
    void make_heap()
    {
        for (int i = (m_size - 1) >> 1; i >= 0; --i)
        {
            Helper::increase_iteration_cnt();
            top_down_heapify(i);
        }
    }

    void bottom_up_heapify(int index)
    {
        int parent = (index - 1) >> 1;
        while (index > 0
               && Helper::compare(m_container[parent], m_container[index],
                                  TCompare()))
        {
            Helper::increase_iteration_cnt();
            Helper::swap(m_container[index], m_container[parent]);
            index = parent;
            parent = (index - 1) >> 1;
        }
    }

    void top_down_heapify(int index)
    {
        int left = (index << 1) + 1, right = (index << 1) + 2;
        while (left < m_size)
        {
            Helper::increase_iteration_cnt();
            if (right >= m_size)
            {
                if (Helper::compare(m_container[index], m_container[left],
                                    TCompare()))
                {
                    Helper::swap(m_container[index], m_container[left]);
                }
                break;
            }

            int max = (Helper::compare(m_container[left], m_container[right],
                                       TCompare())
                           ? right
                           : left);

            if (!Helper::compare(m_container[index], m_container[max],
                                 TCompare()))
            {
                break;
            }

            Helper::swap(m_container[index], m_container[max]);
            index = max;
            left = (index << 1) + 1;
            right = (index << 1) + 2;
        }
    }

private:
    using ParentT::m_size;
    std::vector<TKey> m_container;
};
