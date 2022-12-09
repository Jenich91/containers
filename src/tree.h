#ifndef SRC_TREE_H_
#define SRC_TREE_H_
#include <initializer_list>
#include <limits>
#include <utility>
#include <exception>

#include "treenode.h"
namespace s21 {
template <typename K, typename T>
class Tree {
 protected:
    TreeNode<K, T>* root_;
    size_t size_;
    TreeNode<K, T>* nil_;

 private:
    void print_N(TreeNode<K, T>* root);
    TreeNode<K, T>* Grandpa(TreeNode<K, T>* node) const;
    TreeNode<K, T>* Brother(TreeNode<K, T>* node) const;
    TreeNode<K, T>* Uncle(TreeNode<K, T>* node) const;
    void RotateLeft(TreeNode<K, T>* node);
    void RotateRight(TreeNode<K, T>* node);
    void InsertCase1(TreeNode<K, T>* node);
    void InsertCase2(TreeNode<K, T>* node);
    void InsertCase3(TreeNode<K, T>* node);
    void InsertCase4(TreeNode<K, T>* node);
    void InsertCase5(TreeNode<K, T>* node);
    void clean(TreeNode<K, T>* node);
    void delete_case1(TreeNode<K, T>* node);
    void delete_case2(TreeNode<K, T>* node);
    void delete_case3(TreeNode<K, T>* node);
    void delete_case4(TreeNode<K, T>* node);
    void delete_case5(TreeNode<K, T>* node);
    void delete_case6(TreeNode<K, T>* node);
    void replace_node(TreeNode<K, T>* node, TreeNode<K, T>* child);
    void delete_one_child(TreeNode<K, T>* node);
    TreeNode<K, T>* next_elem(TreeNode<K, T>* root) const;
    int number_of_child(TreeNode<K, T>* root) const;
    void swap_node(TreeNode<K, T>* del, TreeNode<K, T>* next);

 public:
    class Iterator {
     public:
        TreeNode<K, T>* node_;
        Iterator() : node_(nullptr) {}
        void operator++();
        void operator--();
        bool operator==(const Iterator& other) { return this->node_ == other.node_; }
        bool operator!=(const Iterator& other) { return this->node_ != other.node_; }
        const K operator*();
    };
    Tree() : root_(nullptr), size_(0), nil_(nullptr) {}
    explicit Tree(const std::initializer_list<K>& items);
    Tree(const Tree<K, T>& t);
    ~Tree();
    Tree<K, T>& operator=(Tree<K, T>&& other);
    Iterator begin() const;
    Iterator end() const;
    bool empty() { return !root_; }
    size_t size() { return size_; }
    size_t max_size() { return std::numeric_limits<size_t>::max() / sizeof(TreeNode<K, T>) / 2; }
    void swap(Tree<K, T>& other);
    void merge(Tree<K, T>* other, bool is_set);
    Iterator find(const K& key);
    bool contains(const K& key);
    Iterator insert(const K& value);
    void clear();
    void print();
    void erase(Iterator pos);

 protected:
    std::pair<Iterator, bool> FindContains(const K& key);

 private:
    Iterator FindPlace(const K& value);
};

}  // namespace s21
#include "tree.cpp"
#endif  // SRC_TREE_H_
