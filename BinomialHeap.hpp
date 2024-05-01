#pragma once

#include "Heap.hpp"
#include "Helper.hpp"

#include <functional>
#include <memory>
#include <vector>

template <class TKey, class TCompare = std::less<TKey>>
class BinomialHeap : public Heap<TKey, TCompare>
{
public:
    using SelfT = BinomialHeap<TKey, TCompare>;
    using ParentT = Heap<TKey, TCompare>;
    using typename ParentT::KeyT;

public:
    BinomialHeap() = default;

    BinomialHeap(SelfT const& other) = delete;

    BinomialHeap(SelfT&& other)
        : m_top(other.m_top),
          m_trees(std::move(other.m_trees))
    {
        m_size = other.m_size;
        other.m_size = 0;
        other.m_top = nullptr;
    }

    template <class TIterator>
    BinomialHeap(TIterator first, TIterator last)
    {
        assign(first, last);
    }

    ~BinomialHeap() = default;

    SelfT& operator=(SelfT const& other) = delete;

    SelfT& operator=(SelfT&& other)
    {
        m_size = other.m_size;
        m_top = other.m_top;
        m_trees = std::move(other.m_trees);
        other.m_size = 0;
        other.m_top = nullptr;
        return *this;
    }

    TKey const& get_top() const override
    {
        return m_top->value;
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

    void clear() override
    {
        *this = SelfT{};
    }

    void push(TKey const& value) override
    {
        ++m_size;
        auto tree = std::make_unique<TreeNode>(value);
        insert_tree(std::move(tree));
    }

    void push(TKey&& value) override
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

    void pop() override
    {
        --m_size;
        TreeNodePtr top = std::move(m_trees[m_top->rank]);
        m_top = nullptr;
        insert_tree_list(std::move(top->children));
        update_top();
    }

    void meld(SelfT&& other)
    {
        m_size += other.m_size;
        for (int8_t i = 0; i <= HIGHEST_RANK; ++i)
        {
            Helper::increase_iteration_cnt();
            if (other.m_trees[i])
            {
                insert_tree(std::move(other.m_trees[i]));
            }
        }
    }

private:
    struct TreeNode;
    using TreeNodePtr = std::unique_ptr<TreeNode>;
    using TreeList = std::vector<TreeNodePtr>;

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

        TreeNode(TreeNode const&) = delete;
    };

private:
    void insert_tree(TreeNodePtr tree)
    {
        while (m_trees[tree->rank])
        {
            Helper::increase_iteration_cnt();
            int8_t rank = tree->rank;
            tree = merge_trees(std::move(tree), std::move(m_trees[rank]));
        }
        if (!m_top || !Helper::compare(tree->value, m_top->value, TCompare()))
        {
            m_top = tree.get();
        }
        m_trees[tree->rank] = std::move(tree);
    }

    void insert_tree_list(TreeList&& trees)
    {
        for (auto it = trees.begin(); it != trees.end(); ++it)
        {
            Helper::increase_iteration_cnt();
            insert_tree(std::move(*it));
        }
    }

    // FIRST and SECOND must have the same rank
    TreeNodePtr merge_trees(TreeNodePtr first, TreeNodePtr second)
    {
        if (Helper::compare(first->value, second->value, TCompare()))
        {
            std::swap(first, second);
        }
        first->children.push_back(std::move(second));
        ++first->rank;
        return first;
    }

    void update_top()
    {
        if (m_size == 0)
        {
            m_top = nullptr;
            return;
        }

        for (int8_t i = 0; i <= HIGHEST_RANK; ++i)
        {
            Helper::increase_iteration_cnt();

            if (!m_trees[i])
            {
                continue;
            }

            if (!m_top
                || !Helper::compare(m_trees[i]->value, m_top->value,
                                    TCompare()))
            {
                m_top = m_trees[i].get();
            }
        }
    }

private:
    static int8_t const HIGHEST_RANK = 31;

    using ParentT::m_size;
    TreeNode* m_top = nullptr;
    TreeList m_trees = TreeList(HIGHEST_RANK + 1);
};
