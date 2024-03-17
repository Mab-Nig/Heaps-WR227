#pragma once

#include "Helper.hpp"

#include <functional>
#include <list>
#include <memory>

template <class TKey, class TCompare = std::less<TKey>>
class PairingHeap
{
public:
    using HeapT = PairingHeap<TKey, TCompare>;

public:
    PairingHeap() = default;

    PairingHeap(TKey const& value)
        : m_root(std::make_unique<TreeNode>(value))
    {
        m_size = 1;
    }

    PairingHeap(TKey&& value)
        : m_root(std::make_unique<TreeNode>(std::move(value)))
    {
        m_size = 1;
    }

    template <class TIterator>
    PairingHeap(TIterator first, TIterator last)
    {
        assign(first, last);
    }

    PairingHeap(HeapT const&) = delete;

    PairingHeap(HeapT&& other)
        : m_root(std::move(other))
    {
        m_size = other.m_size;
        other.m_size = 0;
    }

    HeapT& operator=(HeapT const&) = delete;

    HeapT& operator=(HeapT&& other)
    {
        m_size = other.m_size;
        m_root = std::move(other.m_root);
        other.m_size = 0;
        return *this;
    }

    TKey const& get_top() const
    {
        return m_root->value;
    }

    template <class TIterator>
    void assign(TIterator first, TIterator last)
    {
        clear();
        for (auto it = first; it != last; ++it)
        {
            Helper::increase_iteration_cnt();
            push(*it);
        }
    }

    void clear()
    {
        *this = HeapT();
    }

    void push(TKey const& value)
    {
        meld(HeapT(value));
    }

    void push(TKey&& value)
    {
        meld(HeapT(std::move(value)));
    }

    template <class... Args>
    void emplace(Args&&... args)
    {
        meld(HeapT(TKey(std::forward<Args>(args)...)));
    }

    void pop()
    {
        --m_size;

        if (m_size == 0)
        {
            m_root = nullptr;
            return;
        }

        TreeList& children = m_root->children;
        for (auto it = children.begin();
             it != children.end() && std::next(it) != children.end(); ++it)
        {
            Helper::increase_iteration_cnt();
            *it = merge_trees(std::move(*it), std::move(*std::next(it)));
            children.erase(std::next(it));
        }

        for (auto it = std::next(children.rbegin()); it != children.rend();
             ++it)
        {
            Helper::increase_iteration_cnt();
            children.back() =
                merge_trees(std::move(children.back()), std::move(*it));
        }
        m_root = std::move(children.back());
    }

    void meld(HeapT&& other)
    {
        if (other.m_size == 0)
        {
            return;
        }

        if (m_size == 0)
        {
            *this = std::move(other);
            return;
        }

        m_size += other.m_size;
        m_root = merge_trees(std::move(m_root), std::move(other.m_root));
    }

private:
    struct TreeNode;
    using TreeNodePtr = std::unique_ptr<TreeNode>;
    using TreeList = std::list<TreeNodePtr>;

    struct TreeNode
    {
        TKey value;
        TreeList children;

        TreeNode(TKey const& value)
            : value(value)
        {
        }

        TreeNode(TKey&& value)
            : value(std::move(value))
        {
        }

        TreeNode(TreeNode const&) = delete;
        TreeNode(TreeNode&&) = default;

        TreeNode& operator=(TreeNode const&) = delete;
        TreeNode& operator=(TreeNode&&) = default;
    };

private:
    TreeNodePtr merge_trees(TreeNodePtr first, TreeNodePtr second)
    {
        if (!first)
        {
            return second;
        }

        if (!second)
        {
            return first;
        }

        if (Helper::compare(first->value, second->value, TCompare()))
        {
            second->children.push_front(std::move(first));
            return second;
        }

        first->children.push_front(std::move(second));
        return first;
    }

private:
    int m_size = 0;
    TreeNodePtr m_root;
};
