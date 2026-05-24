#pragma once

#include "Heap.hpp"
#include "Helper.hpp"

#include <functional>
#include <memory>
#include <vector>

template <class TKey, class TCompare = std::less<TKey>>
class PairingHeap : public Heap<TKey, TCompare>
{
public:
    using SelfT = PairingHeap<TKey, TCompare>;
    using ParentT = Heap<TKey, TCompare>;
    using typename ParentT::KeyT;

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

    PairingHeap(SelfT const&) = delete;

    PairingHeap(SelfT&& other)
        : m_root(std::move(other.m_root))
    {
        m_size = other.m_size;
        other.m_size = 0;
    }

    SelfT& operator=(SelfT const&) = delete;

    SelfT& operator=(SelfT&& other)
    {
        m_size = other.m_size;
        m_root = std::move(other.m_root);
        other.m_size = 0;
        return *this;
    }

    TKey const& get_top() const override
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

    void clear() override
    {
        *this = SelfT{};
    }

    void push(TKey const& value) override
    {
        ++m_size;
        auto tree = std::make_unique<TreeNode>(value);
        m_root = merge_trees(std::move(m_root), std::move(tree));
    }

    void push(TKey&& value) override
    {
        ++m_size;
        auto tree = std::make_unique<TreeNode>(std::move(value));
        m_root = merge_trees(std::move(m_root), std::move(tree));
    }

    template <class... Args>
    void emplace(Args&&... args)
    {
        ++m_size;
        auto tree =
            std::make_unique<TreeNode>(TKey(std::forward<Args>(args)...));
        m_root = merge_trees(std::move(m_root), std::move(tree));
    }

    void pop() override
    {
        --m_size;

        if (m_size == 0)
        {
            m_root = nullptr;
            return;
        }

        TreeList& children = m_root->children;
        for (int i = 0; i + 1 < children.size(); i += 2)
        {
            Helper::increase_iteration_cnt();
            children[i] =
                merge_trees(std::move(children[i]), std::move(children[i + 1]));
        }

        std::unique_ptr<TreeNode> new_root;
        for (int i = children.size() - 1 - !(children.size() & 1); i >= 0;
             i -= 2)
        {
            Helper::increase_iteration_cnt();
            new_root = merge_trees(std::move(new_root), std::move(children[i]));
        }
        m_root = std::move(new_root);
    }

    void meld(SelfT&& other)
    {
        m_size += other.m_size;
        m_root = merge_trees(std::move(m_root), std::move(other.m_root));
    }

private:
    struct TreeNode;
    using TreeNodePtr = std::unique_ptr<TreeNode>;
    using TreeList = std::vector<TreeNodePtr>;

    struct TreeNode
    {
        TKey value;
        TreeList children;

        TreeNode() = default;

        TreeNode(TKey const& value)
            : value{value}
        {
        }

        TreeNode(TKey&& value)
            : value{std::move(value)}
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
            std::swap(first, second);
        }
        first->children.push_back(std::move(second));
        return first;
    }

private:
    using ParentT::m_size;
    TreeNodePtr m_root;
};
