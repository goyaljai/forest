/**
 * @file binary_search_tree.h
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>

/**
 * @brief The forest library namespace
 */
namespace forest {
        template <typename key_t, typename value_t>
        struct binary_search_tree_node {
                key_t key;     ///< The key of the node
                value_t value; ///< The value of the node
                binary_search_tree_node *parent;  ///< A pointer to the parent of the node
                binary_search_tree_node *left;    ///< A pointer to the left child of the node
                binary_search_tree_node *right;   ///< A pointer to the right child of the node
                /**
                 * @brief Constructor of a binary search tree node
                 */
                binary_search_tree_node(key_t key, value_t value) {
                        this->key = key;
                        this->value = value;
                        this->parent = nullptr;
                        this->left = nullptr;
                        this->right = nullptr;
                }
                /**
                 * @brief Prints to the std::cout information about the node
                 */
                void info() const {
                        std::cout << this->key << "\t";
                        if (this->left != nullptr) {
                                std::cout << this->left->key << "\t";
                        } else {
                                std::cout << "null" << "\t";
                        }
                        if (this->right != nullptr) {
                                std::cout << this->right->key << "\t";
                        } else {
                                std::cout << "null" << "\t";
                        }
                        if (this->parent != nullptr) {
                                std::cout << this->parent->key << std::endl;
                        } else {
                                std::cout << "null" << std::endl;
                        }
                }
        };
        template <typename key_t, typename value_t>
        class binary_search_tree {
        private:
                binary_search_tree_node <key_t, value_t> *root;
                void pre_order_traversal(binary_search_tree_node <key_t, value_t> *x) {
                        if (x == nullptr) return;
                        x->info();
                        pre_order_traversal(x->left);
                        pre_order_traversal(x->right);
                }
                void in_order_traversal(binary_search_tree_node <key_t, value_t> *x) {
                        if (x == nullptr) return;
                        in_order_traversal(x->left);
                        x->info();
                        in_order_traversal(x->right);
                }
                void post_order_traversal(binary_search_tree_node <key_t, value_t> *x) {
                        if (x == nullptr) return;
                        post_order_traversal(x->left);
                        post_order_traversal(x->right);
                        x->info();
                }
                void breadth_first_traversal(binary_search_tree_node <key_t, value_t> *x) {
                        std::queue <binary_search_tree_node <key_t, value_t> *> queue;
                        if (x == nullptr) return;
                        queue.push(x);
                        while(queue.empty() == false) {
                                binary_search_tree_node <key_t, value_t> *y = queue.front();
                                y->info();
                                queue.pop();
                                if (y->left != nullptr) queue.push(y->left);
                                if (y->right != nullptr) queue.push(y->right);
                        }
                }
                unsigned long long height(binary_search_tree_node <key_t, value_t> *x) {
                        if (x == nullptr) return 0;
                        return std::max(height(x->left), height(x->right)) + 1;
                }
                unsigned long long size(binary_search_tree_node <key_t, value_t> *x) {
                        if (x == nullptr) return 0;
                        return size(x->left) + size(x->right) + 1;
                }
                void graphviz(std::ofstream &file, binary_search_tree_node <key_t, value_t> *x, unsigned long long *count) {
                        if (x == nullptr) return;
                        graphviz(file, x->left, count);
                        if (x->left != nullptr) {
                                file << "\t" << x->key << " -> " << x->left->key << ";" << std::endl;
                        } else {
                                file << "\t" << "null" << *count << " " << "[shape=point]" << ";" << std::endl;
                                file << "\t" << x->key << " -> " << "null" << *count << ";" << std::endl;
                                (*count)++;
                        }
                        if (x->right != nullptr) {
                                file << "\t" << x->key << " -> " << x->right->key << ";" << std::endl;
                        } else {
                                file << "\t" << "null" << *count << " " << "[shape=point]" << ";" << std::endl;
                                file << "\t" << x->key << " -> " << "null" << *count << ";" << std::endl;
                                (*count)++;
                        }
                        graphviz(file, x->right, count);
                }
        public:
                binary_search_tree() {
                        root = nullptr;
                }
                ~binary_search_tree() {

                }
                /**
                 * @brief Performs a Pre Order Traversal starting from the root node
                 * @return void
                 */
                void pre_order_traversal() {
                        pre_order_traversal(root);
                }
                /**
                 * @brief Performs a In Order Traversal starting from the root node
                 * @return void
                 */
                void in_order_traversal() {
                        in_order_traversal(root);
                }
                /**
                 * @brief Performs a Post Order Traversal starting from the root node
                 * @return void
                 */
                void post_order_traversal() {
                        post_order_traversal(root);
                }
                /**
                 * @brief Performs a Breadth First Traversal starting from the root node
                 * @return void
                 */
                void breadth_first_traversal() {
                        breadth_first_traversal(root);
                }
                /**
                 * @brief Generates a DOT file representing the Binary Search Tree
                 * @param filename The filename of the .dot file
                 * @return void
                 */
                void graphviz(std::string filename) {
                        std::ofstream file;
                        unsigned long long count = 0;
                        file.open(filename);
                        file << "digraph {" << std::endl;
                        graphviz(file, root, &count);
                        file << "}" << std::endl;
                        file.close();
                }
                /**
                 * @brief Inserts a new node into the Binary Search Tree
                 * @param key The key for the new node
                 * @param value The value for the new node
                 * @return true if the new node was inserted and false otherwise
                 */
                const binary_search_tree_node <key_t, value_t> *insert(key_t key, value_t value) {
                        binary_search_tree_node <key_t, value_t> *current = root;
                        binary_search_tree_node <key_t, value_t> *parent = nullptr;
                        while(current!=nullptr) {
                                parent = current;
                                if (key > current->key) {
                                        current = current->right;
                                } else if (key < current->key) {
                                        current = current->left;
                                } else {
                                        return nullptr;
                                }
                        }
                        current = new binary_search_tree_node <key_t, value_t> (key, value);
                        current->parent = parent;
                        if(parent == nullptr) {
                                root = current;
                        } else if (current->key > parent->key) {
                                parent->right = current;
                        } else if (current->key < parent->key) {
                                parent->left = current;
                        }
                        return current;
                }
                /**
                 * @brief Performs a binary search starting from the root node
                 * @return The node with the key specified
                 */
                const binary_search_tree_node <key_t, value_t> *search(key_t key) {
                        binary_search_tree_node <key_t, value_t> *x = root;
                        while (x != nullptr) {
                                if (key > x->key) {
                                        x = x->right;
                                } else if (key < x->key) {
                                        x = x->left;
                                } else {
                                        return x;
                                }
                        }
                        return nullptr;
                }
                
                /**
                 * @brief Deletes the node with the given key
                 * // utility inorder function
                 */
                binary_search_tree_node <key_t,value_t> *minValueNode(binary_search_tree_node <key_t, value_t> *node)
                {
                    binary_search_tree_node <key_t, value_t> *current = node;

                    while (current->left != nullptr)
                        current = current->left;

                    return current;
                }
                
                /**
                 * @brief Deletes the node with the given key
                 *
                 */

                const binary_search_tree_node <key_t,value_t> *delete(key_t key)
                {
                        if (root == nullptr) return root;

                        if(key < root->key)
                        {
                                root->left = delete(root->left,key);
                        }
                        else
                        {
                                root->right = delete(root->right,key);
                        }
                        else
                        {
                                if (root->left == nullptr)
                        {
                            binary_search_tree_node <key_t, value_t> *temp = root->right;
                            return temp;
                        }
                        else if (root->right == nullptr)
                        {
                            binary_search_tree_node <key_t, value_t> *temp = root->left;
                            return temp;
                        }
                        // inorder
                        binary_search_tree_node <key_t, value_t> *temp = minValueNode(root->right);
                        root->key = temp->key;

                        root->right = deleteNode(root->right, temp->key);

                        }return root;

                }
                
                
                /**
                 * @brief Finds the node with the minimum key
                 * @return The node with the minimum key
                 */
                const binary_search_tree_node <key_t, value_t> *minimum() {
                        binary_search_tree_node <key_t, value_t> *x = root;
                        if (x == nullptr) return nullptr;
                        while(x->left != nullptr) x = x->left;
                        return x;
                }
                /**
                 * @brief Finds the node with the maximum key
                 * @return The node with the maximum key
                 */
                const binary_search_tree_node <key_t, value_t> *maximum() {
                        binary_search_tree_node <key_t, value_t> *x = root;
                        if (x == nullptr) return nullptr;
                        while(x->right != nullptr) x = x->right;
                        return x;
                }
                /**
                 * @brief Finds the height of the tree
                 * @return The height of the binary search tree
                 */
                unsigned long long height() {
                        return height(root);
                }
                /**
                 * @brief Finds the size of the tree
                 * @return The size of the binary search tree
                 */
                unsigned long long size() {
                        return size(root);
                }
                /**
                 * @brief Finds if the binary search tree is empty
                 * @return true if the binary search tree is empty and false otherwise
                 */
                bool empty() {
                        if (root == nullptr) {
                                return true;
                        } else {
                                return false;
                        }
                }
        };
}

#endif
