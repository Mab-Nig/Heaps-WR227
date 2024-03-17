#pragma once

#include "Helper.hpp"

#include <functional>
#include <list>
#include <memory>
#include <vector>

template <class TKey, class TCompare = std::less<TKey>>
class BinomialHeap
{
public:
    using HeapT = BinomialHeap<TKey, TCompare>;

public:
    BinomialHeap() = default;

    BinomialHeap(HeapT const& other) = delete;

    BinomialHeap(HeapT&& other)
        : m_top(other.m_top),
          m_trees(std::move(other.m_trees))
    {
        m_size = other.m_size;
        other.m_size = 0;
        other.m_top = -1;
    }

    template <class TIterator>
    BinomialHeap(TIterator first, TIterator last)
    {
        assign(first, last);
    }

    ~BinomialHeap() = default;

    HeapT& operator=(HeapT const& other) = delete;

    HeapT& operator=(HeapT&& other)
    {
        m_size = other.m_size;
        m_top = other.m_top;
        m_trees = std::move(other.m_trees);
        other.m_size = 0;
        other.m_top = -1;
        return *this;
    }

    TKey const& get_top() const
    {
        return m_trees[m_top]->value;
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
        ++m_size;
        auto tree = std::make_unique<TreeNode>(value);
        insert_tree(std::move(tree));
    }

    void push(TKey&& value)
    {
        ++m_size;
        auto tree = std::make_unique<TreeNode>(std::move(value));
        insert_tree(std::move(tree));
    }

    template <class... Args>
    void emplace(Args&&... args)
    {
        ++m_size;
        auto tree =
            std::make_unique<TreeNode>(TKey(std::forward<Args>(args)...));
        insert_tree(std::move(tree));
    }

    void pop()
    {
        --m_size;
        TreeNodePtr top = std::move(m_trees[m_top]);
        insert_tree_list(std::move(top->children));
    }

    void meld(HeapT&& other)
    {
        m_size += other.m_size;
        insert_tree_list(std::move(other.m_trees));
    }

private:
    struct TreeNode;
    using TreeNodePtr = std::unique_ptr<TreeNode>;
    using TreeList = std::list<TreeNodePtr>;

    struct TreeNode
    {
        int8_t rank = 0;
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
    };

private:
    int8_t insert_tree(TreeNodePtr tree)
    {
        while (m_trees[tree->rank])
        {
            tree = merge_trees(std::move(tree), std::move(m_trees[tree->rank]));
        }
        if (Helper::compare(m_trees[m_top]->value, tree->value, TCompare()))
        {
            m_top = tree->rank;
        }
        m_trees[tree->rank] = std::move(tree);
    }

    void insert_tree_list(TreeList&& trees)
    {
        for (auto it = trees.begin(); it != trees.end(); ++it)
        {
            insert_tree(std::move(*it));
        }
    }

    // FIRST and SECOND must have the same rank
    TreeNodePtr merge_trees(TreeNodePtr first, TreeNodePtr second)
    {
        if (!Helper::compare(first->value, second->value, TCompare()))
        {
            first->children.push_back(std::move(second));
            ++first->rank;
            return first;
        }

        second->children.push_back(std::move(first));
        ++second->rank;
        return second;
    }

    void update_top()
    {
        if (m_size == 0)
        {
            m_top = -1;
            return;
        }

        for (int i = 0; i < HIGHEST_RANK; ++i)
        {
            if (m_top == -1
                || (m_trees[i]
                    && Helper::compare(m_trees[m_top]->value, m_trees[i],
                                       TCompare())))
            {
                m_top = i;
            }
        }
    }

private:
    static int8_t const HIGHEST_RANK = 32;

    int m_size = 0;
    int8_t m_top = -1;
    std::vector<TreeNodePtr> m_trees = std::vector<TreeNodePtr>(HIGHEST_RANK);
};
